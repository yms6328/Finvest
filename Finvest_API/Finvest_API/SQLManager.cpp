/*
    SQLManager.cpp
    * Create query statement and return result
    * author: Finvest
    * jag9123@gmail.com
*/


#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>
#include "SQLManager.h"

#pragma comment(lib, "libmysql.lib")

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "mmgp"
#define DB_NAME "stdb_dbo"

using namespace std;

const string T_DL("dbo_st_dldata");
const string T_CODE("dbo_st_code");
const string T_TB("dbo_st_tbdata");

SQLManager::SQLManager()
{
    // initialize variables and mysql
    m_row_num = 0;
    m_field_num = 0;
    m_is_connect = false;
    m_exist_result = false;

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
        mysql_query(&m_connect, "set names euckr"); // Set Korean
        m_is_connect = true;
    }
    else
    {
        m_is_connect = false;
    }

    return m_is_connect;
}

void SQLManager::SetTestStock(const string& stock_name)
{
    m_stock_name = stock_name;
    SQLManager::ExecuteGetStockCode();
}

string SQLManager::ExecuteGetStockCode()
{
    string query = "SELECT S_CODE FROM " + T_CODE + " where S_NAME='" + m_stock_name + "'";
    char** result = ExecuteQuery(query);

    if(result == NULL)
    {
        return "no result";
    }
    else
    {
        m_stock_code = result[0];
    }

    return m_stock_code;
}

int SQLManager::ExecuteGetClose(int date)
{
    string query = "SELECT S_CLOSE FROM " + T_DL + 
                    " WHERE S_CODE='" + m_stock_code + "' AND S_DATE='" + ConvertIntToStr(date) + "'";
    char** result = ExecuteQuery(query);

    if(result == NULL)
    {
        return 1;
    }
    else
    {
        return atoi(result[0]);
    }
}

string SQLManager::ConvertIntToStr(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

char** SQLManager::ExecuteQuery(const string& full_query)
{
    if(mysql_query(&m_connect, full_query.c_str()))
    {
        return 0;
    }
    else
    {
        m_result = mysql_store_result(&m_connect);
        if(m_result)
        {
            m_row = mysql_fetch_row(m_result);
            m_row_num = mysql_num_rows(m_result);
            m_field_num = mysql_num_fields(m_result);
            m_exist_result = true;
        }
        else
        {
            m_exist_result = false;
        }
    }

    return m_row;
}