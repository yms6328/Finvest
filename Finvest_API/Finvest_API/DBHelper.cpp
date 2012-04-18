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

int DBHelper::GetPrevClose(int nday)
{
    return sql_manager.GetPrevClose(nday);
}

int* DBHelper::GetPeriodClose(int nday)
{
    return sql_manager.GetPeriodClose(nday);
}

int DBHelper::GetOpen()
{
    return sql_manager.GetTodayOpen();
}

int DBHelper::GetPrevOpen(int nday)
{
    return sql_manager.GetPrevOpen(nday);
}

int* DBHelper::GetPeriodOpen(int nday)
{
    return sql_manager.GetPeriodOpen(nday);
}

int DBHelper::GetHigh()
{
    return sql_manager.GetTodayHigh();
}

int DBHelper::GetPrevHigh(int nday)
{
    return sql_manager.GetPrevHigh(nday);
}

int* DBHelper::GetPeriodHigh(int nday)
{
    return sql_manager.GetPeriodHigh(nday);
}

int DBHelper::GetLow()
{
    return sql_manager.GetTodayLow();
}

int DBHelper::GetPrevLow(int nday)
{
    return sql_manager.GetPrevLow(nday);
}

int* DBHelper::GetPeriodLow(int nday)
{
    return sql_manager.GetPeriodLow(nday);
}