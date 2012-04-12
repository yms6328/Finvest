#include <iostream>
#include <string.h>
#include <sstream>
#include "DBHelper.h"
#include "SQLManager.h"

using namespace std;

DBHelper::DBHelper()
{
    DBHelper::DBConnect();
}

DBHelper::~DBHelper()
{
    ;
}

void DBHelper::DBConnect()
{
    if(sql_manager.Connect())
    {
        cout << "Database connection complete" << endl;
    }
    else
    {
        cout << "Connection falied" << endl;
    }
}

int DBHelper::GetStockCode(char* stock_name)
{
    return sql_manager.GetStockCode(stock_name);
}