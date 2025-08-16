#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <stdexcept>
#include "Db.h"

int main() {

#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif

	try {
		std::string connection{ "host=localhost port=5432 dbname=orm user=postgres password=000" };
		Database db(connection);

		db.initializeTables();
		db.populateTestData();

		std::string input{};
		std::cout << "Enter the publisher's name or id (\"exit\" to quit): ";
		std::getline(std::cin, input);
		while (input != "exit") {
			try {
				int id{ std::stoi(input)};
				db.query(id);
			}
			catch (const std::logic_error& e) {
				db.query(input);
			}

			std::cout << "Enter the publisher's name or id (\"exit\" to quit): ";
			std::getline(std::cin, input);
		}

	}
	catch (const Wt::Dbo::Exception& e) {
		std::cout << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}

