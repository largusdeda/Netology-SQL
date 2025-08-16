#pragma once

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
#include <memory>
#include <cstdlib>
#include "book.h"
#include "publisher.h"
#include "sale.h"
#include "shop.h"
#include "stock.h"

class Database {
public:
    Database(const std::string& connection_string);
    void initializeTables();
    void populateTestData();
    void query(const std::string& publisher_name);
    void query(int publisher_id);

private:
    Wt::Dbo::Session session;
};
