#pragma once
#include <functional>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "consts.h"
#include "general_models.h"
namespace core {
	class OrmManager {
	public:
		explicit OrmManager(const std::string& conn_str);
		~OrmManager() = default;
		void CreateTables();
		void FillTables();
		std::string FindShopsByPublisher(const std::string& name_or_id);
	private:
		void ConnectToPostgres(const std::string& conn_str);
		void FillEntity(
			Wt::Dbo::ptr<models::Publisher> pub_target,
			const std::string& name
		);
		void FillEntity(
			Wt::Dbo::ptr<models::Book> book_target,
			const std::string& title,
			Wt::Dbo::ptr<models::Publisher> pub
		);
		void FillEntity(
			Wt::Dbo::ptr<models::Shop> shop_target,
			const std::string& name
		);
		void FillEntity(
			Wt::Dbo::ptr<models::Stock> stock_target,
			int count,
			Wt::Dbo::ptr<models::Book> book,
			Wt::Dbo::ptr<models::Shop> shop
		);
		void FillEntity(
			Wt::Dbo::ptr<models::Sale> sale_target,
			double price,
			const std::string& date_sale,
			int count,
			Wt::Dbo::ptr<models::Stock> stock
		);
		template <typename T>
		Wt::Dbo::ptr<T> CreateModel() {
			return session_.add(std::make_unique<T>());
		}
		Wt::Dbo::ptr<models::Publisher> FindPublisher(const std::string& name_or_id);
		std::set<std::string> FindShops(Wt::Dbo::ptr<models::Publisher> publisher);
		Wt::Dbo::Session session_;
	};
}
namespace helpers { 
	inline std::string FormatShopsResult(const std::set<std::string>& shops) { // for formatting search shops result 
		std::string result = std::string(consts::messages::kShopsHeader);
		for (const auto& shop_name : shops) {
			result += "- " + shop_name + "\n";
		}
		return result;
	}
	inline std::string FormatDboError(const Wt::Dbo::Exception& e) { // for formating errors
		std::string msg;
		msg += consts::errors::kDboErrorMsg;
		msg += e.what();
		msg += consts::errors::kCodeMsg;
		msg += e.code();
		return msg;
	}
	inline std::string FormatStdError(const std::exception& e) { // for formating errors
		std::string msg;
		msg += consts::errors::kStandardErrorMsg;
		msg += e.what();
		return msg;
	}
	inline void WrapExceptions(const std::function<void()>& action) { // for safety run methods
		try {
			action();
		}
		catch (const Wt::Dbo::Exception& e) {
			throw std::runtime_error(FormatDboError(e));
		}
		catch (const std::exception& e) {
			throw std::runtime_error(FormatStdError(e));
		}
		catch (...) {
			throw std::runtime_error(std::string(consts::errors::kUnknownErrorMsg));
		}
	}
}