#include <iostream>
#include <string>
#include "DBHelper.h"
#include "QueryManager.h"

DBHelper::DBHelper()
{
    ;
}

void DBHelper::Connect()
{
    m_q_manager.DB_Connect();
}

void DBHelper::GetStockCode(const std::string& stock_name)
{
    std::cout << m_q_manager.ExecuteGetCodeQuery(stock_name) << std::endl;
}

void DBHelper::GetStockName(const std::string& stock_code)
{
    std::string query = "Select S_NAME from dbo_st_code where S_CODE=" + stock_code + ";";
}