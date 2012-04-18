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
const int DURING = 100;
const int ONEDAY = 200;

SQLManager::SQLManager()
{
    // initialize variables and mysql
    m_row_num = 0;
    m_field_num = 0;
    m_is_connect = false;
    m_exist_result = false;

    m_today = InitDate();
    str_today = DateFormatting(&m_today);

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

void SQLManager::SetStock(const string& stock_name)
{
    m_stock_name = stock_name;
    SQLManager::GetStockCode();
}

string SQLManager::GetStockCode()
{
    string query = "SELECT S_CODE FROM " + T_CODE + " where S_NAME='" + m_stock_name + "'";
    MYSQL_RES* result = ExecuteQuery(query);
    while(m_row = mysql_fetch_row(result))
    {
        if(result == NULL)
        {
            return "no result";
        }
        else
        {
            m_stock_code = m_row[0];
        }
    }

    return m_stock_code;
}

int SQLManager::GetTodayClose()
{
    return GetData(F_CLOSE);
}

int SQLManager::GetPrevClose(int nday)
{
    int* result_arr = GetData(F_CLOSE, GetPrevDate(nday), nday);
    return result_arr[m_row_num - 1];
}

int* SQLManager::GetPeriodClose(int nday)
{
    return GetData(F_CLOSE, GetPrevDate(nday), nday);
}

int SQLManager::GetTodayOpen()
{
    return GetData(F_OPEN);
}

int SQLManager::GetPrevOpen(int nday)
{
    int* result_arr = GetData(F_OPEN, GetPrevDate(nday), nday);
    return result_arr[m_row_num - 1];
}

int* SQLManager::GetPeriodOpen(int nday)
{
    return GetData(F_OPEN, GetPrevDate(nday), nday);
}

int SQLManager::GetTodayHigh()
{
    return GetData(F_HIGH);
}

int SQLManager::GetPrevHigh(int nday)
{
    int* result_arr = GetData(F_HIGH, GetPrevDate(nday), nday);
    return result_arr[m_row_num - 1];
}

int* SQLManager::GetPeriodHigh(int nday)
{
    return GetData(F_HIGH, GetPrevDate(nday), nday);
}

int SQLManager::GetTodayLow()
{
    return GetData(F_LOW);
}

int SQLManager::GetPrevLow(int nday)
{
    int* result_arr = GetData(F_LOW, GetPrevDate(nday), nday);
    return result_arr[m_row_num - 1];
}

int* SQLManager::GetPeriodLow(int nday)
{
    return GetData(F_LOW, GetPrevDate(nday), nday);
}


int SQLManager::GetData(const string& field)
{
    string query = "SELECT " + field + " FROM " + T_DL
                    + " WHERE S_CODE='" + m_stock_code
                    + "' AND S_DATE='" + str_today + "'";
    int query_res;
    MYSQL_RES* result = ExecuteQuery(query);
    while(m_row = mysql_fetch_row(result))
    {
        if(result == NULL)
        {
            return 1;
        }
        else
        {
            query_res = atoi(m_row[0]);
        }
    }

    return query_res;
}

int* SQLManager::GetData(const string& field, const string& mindate, const int nday)
{
    int count = 0;
    string str_nday = ConvertIntToStr(nday);
    string query = "SELECT " + field + ", S_DATE FROM " + T_DL + " WHERE S_CODE='" + m_stock_code + "' AND "
                   + "S_DATE > '" + mindate + "' AND S_DATE < '"
                   + str_today + "' ORDER BY S_DATE DESC LIMIT " + str_nday;

    MYSQL_RES* result = ExecuteQuery(query);
    int* query_res = new int[m_row_num];

    while(m_row = mysql_fetch_row(result))
    {
        if(result == NULL)
        {
            ;
        }
        else
        {
            for(int i = 0; i < m_field_num; i++)
            {
                query_res[count] = atoi(m_row[0]);
            }
            count++;            
        }
    }

    return query_res;
}

MYSQL_RES* SQLManager::ExecuteQuery(const string& full_query)
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
            m_row_num = mysql_num_rows(m_result);
            m_field_num = mysql_num_fields(m_result);
            m_exist_result = true;
        }
        else
        {
            m_exist_result = false;
        }
    }

    return m_result;
}

tm SQLManager::InitDate()
{
    struct tm init_date;

    // temp date & initialize date - 20051104
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

string SQLManager::GetPrevDate(int nday)
{
    struct tm newtime; 
    time_t tday; 
    tday = 0;

    localtime_s(&newtime, &tday);
    newtime.tm_mday += 1;
    tday = mktime(&newtime);
 
    time_t tnow = mktime(&m_today);
    tnow -= (tday * (nday + 5));
    localtime_s(&newtime, &tnow);

    return DateFormatting(&newtime);
}

string SQLManager::ConvertIntToStr(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}