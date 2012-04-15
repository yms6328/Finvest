/*
    DBHelper.cpp
    * Stock Database API
    * author: Finvest
    * jag9123@gmail.com
*/

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
    sql_manager.~SQLManager();
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

void DBHelper::SetStock(const string& stock_name)
{
    sql_manager.SetTestStock(stock_name);
}

string DBHelper::GetStockCode()
{
    return sql_manager.GetStockCode();
}

int DBHelper::GetClose()
{
    return sql_manager.GetTodayClose();
}

int DBHelper::GetPrevClose(int day)
{
    return sql_manager.GetBeforeClose(day);
}

int DBHelper::GetOpen()
{
    return sql_manager.GetTodayOpen();
}