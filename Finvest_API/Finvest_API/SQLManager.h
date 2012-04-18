#ifndef SQLMANAGER_H
#define SQLMANAGER_H
#include <mysql.h>
#include <string.h>
#include <time.h>

class SQLManager
{    
    public:
        SQLManager();
        virtual ~SQLManager();

        bool Connect();
        void SetStock(const std::string& stock_name);

        std::string GetStockCode();
        std::string GetStockName(const std::string& stock_code);
        
        int GetTodayClose();
        int GetPrevClose(int nday);
        int* GetPeriodClose(int nday);

        int GetTodayOpen();
        int GetPrevOpen(int nday);
        int* GetPeriodOpen(int nday);

        int GetTodayHigh();
        int GetPrevHigh(int nday);
        int* GetPeriodHigh(int nday);

        int GetTodayLow();
        int GetPrevLow(int nday);
        int* GetPeriodLow(int nday);

    private:
        /* variables */
        MYSQL m_connect;
        MYSQL_RES* m_result;
        MYSQL_ROW m_row;

        std::string m_stock_name;
        std::string m_stock_code;
        std::string str_today;

        bool m_is_connect;
        bool m_exist_result;
        int m_row_num;
        int m_field_num;

        tm m_today;

        /* functions */
        tm InitDate();

        int GetData(const std::string& field);
        int* GetData(const std::string& field, const std::string& min_date, const int nday);
        MYSQL_RES* ExecuteQuery(const std::string& full_query);

        std::string DateFormatting(tm* tm_date);
        std::string GetPrevDate(int nday);
        std::string ConvertIntToStr(int number);
};

#endif