#include <exception>
#include <iostream>
#include <string>

#include "consts.h"
#include "orm_manager.h"
int main() {
	std::string conn_str;
	conn_str += consts::db_config::kHostKey;
	conn_str += consts::db_config::kHost;

	conn_str += consts::db_config::kPortKey;
	conn_str += consts::db_config::kPort;

	conn_str += consts::db_config::kDbNameKey;
	conn_str += consts::db_config::kDbName;

	conn_str += consts::db_config::kUserKey;
	conn_str += consts::db_config::kUser;

	conn_str += consts::db_config::kPasswordKey;
	conn_str += consts::db_config::kPassword;

	try {
		core::OrmManager manager(conn_str);
		manager.CreateTables();
		manager.FillTables();
		std::string user_input;
		std::cout << consts::messages::kEnterPublisher;
		std::getline(std::cin >> std::ws, user_input);
		std::cout << manager.FindShopsByPublisher(user_input) << "\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cerr << consts::errors::kUnknownErrorMsg;
		return 2;
	}
	return 0;
}