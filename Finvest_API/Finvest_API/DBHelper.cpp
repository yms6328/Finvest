#include <iostream>
#include <string>
#include <sstream>
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

std::string DBHelper::GetStockCode(const std::string& stock_name)
{
    std::stringstream sstr;
    sstr << m_q_manager.ExecuteGetCodeQuery(stock_name);
    return sstr.str();
}

void DBHelper::GetStockName(const std::string& stock_code)
{
    std::cout << m_q_manager.ExecuteGetNameQuery(stock_code) << std::endl;;
}

int DBHelper::GetClose(const std::string& stock_name, const std::string& stock_date)
{
    std::string query = "where S_CODE='" + DBHelper::GetStockCode(stock_name) + "' AND S_DATE='" + stock_date;
    return m_q_manager.ExecuteGetCloseQuery(query);
}

void DBHelper::test()
{
    m_q_manager.test();
}