#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <map>

struct Client {
	std::string firstname;
	std::string lastname;
	std::string email;
	std::vector<std::string> phone_numbers;
};

class Database {

private:
	pqxx::connection c;

public:
	Database(const std::string& connection);

	void createDbTables();
	void addClient(const std::string& first_name, const std::string& last_name, const std::string& email, const std::string& phone_num);
	void addPhoneNum(const std::string& email,  const std::string& phone_num);
	void updateClient(const std::string& email, const std::string& new_firstname, const std::string& new_lastname, const std::string& new_email);
	void removePhoneNum(const std::string& email, const std::string& phone_num);
	void removeClient(const std::string& email);

	std::vector<Client> findClients(const std::string& query);
};
