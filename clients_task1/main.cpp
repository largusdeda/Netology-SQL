#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <vector>
#include "sql_class.h"

int main() {

#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif

	std::string connection{ "host=localhost port=5432 dbname=clients user=postgres password=000" };
	Database db(connection);

	db.createDbTables();

	db.addClient("AAA", "BBB", "ccc@ddd.com", "88005553535");
	db.addClient("Adsd", "Jjkjkh", "gfdg@ddd.com", "21344234");

	db.addPhoneNum("ccc@ddd.com", "969696");
	db.addPhoneNum("ccc@ddd.com", "535435");
	db.addPhoneNum("gfdg@ddd.com", "0000000");

	db.updateClient("gfdg@ddd.com", "GG", "KK", "newemail@qq.ru");

	db.removePhoneNum("newemail@qq.ru", "21344234");

	db.addClient("AAA", "LLL", "lll@joo.ru", "123456");

	db.addPhoneNum("lll@joo.ru", "987654");

	std::vector<Client> found = db.findClients("AAA");
	for (const auto& client : found) {
		std::cout << "Found client: " << client.firstname << " " << client.lastname << " " << client.email << " ";
		for (const auto& phone_num : client.phone_numbers) {
			std::cout << phone_num << " ";
		}
		std::cout << std::endl;
	}

	db.removeClient("ccc@ddd.com");

	return EXIT_SUCCESS;
}