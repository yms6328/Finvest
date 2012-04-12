#include <iostream>
#include <mysql.h>
#include <string.h>
#include "SQLManager.h"

#pragma comment(lib, "libmysql.lib")

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "mmgp"
#define DB_NAME "stdb_dbo"

using namespace std;

SQLManager::SQLManager()
{
    mysql_init(&m_connect);
}

SQLManager::~SQLManager()
{
    mysql_close(&m_connect);
}

bool SQLManager::Connect()
{
    if(&m_connect == NULL) 
    {
        cout << "ERROR: " << mysql_error(&m_connect) << endl;
    }

    if(mysql_real_connect(&m_connect, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, 0, 0))
    {
        isConnect = true;
    }
    else
    {
        isConnect = false;
    }

    return isConnect;
}

int SQLManager::GetStockCode(char* stock_name)
{

}