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
        void SetStock(const std::string& stock_name);

        std::string GetStockCode();

        int GetClose(); // 오늘 날짜의 data 가져옴
        int GetPrevClose(); // n일 전의 data
        int* GetPeriodClose(); // n일간의 data

    private:
        int nday;
};
#endif