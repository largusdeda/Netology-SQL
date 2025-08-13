#include "sql_class.h"

Database::Database(const std::string& connection) : c{ connection } { 
	std::cout << "Connected to database" << std::endl; 
}

void Database::createDbTables() {
	pqxx::work tx{ c };
	try {
		tx.exec(
			"CREATE TABLE IF NOT EXISTS clients ( \
			id SERIAL PRIMARY KEY, \
			firstname VARCHAR(40) NOT NULL, \
			lastname VARCHAR(60) NOT NULL, \
			email VARCHAR(60) UNIQUE NOT NULL \
			); \
			CREATE TABLE IF NOT EXISTS phone_numbers ( \
			id SERIAL PRIMARY KEY, \
			client_id INTEGER REFERENCES clients(id), \
			phone_number VARCHAR(30) UNIQUE);"
		);
		tx.commit();

		std::cout << "Db tables created" << std::endl;
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Database::addClient(const std::string& firstname, const std::string& lastname, const std::string& email, const std::string& phone_num) {
	pqxx::work tx{ c };
	try {
		pqxx::result res = tx.exec_params("INSERT INTO clients (firstname, lastname, email) VALUES ($1, $2, $3) RETURNING id", firstname, lastname, email);

		if (!res.empty()) {
			int client_id{ res[0][0].as<int>() };
			tx.exec_params("INSERT INTO phone_numbers (client_id, phone_number) VALUES ($1, $2)", client_id, phone_num);
			tx.commit();

			std::cout << "Client added (ID: " << client_id << ")" << std::endl;
		}
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Database::addPhoneNum(const std::string& email, const std::string& phone_num) {
	pqxx::work tx{ c };
	try {
		pqxx::result res = tx.exec_params("SELECT id FROM clients WHERE email = $1", email);
		if (!res.empty()) {
			int client_id{ res[0][0].as<int>() };
			tx.exec_params("INSERT INTO phone_numbers (client_id, phone_number) VALUES ($1, $2)", client_id, phone_num);
			tx.commit();

			std::cout << "Phone number added for client (ID: " << client_id << ")" << std::endl;
		}
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Database::updateClient(const std::string& email, const std::string& new_firstname, const std::string& new_lastname, const std::string& new_email) {
	pqxx::work tx{ c };
	try {
		pqxx::result res = tx.exec_params("SELECT id FROM clients WHERE email = $1", email);
		if (!res.empty()) {
			int client_id{ res[0][0].as<int>() };
			tx.exec_params("UPDATE clients SET firstname = $1, lastname = $2, email = $3 WHERE id = $4", new_firstname, new_lastname, new_email, client_id);
			tx.commit();

			std::cout << "Client updated (ID:  " << client_id << ")" << std::endl;
		}
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Database::removePhoneNum(const std::string& email, const std::string& phone_num) {
	pqxx::work tx{ c };
	try {
		pqxx::result res = tx.exec_params("SELECT id FROM clients WHERE email = $1", email);
		if (!res.empty()) {
			int client_id{ res[0][0].as<int>() };
			tx.exec_params("DELETE FROM phone_numbers WHERE client_id = $1 AND phone_number = $2", client_id, phone_num);
			tx.commit();

			std::cout << "Phone number removed for client (ID: " << client_id << ")" << std::endl;
		}
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Database::removeClient(const std::string& email) {
	pqxx::work tx{ c };
	try {
		pqxx::result res = tx.exec_params("SELECT id FROM clients WHERE email = $1", email);
		if (!res.empty()) {
			int client_id{ res[0][0].as<int>() };
			tx.exec_params("DELETE FROM phone_numbers WHERE client_id = $1", client_id);
			tx.exec_params("DELETE FROM clients WHERE id = $1", client_id);
			tx.commit();

			std::cout << "Client removed (ID: " << client_id << ")" << std::endl;
		}
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}

std::vector<Client> Database::findClients(const std::string& query) {
	std::vector<Client> result;
	std::map<std::string, Client> uniqueClients;

	pqxx::work tx{ c };
	try {
		pqxx::result res = tx.exec_params(
			"SELECT DISTINCT c.firstname, c.lastname, c.email, phn.phone_number FROM clients c \
			LEFT JOIN phone_numbers phn ON c.id = phn.client_id \
			WHERE c.firstname = $1 OR c.lastname = $1 OR c.email = $1 OR phn.phone_number = $1", query);
		
		for (auto& row : res) {
			std::string email = row["email"].as<std::string>();

			if (uniqueClients.find(email) == uniqueClients.end()) {
				Client client;
				client.firstname = row["firstname"].as<std::string>();
				client.lastname = row["lastname"].as<std::string>();
				client.email = email;
				uniqueClients[email] = client;
			}

			if (!row["phone_number"].is_null()) {
				uniqueClients[email].phone_numbers.push_back(
					row["phone_number"].as<std::string>()
				);
			}
		}

		for (const auto& [email, client] : uniqueClients) {
			result.push_back(client);
		}

		return result;
	}
	catch (pqxx::sql_error e) {
		std::cout << e.what() << std::endl;
	}
}



