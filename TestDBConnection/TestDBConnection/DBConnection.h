#pragma once
#include "mysql.h"
#include <string>

class DBConnectionInterface
{
public:
    DBConnectionInterface();
    virtual ~DBConnectionInterface();

    virtual bool open() = 0;
    virtual void close() = 0;
    virtual MYSQL_RES* execQuery(const std::string&) = 0;
};

class DBConnection : public DBConnectionInterface
{
private:
    MYSQL* _mysql;
    const char* _host;
    const char* _userName;
    const char* _password;
    const char* _dbName;
    const int _port;
    const int _flag;
    bool _opened;

public:
    DBConnection(const std::string&, const std::string&, const std::string&, const std::string&, const int, const int);
    ~DBConnection();

    bool open() override;
    void close() override;
    MYSQL_RES* execQuery(const std::string&) override;

};

