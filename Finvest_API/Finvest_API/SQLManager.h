#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <mysql.h>

class SQLManager
{
    MYSQL m_connect;
    MYSQL_RES* m_result;
    MYSQL_ROW m_row;
    bool isConnect;

    public:
        SQLManager();
        virtual ~SQLManager();

        bool Connect();
        int GetStockCode(char* stock_name);
};

#endif