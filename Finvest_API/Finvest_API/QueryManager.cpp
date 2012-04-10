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
    return execute(query);
}

std::string QueryManager::ExecuteGetNameQuery(const std::string& code)
{
    std::string query = "Select S_NAME from dbo_st_code where S_CODE=" + code + ";";
    return execute(query);
}

int QueryManager::ExecuteGetCloseQuery(const std::string& query)
{
    char result_array[3];
    std::string full_query = "Select S_CLOSE from dbo_st_dldata " + query;
    return atoi(execute(full_query).c_str());
}

void QueryManager::test()
{
    std::string query = "select S_CLOSE from dbo_st_dldata limit 3";
    execute(query);
}

std::string QueryManager::execute(const std::string& full_query)
{
    std::stringstream ss;

    int query_state = mysql_query(m_connection, full_query.c_str());
    if (query_state != 0)
    {
        std::cout << mysql_error(m_connection) << std::endl;
    }
    m_result = mysql_store_result(m_connection);
    int fields = mysql_num_fields(m_result);
    int num_of_row = mysql_num_rows(m_result);

    std::cout << "num of row: " << num_of_row << std::endl;
    std::cout << "num of field: " << fields << std::endl;

    while((m_row = mysql_fetch_row(m_result)) != NULL)
    {
        for(int count = 0; count < num_of_row; count++)
        {
            ss << m_row[0];
            std::cout << "row" << count << " " << m_row[count] << std::endl;
        }
    }

    return ss.str();
}