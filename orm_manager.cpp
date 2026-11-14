#include "orm_manager.h"

#include <charconv>
#include <exception>
#include <set>
#include <string>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "consts.h"
#include "general_models.h"
namespace core {
	OrmManager::OrmManager(const std::string & conn_str) {
		helpers::WrapExceptions([this, &conn_str]() {
			ConnectToPostgres(conn_str);
			});
	}
	void OrmManager::CreateTables() {
		helpers::WrapExceptions([this]() {
			session_.mapClass<models::Publisher>(
				consts::db_tables::kPublisherTable.data());
			session_.mapClass<models::Book>(
				consts::db_tables::kBookTable.data());
			session_.mapClass<models::Shop>(
				consts::db_tables::kShopTable.data());
			session_.mapClass<models::Stock>(
				consts::db_tables::kStockTable.data());
			session_.mapClass<models::Sale>(
				consts::db_tables::kSaleTable.data());

			Wt::Dbo::Transaction transaction(session_);
			session_.createTables();
			transaction.commit();
			});
	}
	void OrmManager::FillTables() {
		helpers::WrapExceptions([this]() {
			Wt::Dbo::Transaction transaction(session_);

			auto pub1 = CreateModel<models::Publisher>();
			FillEntity(pub1, std::string(consts::test_data::kPubEksmo));
			auto pub2 = CreateModel<models::Publisher>();
			FillEntity(pub2, std::string(consts::test_data::kPubAst));
			auto pub3 = CreateModel<models::Publisher>();
			FillEntity(pub3, std::string(consts::test_data::kPubAzbooka));

			auto book1 = CreateModel<models::Book>();
			FillEntity(book1, std::string(consts::test_data::kBookMaster), pub1);
			auto book2 = CreateModel<models::Book>();
			FillEntity(book2, std::string(consts::test_data::kBookCrime), pub2);
			auto book3 = CreateModel<models::Book>();
			FillEntity(book3, std::string(consts::test_data::kBookChairs), pub3);

			auto shop1 = CreateModel<models::Shop>();
			FillEntity(shop1, std::string(consts::test_data::kShopChitai));
			auto shop2 = CreateModel<models::Shop>();
			FillEntity(shop2, std::string(consts::test_data::kShopBukvoed));
			auto shop3 = CreateModel<models::Shop>();
			FillEntity(shop3, std::string(consts::test_data::kShopMoscow));

			auto stock1 = CreateModel<models::Stock>();
			FillEntity(stock1, consts::test_data::kStockCount1, book1, shop1);
			auto stock2 = CreateModel<models::Stock>();
			FillEntity(stock2, consts::test_data::kStockCount2, book2, shop2);
			auto stock3 = CreateModel<models::Stock>();
			FillEntity(stock3, consts::test_data::kStockCount3, book3, shop3);

			auto sale1 = CreateModel<models::Sale>();
			FillEntity(sale1, consts::test_data::kSalePrice1, 
				std::string(consts::test_data::kDateNov1), 
				consts::test_data::kSaleCount1, stock1);
			auto sale2 = CreateModel<models::Sale>();
			FillEntity(sale2, consts::test_data::kSalePrice2, 
				std::string(consts::test_data::kDateNov2), 
				consts::test_data::kSaleCount2, stock2);
			auto sale3 = CreateModel<models::Sale>();
			FillEntity(sale3, consts::test_data::kSalePrice3, 
				std::string(consts::test_data::kDateNov3), 
				consts::test_data::kSaleCount3, stock3);

			transaction.commit();
			});
	}
	std::string OrmManager::FindShopsByPublisher(const std::string& name_or_id) {
		std::string result{};
		helpers::WrapExceptions([this, &name_or_id, &result]() {
			
			Wt::Dbo::Transaction transaction(session_);
			auto publisher = FindPublisher(name_or_id);
			if (!publisher) {
				result = std::string(consts::messages::kPublisherNotFound);
				return;
			}
			auto shops = FindShops(publisher);
			if (shops.empty()) {
				result = std::string(consts::messages::kNoShopsFound);
				return;
			}
			result = helpers::FormatShopsResult(shops);
		});
		return result;
	}
	void OrmManager::ConnectToPostgres(const std::string& conn_str) {
		auto backend_postgres = std::make_unique<Wt::Dbo::backend::Postgres>(conn_str);
		session_.setConnection(std::move(backend_postgres));
	}

	void OrmManager::FillEntity(
		Wt::Dbo::ptr<models::Publisher> pub_target,
		const std::string& name) {
		pub_target.modify()->name = name;
	}

	void OrmManager::FillEntity(
		Wt::Dbo::ptr<models::Book> book_target,
		const std::string& title, 
		Wt::Dbo::ptr<models::Publisher> pub) {
		book_target.modify()->title = title;
		book_target.modify()->publisher = pub;
	}

	void OrmManager::FillEntity(
		Wt::Dbo::ptr<models::Shop> shop_target,
		const std::string& name) {
		shop_target.modify()->name = name;
	}

	void OrmManager::FillEntity(
		Wt::Dbo::ptr<models::Stock> stock_target,
		int count, 
		Wt::Dbo::ptr<models::Book> book, 
		Wt::Dbo::ptr<models::Shop> shop) {
		stock_target.modify()->count = count;
		stock_target.modify()->book = book;
		stock_target.modify()->shop = shop;
	}

	void OrmManager::FillEntity(
		Wt::Dbo::ptr<models::Sale> sale_target,
		double price, 
		const std::string& date_sale,
		int count, 
		Wt::Dbo::ptr<models::Stock> stock) {
		sale_target.modify()->price = price;
		sale_target.modify()->date_sale = date_sale;
		sale_target.modify()->count = count;
		sale_target.modify()->stock = stock;
	}
	Wt::Dbo::ptr<models::Publisher> OrmManager::FindPublisher(const std::string& name_or_id) {
		const char* end_ptr = name_or_id.data() + name_or_id.size();
		int id = 0;
		auto [ptr, ec] = std::from_chars(name_or_id.data(), end_ptr, id);
		if (ec == std::errc() && ptr == end_ptr) {
			return session_.find<models::Publisher>().
				where(std::string(consts::sql_conditions::kById)).
				bind(id);
		}
		else {
			return session_.find<models::Publisher>().
				where(std::string(consts::sql_conditions::kByName)).
				bind(name_or_id);
		}
	}
	std::set<std::string> OrmManager::FindShops(Wt::Dbo::ptr<models::Publisher> publisher) {
		std::set<std::string> unique_shops;
		for (const auto& book : publisher->books) {
			for (const auto& stock : book->stocks) {
				auto shop = stock->shop;
				if (shop) {
					unique_shops.insert(shop->name);
				}
			}
		}
		return unique_shops;
	}
}