#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <map>
#include "User.h"
#include "Message.h"
#include "DataBase.h"

#include <QStringList>

class Chat
{
private:
    std::map<int, std::shared_ptr <User>> _users;
    int _users_count;
    std::shared_ptr <User> _activeUser;
    int client_socket_file_descriptor, server_socket_file_descriptor;
    bool _connected;
    std::shared_ptr<DataBase> _database;


    void addUser(const std::shared_ptr<User>& user);

public:
    Chat();
    ~Chat();

    void createNewUser(const std::string& name, const std::string& login, const std::string& password);
    void setActiveUser(const std::shared_ptr<User>& user);
    void login(std::string login, std::string password);
    void writeToOne(std::string text, std::shared_ptr<User>);
    void writeToAll(const std::string text);
    bool isLoginExist(const std::string& login);
    std::shared_ptr <User> getActiveUser();
    std::shared_ptr <User> getUser(const std::string login);
    QStringList getAllLogins();
    std::string getNameByLogin(const std::string login);
    std::string getLoginByName(const std::string name);
    QString getLoginById(const std::string );
    bool createDBConnection(QStringList params);
    void getUsersFromDB();
    void updateUnreadedMessages();
    QStringList getMessages(bool isPrivate, QString login = "");
    void banUser(const std::string name);
    void unBanUser(const std::string name);
    void disableUser(const std::string name);
    void enableUser(const std::string name);
};
