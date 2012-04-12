#ifndef DBHELPER_H
#define DBHELPER_H
#include <string>
#include "SQLManager.h"

class DBHelper
{
    public:
        SQLManager sql_manager;

        DBHelper();
        ~DBHelper();        

        void DBConnect();

        int GetStockCode(char* stock_name);
        std::string GetStockName(const std::string& stock_code);

        int GetTodayClose(const std::string& stock_name); // 오늘 날짜의 data 가져옴
        int GetPrevClose(const std::string& stock_name, int day); // n일 전의 data
        int* GetPeriodClose(const std::string& stock_name, int period); // n일간의 data
};
#endif