#pragma once

#include <Wt/Dbo/Dbo.h>
#include <string>
#include "stock.h"

class Stock;

class Sale {

public:
	double price{ 0.0 };
	int count{ 0 };
	std::string date_sale{ "" };
	Wt::Dbo::ptr<Stock> stock;

	template<class Action>
	void persist(Action& a) {
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::field(a, date_sale, "date_sale");
		Wt::Dbo::belongsTo(a, stock, "id_stock");
	}

};