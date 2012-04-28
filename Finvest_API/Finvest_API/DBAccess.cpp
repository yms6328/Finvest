#include <iostream>
#include <stdio.h>
#include <mysql.h>
#include <time.h>
#include <string>
#include <sstream>
#include "DBAccess.h"

#pragma comment(lib, "libmysql.lib")

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "mmgp"
#define DB_NAME "stdb_dbo"

using namespace std;

const string T_DL("dbo_st_dldata");
const string T_CODE("dbo_st_code");
const string T_TB("dbo_st_tbdata");

DBAccess::DBAccess()
{
    printf("start \n");
    mysql_init(&m_connect);
    str_today = "20050607";
    DBConnect();
}

DBAccess::~DBAccess()
{
    mysql_close(&m_connect);
}

bool DBAccess::DBConnect()
{
    printf("DB Connect \n");
    if(&m_connect == NULL)
    {
        printf("error", mysql_error(&m_connect));
    }

    if(mysql_real_connect(&m_connect, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, 0, 0))
    {
        mysql_query(&m_connect, "set names euckr"); // Set Korean
        m_isConnect = true;
    }
    else
    {
        m_isConnect = false;
    }

    return m_isConnect;
}

bool DBAccess::SetStock(const string& stock_code)
{
    ClearMemory();
    return LoadData(stock_code);
}

bool DBAccess::LoadData(const string& stock_code)
{
    int count = 0;
    string query = "SELECT * FROM ";
    query += T_DL;
    query += " WHERE S_CODE = '";
    query += stock_code;
    query += "' AND S_DATE <= '";
    query += str_today;
    query += "' ORDER BY S_DATE DESC LIMIT 50";

    cout << query << endl;
    if(mysql_query(&m_connect, query.c_str()))
    {
        m_existResult = false;
    }
    else
    {
        m_result = mysql_store_result(&m_connect);
        if(m_result)
        {
            m_rowNum = mysql_num_rows(m_result);
            m_fieldNum = mysql_num_fields(m_result);
            m_existResult = true;

            while(m_row = mysql_fetch_row(m_result))
            {
                if(m_result == NULL)
                {
                    m_existResult = false;
                }
                else
                {
                    gStock_memory[count].m_cDate = m_row[1];
                    /*
                        save data to array
                        !
                        how to convert char* to double or float
                        int -> atoi
                    */
                }
                count++;
            }
        }
        else
        {
            m_existResult = false;
        }
    }
    return m_existResult;
}

/*
    public functions
*/

// Close
int DBAccess::GetTodayClose()
{
    return gStock_memory[0].m_nClose;   
}

int DBAccess::GetPrevClose(int nDay)
{
    return gStock_memory[(nDay - 1)].m_nClose;
}

int* DBAccess::GetClose(int nDay)
{
    int* arr;
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nClose;
    }
}

// Open
int DBAccess::GetTodayOpen()
{
    return gStock_memory[0].m_nOpen;
}

int DBAccess::GetPrevOpen(int nDay)
{
    return gStock_memory[(nDay - 1)].m_nOpen;
}

int* DBAccess::GetOpen(int nDay)
{
    int* arr;
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nOpen;
    }
}

// High
int DBAccess::GetTodayHigh()
{
    return gStock_memory[0].m_nHigh;
}

int DBAccess::GetPrevHigh(int nDay)
{
    return gStock_memory[(nDay - 1)].m_nHigh;
}

int* DBAccess::GetHigh(int nDay)
{
    int* arr;
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nHigh;
    }
}

// Low
int DBAccess::GetTodayLow()
{
    return gStock_memory[0].m_nLow;
}

int DBAccess::GetPrevLow(int nDay)
{
    return gStock_memory[(nDay - 1)].m_nLow;
}

int* DBAccess::GetLow(int nDay)
{
    int* arr;
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nLow;
    }
}

// Diff
int DBAccess::GetTodayDiff()
{
    return gStock_memory[0].m_nDiff;
}

int DBAccess::GetPrevDiff(int nDay)
{
    return gStock_memory[(nDay - 1)].m_nDiff;
}

int* DBAccess::GetDiff(int nDay)
{
    int* arr;
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nDiff;
    }
}

// Volume
double DBAccess::GetTodayVolume()
{
    return gStock_memory[0].m_dVolume;
}

double DBAccess::GetPrevVolume(int nDay)
{
    return gStock_memory[(nDay - 1)].m_dVolume;
}

double* DBAccess::GetVolume(int nDay)
{
    int* arr;
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_dVolume;
    }
}

/*
    private functions
*/
void DBAccess::ClearMemory()
{
    printf("clear \n");
    int i;
    for(i = 0; i < 50; i++)
    {
        gStock_memory[i].m_cDate = "";
        gStock_memory[i].m_nClose = 0;
        gStock_memory[i].m_nOpen = 0;
        gStock_memory[i].m_nHigh = 0;
        gStock_memory[i].m_nLow = 0;
        gStock_memory[i].m_nDiff = 0;
        gStock_memory[i].m_fScale = 1.0;
        gStock_memory[i].m_dVolume = 0.0;
        gStock_memory[i].m_dPMA5 = 0.0;
        gStock_memory[i].m_dPMA10 = 0.0;
        gStock_memory[i].m_dPMA20 = 0.0;
        gStock_memory[i].m_dPMA60 = 0.0;
        gStock_memory[i].m_dPMA120 = 0.0;
        gStock_memory[i].m_dVMA5 = 0.0;
        gStock_memory[i].m_dVMA10 = 0.0;
        gStock_memory[i].m_dVMA20 = 0.0;
        gStock_memory[i].m_dVMA60 = 0.0;
        gStock_memory[i].m_dVMA120 = 0.0;
    }
}