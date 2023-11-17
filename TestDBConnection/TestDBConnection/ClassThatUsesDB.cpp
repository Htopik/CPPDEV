#include <iostream>
#include <cstddef>
#include "ClassThatUsesDB.h"

ClassThatUsesDB::ClassThatUsesDB(DBConnectionInterface* connection) :_connection(connection)
{
}

ClassThatUsesDB::~ClassThatUsesDB()
{
    closeConnection();
}

bool ClassThatUsesDB::openConnection()
{
    return _connection->open();
}

void ClassThatUsesDB::useConnection()
{
    MYSQL_RES* res = _connection->execQuery("select user_id, login from users");
    if (res)
    {
        MYSQL_ROW row;
        size_t size = mysql_num_fields(res);

        while (row = mysql_fetch_row(res))
        {
            for (size_t i = 0; i < size; ++i)
            {
                std::cout << row[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void ClassThatUsesDB::closeConnection()
{
    _connection->close();
}
