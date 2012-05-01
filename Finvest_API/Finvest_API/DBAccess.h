#ifndef DBACCESS_H
#define DBACCESS_H
#include <iostream>
#include <mysql.h>

class DBAccess
{
    // struct: save one row in query result
    typedef struct stock
    {
        std::string m_cDate;
        int m_nClose;
        int m_nOpen;
        int m_nHigh;
        int m_nLow;
        int m_nDiff;
        float m_fScale;

        double m_dVolume;

        // PMA: 가격 이동평균, index에서 사용
        double m_dPMA5;
        double m_dPMA10;
        double m_dPMA20;
        double m_dPMA60;
        double m_dPMA120;

        // VMA: 거래량 이동평균
        double m_dVMA5;
        double m_dVMA10;
        double m_dVMA20;
        double m_dVMA60;
        double m_dVMA120;
    } Stock;

    Stock gStock_memory[80];

    /*
        MySQL Variables
    */
    MYSQL m_connect;
    MYSQL_ROW m_row;
    MYSQL_RES* m_result;

    bool m_isConnect;
    bool m_existResult;
    int m_rowNum;
    int m_fieldNum;
    std::string str_today;

    public:
        DBAccess();
        ~DBAccess();

        bool SetStock(const std::string& stock_name);

        int GetTodayClose();
        int GetPrevClose(int nDay);
        int* GetClose(int nDay);

        int GetTodayOpen();
        int GetPrevOpen(int nDay);
        int* GetOpen(int nDay);

        int GetTodayHigh();
        int GetPrevHigh(int nDay);
        int* GetHigh(int nDay);

        int GetTodayLow();
        int GetPrevLow(int nDay);
        int* GetLow(int nDay);

        int GetTodayDiff();
        int GetPrevDiff(int nDay);
        int* GetDiff(int nDay);

        double GetTodayVolume();
        double GetPrevVolume(int nDay);
        double* GetVolume(int nDay);

        float GetScale();

        double GetPMA5();
        double GetPMA10();
        double GetPMA20();
        double GetPMA60();
        double GetPMA120();

        double GetVMA5();
        double GetVMA10();
        double GetVMA20();
        double GetVMA60();
        double GetVMA120();

        bool DBConnect();

    private:
        void ClearMemory();
        bool LoadData(const std::string& stock_code);
        std::string GetStockCode(const std::string& stock_name);
        int* GetDataArray(int nDay, int data);
};
#endif