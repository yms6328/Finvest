#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H
#include <string>
#include <mysql.h>

class QueryManager
{
    protected:
        MYSQL *m_connection;
        MYSQL_RES *m_result;
        MYSQL_ROW m_row;

    public:
        QueryManager();
        void DB_Connect();
        std::string ExecuteGetNameQuery(const std::string& code);
        std::string ExecuteGetCodeQuery(const std::string& name);

    private:
        char* execute(const std::string& full_query);
};
#endif