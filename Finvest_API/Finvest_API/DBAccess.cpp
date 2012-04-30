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

const std::string T_DL("st_dldata");
const std::string T_CODE("st_code");
const std::string T_TB("st_tbdata");

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

bool DBAccess::SetStock(const std::string& stock_name)
{
    ClearMemory();
    return LoadData(DBAccess::GetStockCode(stock_name));
}

bool DBAccess::LoadData(const std::string& stock_code)
{
    int count = 0;
    std::string query = "SELECT * FROM " + T_DL;
    query += " WHERE S_CODE = '" + stock_code + "'";
    query += "AND S_DATE <= '" + str_today + "'";
    query += "ORDER BY S_DATE DESC LIMIT 50";

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
                gStock_memory[count].m_cDate = m_row[1];
                gStock_memory[count].m_nOpen = atoi(m_row[2]);
                gStock_memory[count].m_nHigh = atoi(m_row[3]);
                gStock_memory[count].m_nLow = atoi(m_row[4]);
                gStock_memory[count].m_nClose = atoi(m_row[5]);
                gStock_memory[count].m_nDiff = atoi(m_row[6]);
                gStock_memory[count].m_dVolume = atof(m_row[7]);
                gStock_memory[count].m_fScale = (float)atof(m_row[8]);
                gStock_memory[count].m_dPMA5 = atof(m_row[9]);
                gStock_memory[count].m_dPMA10 = atof(m_row[10]);
                gStock_memory[count].m_dPMA20 = atof(m_row[11]);
                gStock_memory[count].m_dPMA60 = atof(m_row[12]);
                gStock_memory[count].m_dPMA120 = atof(m_row[13]);
                gStock_memory[count].m_dVMA5 = atof(m_row[14]);
                gStock_memory[count].m_dVMA10 = atof(m_row[15]);
                gStock_memory[count].m_dVMA20 = atof(m_row[16]);
                gStock_memory[count].m_dVMA60 = atof(m_row[17]);
                gStock_memory[count].m_dVMA120 = atof(m_row[18]);

                count++;
            }
        }
        else
        {
            printf("No result \n");
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
    int* arr = new int[nDay];
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nClose;
    }
    return arr;
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
    int* arr = new int[nDay];
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nOpen;
    }
    return arr;
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
    int* arr = new int[nDay];
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nHigh;
    }
    return arr;
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
    int* arr = new int[nDay];
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nLow;
    }
    return arr;
}

// Diff
int DBAccess::GetTodayDiff()
{
    return gStock_memory[0].m_nDiff;
}//종가기준

int DBAccess::GetPrevDiff(int nDay)
{
    return gStock_memory[(nDay - 1)].m_nDiff;
}

int* DBAccess::GetDiff(int nDay)
{
    int* arr = new int[nDay];
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_nDiff;
    }
    return arr;
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
    double* arr = new double[nDay];
    for(int cnt = 0; cnt < nDay; cnt++)
    {
        arr[cnt] = gStock_memory[cnt].m_dVolume;
    }
    return arr;
}

// Scale
float DBAccess::GetScale()
{
    return gStock_memory[0].m_fScale;
}

// PMA5
double DBAccess::GetPMA5()
{
    return gStock_memory[0].m_dPMA5;
}

// PMA10
double DBAccess::GetPMA10()
{
    return gStock_memory[0].m_dPMA10;
}

// PMA20
double DBAccess::GetPMA20()
{
    return gStock_memory[0].m_dPMA20;
}

// PMA60
double DBAccess::GetPMA60()
{
    return gStock_memory[0].m_dPMA60;
}

// PMA120
double DBAccess::GetPMA120()
{
    return gStock_memory[0].m_dPMA120;
}

// VMA5
double DBAccess::GetVMA5()
{
    return gStock_memory[0].m_dVMA5;
}

// VMA10
double DBAccess::GetVMA10()
{
    return gStock_memory[0].m_dVMA10;
}

// VMA20
double DBAccess::GetVMA20()
{
    return gStock_memory[0].m_dVMA20;
}

// VMA60
double DBAccess::GetVMA60()
{
    return gStock_memory[0].m_dVMA60;
}

// VMA120
double DBAccess::GetVMA120()
{
    return gStock_memory[0].m_dVMA120;
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

std::string DBAccess::GetStockCode(const std::string& stock_name)
{
    std::string code;
    std::string query = "SELECT S_CODE FROM " + T_CODE + "WHERE S_NAME = '";
    query += stock_name + "' ";

    std::cout << "execute query --- " << query << std::endl;
    mysql_query(&m_connect, query.c_str());
    m_result = mysql_store_result(&m_connect);
    if(m_result)
    {
        code = m_row[0];
    }
    else
    {
        code = "";
    }

    return code;
}