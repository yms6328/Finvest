#ifndef DBHELPER_H
#define DBHELPER_H
#include <string>

class DBHelper
{
    public:
        void Connect();
        void GetClose();
        void GetClose(const std::string& stock_code);
        void GetStockCode(const std::string& stock_name);
        void GetStockName(const std::string& stock_code);
};
#endif