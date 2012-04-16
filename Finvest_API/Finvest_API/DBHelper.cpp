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
    sql_manager.GetBeforeClose(day);
    return 0;
}

int DBHelper::GetOpen()
{
    return sql_manager.GetTodayOpen();
}

int DBHelper::GetPrevOpen(int day)
{
    return sql_manager.GetBeforeOpen(day);
}

int DBHelper::GetHigh()
{
    return sql_manager.GetTodayHigh();
}

int DBHelper::GetPrevHigh(int day)
{
    return sql_manager.GetBeforeHigh(day);
}

int DBHelper::GetLow()
{
    return sql_manager.GetTodayLow();
}

int DBHelper::GetPrevLow(int day)
{
    return sql_manager.GetBeforeLow(day);
}