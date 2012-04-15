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

        int GetClose(); // Get close data today
        int GetPrevClose(int day); // get close data n days before
        int* GetPeriodClose(); // get close data during n days
        int GetOpen();
        int GetPrevOpen(int day);
        int* GetPeriodOpen();
};
#endif