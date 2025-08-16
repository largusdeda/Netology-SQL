#pragma once

#include <Wt/Dbo/Dbo.h>
#include <string>
#include "book.h"

class Book;

class Publisher {
	
public:
	std::string name{ "" };
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "id_publisher");
	}

};
