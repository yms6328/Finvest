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
    if (query_state != 0) {
        std::cout << mysql_error(m_connection) << std::endl;
    }
    m_result = mysql_store_result(m_connection);
    while ( ( m_row = mysql_fetch_row(m_result)) != NULL ) {
        std::cout << m_row[0] << std::endl;
    }
}

void DBHelper::GetStockCode(const std::string& stock_name)
{
    int query_state;
    std::string query;
    query = "Select S_CODE from dbo_st_code where S_NAME=" + stock_name;
    query_state = mysql_query(m_connection, query.c_str());
    if (query_state != 0) {
        std::cout << mysql_error(m_connection) << std::endl;
    }
    m_result = mysql_store_result(m_connection);
    while ( ( m_row = mysql_fetch_row(m_result)) != NULL ) {
        std::cout << m_row[0] << std::endl;
    }
}

void DBHelper::GetStockName(const std::string& stock_code)
{
    int query_state;
    std::string query;
    query = "Select S_NAME from dbo_st_code where S_CODE=" + stock_code;
    query_state = mysql_query(m_connection, query.c_str());
    if (query_state != 0) {
        std::cout << mysql_error(m_connection) << std::endl;
    }
    m_result = mysql_store_result(m_connection);
    while ( ( m_row = mysql_fetch_row(m_result)) != NULL ) {
        std::cout << m_row[0] << std::endl;
    }
}