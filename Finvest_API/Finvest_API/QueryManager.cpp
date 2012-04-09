#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string>
#include <sstream>
#include "QueryManager.h"

#pragma comment(lib, "libmysql.lib")

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "mmgp"
#define DB_NAME "stdb_dbo"

QueryManager::QueryManager()
{
    ;
}

void QueryManager::DB_Connect()
{
    m_connection = mysql_init(NULL);
    
    if(!mysql_real_connect(m_connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, 0, 0))
    {
        fprintf(stderr, "connection failed");
    }
    else
    {
        mysql_query(m_connection, "set names euckr"); // Set Korean
        std::cout << "Success connecting database!" << std::endl;
    }
}

std::string QueryManager::ExecuteGetCodeQuery(const std::string& name)
{
    std::string query = "Select S_CODE from dbo_st_code where S_NAME='" + name + "';";
    std::stringstream ss;
    ss << execute(query);
    return ss.str();
}

char* QueryManager::execute(const std::string& full_query)
{
    char* return_result = "No results!!";
    int query_state = mysql_query(m_connection, full_query.c_str());
    if (query_state != 0)
    {
        std::cout << mysql_error(m_connection) << std::endl;
    }
    m_result = mysql_store_result(m_connection);
    while((m_row = mysql_fetch_row(m_result)) != NULL)
    {
        return_result = m_row[0];
    }

    return return_result;
}