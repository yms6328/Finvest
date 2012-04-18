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

        int GetClose(); // Get close data tonday
        int GetPrevClose(int nday); // get close data n ndays before
        int* GetPeriodClose(int nday); // get close data during n ndays

        int GetOpen();
        int GetPrevOpen(int nday);
        int* GetPeriodOpen(int nday);

        int GetHigh();
        int GetPrevHigh(int nday);
        int* GetPeriodHigh(int nday);

        int GetLow();
        int GetPrevLow(int nday);
        int* GetPeriodLow(int nday);
};
#endif