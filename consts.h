#pragma once
#include <string_view>

namespace consts {
	namespace default_values {
		inline constexpr int kId = 0;
		inline constexpr std::string_view kName = "empty";
		inline constexpr std::string_view kTitle = "empty";
		inline constexpr int kCount = 0;
		inline constexpr double kPrice = 0.0;
		inline constexpr std::string_view kDateSale = "empty-empty-empty";
	}
	namespace db_columns {
		// Common
		inline constexpr std::string_view kIdCol = "id";
		inline constexpr std::string_view kNameCol = "name";
		// Book
		inline constexpr std::string_view kTitleCol = "title";
		inline constexpr std::string_view kIdPublisherCol = "id_publisher";
		// Stock
		inline constexpr std::string_view kIdBookCol = "id_book";
		inline constexpr std::string_view kIdShopCol = "id_shop";
		inline constexpr std::string_view kCountCol = "count";
		// Sale
		inline constexpr std::string_view kPriceCol = "price";
		inline constexpr std::string_view kDateSaleCol = "date_sale";
		inline constexpr std::string_view kIdStockCol = "id_stock";
	}
	namespace db_tables {
		inline constexpr std::string_view kPublisherTable = "publisher";
		inline constexpr std::string_view kBookTable = "book";
		inline constexpr std::string_view kShopTable = "shop";
		inline constexpr std::string_view kStockTable = "stock";
		inline constexpr std::string_view kSaleTable = "sale";
	}
	namespace db_config {
		inline constexpr std::string_view kHostKey = "host=";
		inline constexpr std::string_view kPortKey = " port=";
		inline constexpr std::string_view kDbNameKey = " dbname=";
		inline constexpr std::string_view kUserKey = " user=";
		inline constexpr std::string_view kPasswordKey = " password=";

		inline constexpr std::string_view kHost = "localhost";
		inline constexpr std::string_view kPort = "5432";
		inline constexpr std::string_view kDbName = "postgres";
		inline constexpr std::string_view kUser = "postgres";
		inline constexpr std::string_view kPassword = "zuzha2015A!";
	}
	namespace errors {
		inline constexpr std::string_view kDboErrorMsg = "Dbo error: ";
		inline constexpr std::string_view kCodeMsg = " . Code: ";
		inline constexpr std::string_view kStandardErrorMsg = "Standard error: ";
		inline constexpr std::string_view kUnknownErrorMsg = "Unknown error occurred";
	}
	namespace messages {
		inline constexpr std::string_view kTablesCreated = "Tables created successfully.\n";
		inline constexpr std::string_view kPublisherNotFound = "Publisher not found.\n";
		inline constexpr std::string_view kNoShopsFound = "No shops found selling books by this publisher.\n";
		inline constexpr std::string_view kShopsHeader = "Shops selling books by this publisher:\n";

		inline constexpr std::string_view kDataFilled = "Data filled successfully.\n";
		inline constexpr std::string_view kEnterPublisher = "Enter publisher name or ID: ";
	}
	namespace sql_conditions {
		inline constexpr std::string_view kById = "id = ?";
		inline constexpr std::string_view kByName = "name = ?";
	}
	namespace test_data {
		// Publishers
		inline constexpr std::string_view kPubEksmo = "Eksmo";
		inline constexpr std::string_view kPubAst = "AST";
		inline constexpr std::string_view kPubAzbooka = "Azbooka-Atticus";
		// Books
		inline constexpr std::string_view kBookMaster = "Master and Margarita";
		inline constexpr std::string_view kBookCrime = "Crime and Punishment";
		inline constexpr std::string_view kBookChairs = "The Twelve Chairs";
		// Shops
		inline constexpr std::string_view kShopChitai = "Chitai-Gorod";
		inline constexpr std::string_view kShopBukvoed = "Bukvoed";
		inline constexpr std::string_view kShopMoscow = "Moscow House of Books";
		// Dates for sales
		inline constexpr std::string_view kDateNov1 = "2023-11-01";
		inline constexpr std::string_view kDateNov2 = "2023-11-02";
		inline constexpr std::string_view kDateNov3 = "2023-11-03";
		// Counts for Stock
		inline constexpr int kStockCount1 = 15;
		inline constexpr int kStockCount2 = 20;
		inline constexpr int kStockCount3 = 10;
		// Prices for Sales
		inline constexpr double kSalePrice1 = 850.50;
		inline constexpr double kSalePrice2 = 720.00;
		inline constexpr double kSalePrice3 = 1100.00;
		// Counts for Sales
		inline constexpr int kSaleCount1 = 2;
		inline constexpr int kSaleCount2 = 1;
		inline constexpr int kSaleCount3 = 3;
	}
}