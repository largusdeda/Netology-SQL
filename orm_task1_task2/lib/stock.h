#pragma once

#include <Wt/Dbo/Dbo.h>
#include "book.h"
#include "shop.h"
#include "sale.h"

class Shop;
class Book;
class Sale;

class Stock {

public:
	int count{ 0 };
	Wt::Dbo::ptr<Shop> shop;
	Wt::Dbo::ptr<Book> book;
	Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, book, ">id_book");
		Wt::Dbo::belongsTo(a, shop, ">id_shop");
		Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, ">id_stock");
	}

};