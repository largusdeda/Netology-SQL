#include "db.h"

class Book;
class Publisher;
class Sale;
class Shop;
class Stock;


Database::Database(const std::string& connection_string) {
	try {
		auto postgres{ std::make_unique<Wt::Dbo::backend::Postgres>(connection_string) };
		session.setConnection(std::move(postgres));
	}
	catch (const Wt::Dbo::Exception& e) {
		throw;
	}
}

void Database::initializeTables() {
	try {
		session.mapClass<Book>("book");
		session.mapClass<Publisher>("publisher");
		session.mapClass<Sale>("sale");
		session.mapClass<Shop>("shop");
		session.mapClass<Stock>("stock");

		session.createTables();
	}
	catch (const Wt::Dbo::Exception& e) {
		throw;
	}
}

void Database::populateTestData() {
	try {
		Wt::Dbo::Transaction t{ session };

		std::unique_ptr<Publisher> publisher_1{ new Publisher() };
		publisher_1->name = "Bloomsbury Publishing";
		auto publisher_1_ptr{ session.add(std::move(publisher_1)) };
		std::unique_ptr<Publisher> publisher_2{ new Publisher() };
		publisher_2->name = "Allen & Unwin";
		auto publisher_2_ptr{ session.add(std::move(publisher_2)) };
		std::unique_ptr<Publisher> publisher_3{ new Publisher() };
		publisher_3->name = "Doubleday";
		auto publisher_3_ptr{ session.add(std::move(publisher_3)) };

		std::unique_ptr<Shop> shop_1{ new Shop() };
		shop_1->name = "Strand Bookstore";
		auto shop_1_ptr{ session.add(std::move(shop_1)) };
		std::unique_ptr<Shop> shop_2{ new Shop() };
		shop_2->name = "Kingsbridge Rd Bookshop";
		auto shop_2_ptr{ session.add(std::move(shop_2)) };
		std::unique_ptr<Shop> shop_3{ new Shop() };
		shop_3->name = "East Village Books";
		auto shop_3_ptr{ session.add(std::move(shop_3)) };

		std::unique_ptr<Book> book_1{ new Book() };
		book_1->title = "J. K. Rowling \"Harry Potter and the Chamber of Secrets\"";
		book_1->publisher = session.find<Publisher>().where("name = ?").bind("Bloomsbury Publishing");
		auto book_1_ptr{ session.add(std::move(book_1)) };
		std::unique_ptr<Book> book_2{ new Book() };
		book_2->title = "Neil Gaiman \"Coraline\"";
		book_2->publisher = session.find<Publisher>().where("name = ?").bind("Bloomsbury Publishing");
		auto book_2_ptr{ session.add(std::move(book_2)) };
		std::unique_ptr<Book> book_3{ new Book() };
		book_3->title = "J. R. R. Tolkien \"The Lord of the Rings\"";
		book_3->publisher = session.find<Publisher>().where("name = ?").bind("Allen & Unwin");
		auto book_3_ptr{ session.add(std::move(book_3)) };
		std::unique_ptr<Book> book_4{ new Book() };
		book_4->title = "Graham Dunstan Martin \"Time-Slip\"";
		book_4->publisher = session.find<Publisher>().where("name = ?").bind("Allen & Unwin");
		auto book_4_ptr{ session.add(std::move(book_4)) };
		std::unique_ptr<Book> book_5{ new Book() };
		book_5->title = "Stephen King \"Pet Sematary\"";
		book_5->publisher = session.find<Publisher>().where("name = ?").bind("Doubleday");
		auto book_5_ptr{ session.add(std::move(book_5)) };
		std::unique_ptr<Book> book_6{ new Book() };
		book_6->title = "Arthur Hailey \"Airport\"";
		book_6->publisher = session.find<Publisher>().where("name = ?").bind("Doubleday");
		auto book_6_ptr{ session.add(std::move(book_6)) };

		Wt::Dbo::collection<Wt::Dbo::ptr<Shop>> shops = session.find<Shop>();
		for (const auto& shop : shops) {
			Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books = session.find<Book>();
			for (const auto& book : books) {
				if ((shop->name == "East Village Books" || shop->name == "Kingsbridge Rd Bookshop") && book->publisher->name == "Doubleday") {
					continue;
				}

				int count{ std::rand() % 51 };
				std::unique_ptr<Stock> stock{ new Stock() };
				stock->book = book;
				stock->shop = shop;
				stock->count = count;
				auto stock_ptr{ session.add(std::move(stock)) };
			}
		}

		Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks = session.find<Stock>();
		for (const auto& stock : stocks) {
			double price{ std::rand() % 6 + 6.99 };
			int count{ std::rand() % 5 + 1 };
			std::string year = std::to_string(std::rand() % 25 + 2000);
			std::string month = std::to_string(std::rand() % 12 + 1);
			std::string day = std::to_string(std::rand() % 28 + 1);
			std::string date_sale = year + "-" + month + "-" + day;

			std::unique_ptr<Sale> sale{ new Sale() };
			sale->stock = stock;
			sale->price = price;
			sale->count = count;
			sale->date_sale = date_sale;
			auto sale_ptr{ session.add(std::move(sale)) };
		}

		t.commit();
	}
	catch (const Wt::Dbo::Exception& e) {
		throw;
	}
}

void Database::query(const std::string& publisher_name) {
	try {
		Wt::Dbo::Transaction t{ session };

		auto shops = session.query<Wt::Dbo::ptr<Shop>>("SELECT DISTINCT s FROM \"shop\" s")
			.join("\"stock\" st ON s.id = st.id_shop")
			.join("\"book\" b ON st.id_book = b.id")
			.join("\"publisher\" p ON b.id_publisher = p.id")
			.where("p.name = ?")
			.bind(publisher_name).resultList();

		if (shops.size() > 0) {
			std::cout << "Shops that sell \"" << publisher_name << "\" books:" << std::endl;
			for (const auto& sh : shops) {
				std::cout << sh->name << std::endl;
			}
		}
		else {
			std::cout << "No shops that sell \"" << publisher_name << "\" books." << std::endl;
		}

		t.commit();
	}
	catch (const Wt::Dbo::Exception& e) {
		throw;
	}
}

void Database::query(int publisher_id) {
	try {
		Wt::Dbo::Transaction t{ session };

		auto shops = session.query<Wt::Dbo::ptr<Shop>>("SELECT DISTINCT s FROM \"shop\" s")
			.join("\"stock\" st ON s.id = st.id_shop")
			.join("\"book\" b ON st.id_book = b.id")
			.join("\"publisher\" p ON b.id_publisher = p.id")
			.where("p.id = ?")
			.bind(publisher_id).resultList();

		Wt::Dbo::ptr<Publisher> p{ session.find<Publisher>().where("id = ?").bind(publisher_id) };
		if (shops.size() > 0) {
			std::cout << "Shops that sell \"" << p->name << "\" books:" << std::endl;
			for (const auto& sh : shops) {
				std::cout << sh->name << std::endl;
			}
		}
		else {
			std::cout << "No shops that sell \"" << p->name << "\" books." << std::endl;
		}

		t.commit();
	}
	catch (const Wt::Dbo::Exception& e) {
		throw;
	}
}