#ifndef SQLMANAGER_H
#define SQLMANAGER_H
#include <mysql.h>
#include <string.h>

class SQLManager
{    
    public:
        SQLManager();
        virtual ~SQLManager();

        bool Connect();
        void SetTestStock(const std::string& stock_name);
        void SetPrevDate(int nday);
        std::string GetTestStock();

        std::string ExecuteGetStockCode();
        std::string ExecuteGetStockName(const std::string& stock_code);
        
        int ExecuteGetClose(int date);

    private:
        MYSQL m_connect;
        MYSQL_RES* m_result;
        MYSQL_ROW m_row;

        std::string m_stock_name;
        std::string m_stock_code;

        bool m_is_connect;
        bool m_exist_result;
        int m_row_num;
        int m_field_num;

        char** ExecuteQuery(const std::string& full_query);
        std::string ConvertIntToStr(int number);
};

#endif