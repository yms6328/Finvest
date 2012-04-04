#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string>
#include "DBHelper.h"

#pragma comment(lib, "libmysql.lib")

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "mmgp"
#define DB_NAME "stdb_dbo"

MYSQL *m_connection;
MYSQL_RES *m_result;
MYSQL_ROW m_row;

void DBHelper::Connect()
{
    m_connection = mysql_init(NULL);
    if(!m_connection)
    {
        fprintf(stderr, "connection failed");
    }
    
    m_connection = mysql_real_connect(m_connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
    if(m_connection)
    {
        printf("Database Connection -- Success \n");
    }
}

void DBHelper::GetClose()
{

}

void DBHelper::GetClose(const std::string& stock_code)
{
    int query_state;
    std::string query;
    query = "Select S_CLOSE from dbo_st_dldata where S_CODE=" + stock_code + " limit 3";
    query_state = mysql_query(m_connection, query.c_str());
    ExecuteQuery(query);
}

void DBHelper::GetStockCode(const std::string& stock_name)
{
    std::cout << "GetStockCode" << std::endl;
    std::string query;
    std::cout << "stock name: " << stock_name << std::endl;
    query = "Select S_CODE from dbo_st_code where S_NAME='" + stock_name + "';";
    ExecuteQuery(query);
}

void DBHelper::GetStockName(const std::string& stock_code)
{
    std::string query;
    std::cout << "stock name: " << stock_code << std::endl;
    query = "Select S_NAME from dbo_st_code where S_CODE=" + stock_code + ";";
    ExecuteQuery(query);
}

void DBHelper::ExecuteQuery(const std::string& query)
{
    std::cout << query << std::endl;
    std::cout << "Execute Query" << std::endl;
    int query_state;
    query_state = mysql_query(m_connection, query.c_str());
    std::cout << query_state << std::endl;
    if (query_state != 0)
    {
        std::cout << "error!" << std::endl;
        std::cout << mysql_error(m_connection) << std::endl;
    }
    else
    {
        std::cout << "print query result" << std::endl;
        m_result = mysql_store_result(m_connection);
        while ( ( m_row = mysql_fetch_row(m_result)) != NULL )
        {
            std::cout << "query result: ";
            std::cout << m_row[0] << std::endl;
        }
        //m_row = mysql_fetch_row(m_result);
        //std::cout << m_row << std::endl;
    }
}