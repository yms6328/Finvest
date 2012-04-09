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
        void GetStockCode(const std::string& stock_name);
        void GetStockName(const std::string& stock_code);
};
#endif