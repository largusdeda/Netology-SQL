#pragma once

#include <Wt/Dbo/Dbo.h>
#include <string>
#include "publisher.h"
#include "stock.h"

class Publisher;
class Stock;

class Book {

public:
	std::string title{ "" };
	Wt::Dbo::ptr<Publisher> publisher;
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, publisher, ">id_publisher");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, ">id_book");
	}

};