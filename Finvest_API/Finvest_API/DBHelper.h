#ifndef DBHELPER_H
#define DBHELPER_H
#include <string>
#include "QueryManager.h"

class DBHelper
{
    public:
        QueryManager m_q_manager;
        DBHelper();
        void Connect();

        int GetStockCode(const std::string& stock_name);
        std::string GetStockName(const std::string& stock_code);


        int GetClose(const std::string& stock_name);
};
#endif