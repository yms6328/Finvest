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
#include <time.h>
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
const string F_CLOSE("S_CLOSE");
const string F_OPEN("S_OPEN");
const string F_HIGH("S_HIGH");
const string F_LOW("S_LOW");

SQLManager::SQLManager()
{
    // initialize variables and mysql
    m_row_num = 0;
    m_field_num = 0;
    m_is_connect = false;
    m_exist_result = false;

    today = InitDate();

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
    SQLManager::GetStockCode();
}

string SQLManager::GetStockCode()
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

int SQLManager::GetTodayClose()
{
    return ExecuteGetData(F_CLOSE, DateFormatting(&today));
}

int SQLManager::GetBeforeClose(int day)
{
    return ExecuteGetData(F_CLOSE, GetBeforeDate(day));
}

int SQLManager::GetTodayOpen()
{
    return ExecuteGetData(F_OPEN, DateFormatting(&today));
}

int SQLManager::GetBeforeOpen(int day)
{
    return ExecuteGetData(F_OPEN, GetBeforeDate(day));
}

int SQLManager::GetTodayHigh()
{
    return ExecuteGetData(F_HIGH, DateFormatting(&today));
}

int SQLManager::GetBeforeHigh(int day)
{
    return ExecuteGetData(F_HIGH, GetBeforeDate(day));
}

int SQLManager::GetTodayLow()
{
    return ExecuteGetData(F_LOW, DateFormatting(&today));
}

int SQLManager::GetBeforeLow(int day)
{
    return ExecuteGetData(F_LOW, GetBeforeDate(day));
}


int SQLManager::ExecuteGetData(const string& field, const string& date)
{
    string query = "SELECT " + field + " FROM " + T_DL + " WHERE S_CODE='" + m_stock_code + "' AND S_DATE='" + date + "'";
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

tm SQLManager::InitDate()
{
    struct tm init_date;
    // temp date
    init_date.tm_year = 2005 - 1900;
    init_date.tm_mon = 10; // tm_mon = month + 1 = 11;
    init_date.tm_mday = 4;
    init_date.tm_hour = 0;
    init_date.tm_min = 0;
    init_date.tm_sec = 0;
    init_date.tm_isdst = 0;

    return init_date;
}

string SQLManager::DateFormatting(tm* tm_date)
{
    char buffer[26];
    strftime(buffer, 26, "%Y%m%d", tm_date);
    return buffer;
}

string SQLManager::GetBeforeDate(int nday)
{
    struct tm newtime; 
    time_t tday; 
    tday = 0;

    localtime_s(&newtime, &tday);
    newtime.tm_mday += 1;
    tday = mktime(&newtime);
 
    // 현재 시간 time_t 구하여 하루 * n 일수를 빼준다.
    time_t tnow = mktime(&today);
    tnow -= (tday * nday);
    localtime_s(&newtime, &tnow);

    // n일전 날짜를 출력해 본다.
    char timebuf[26]; 
    //asctime_s(timebuf, 26, &newtime); 
    strftime(timebuf, 26, "%Y%m%d", &newtime);
    cout << timebuf << endl;
    return timebuf;
}