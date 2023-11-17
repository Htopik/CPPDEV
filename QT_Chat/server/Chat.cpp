#include "Chat.h"
#include "BadLogin.h"
#include "BadPassword.h"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <string.h>

#include <QString>
#include <QVector>

#define MESSAGE_LENGTH 1024

Chat::Chat() : _users_count(0),
    _activeUser(nullptr),
    _connected(false),
    _database(std::make_shared <DataBase>())
{
}

Chat::~Chat()
{
}

void Chat::createNewUser(const std::string& name, const std::string& login, const std::string& password)
{
    if (isLoginExist(login)) {
        std::cout << "User with login " << login << " is already exists." << std::endl;
        throw BadLogin();
    }
    std::shared_ptr <User> newUser = std::make_shared <User>(name, login, password);
    addUser(newUser);
    setActiveUser(newUser);
    if (_database->hasConnection()) {
        std::string query = "INSERT into users (name, login, password) VALUES ('" + name + "', '" + login + "', '" + password + "');";
        _database->executeQueryWithoutResult(QString::fromStdString(query));
    }

}

void Chat::addUser(const std::shared_ptr<User>& user)
{
    _users.insert(std::make_pair(_users_count++, user));
}

QStringList Chat::getMessages(bool isPrivate, QString login)
{
    QStringList result;
    QString query = "SELECT login, texting, id_receiver FROM message JOIN users ON message.id_sender = users.id "
                    "WHERE %1;";

    if (_database->hasConnection()) {
        if (isPrivate) {
            QString activeUserId, secondUserId;
            std::string idquery = "SELECT id FROM users WHERE login LIKE '" + getActiveUser()->getLogin() + "';";
            QVector<QString> ids = _database->queryResult(QString::fromStdString(idquery));
            activeUserId = ids.at(0);

            QString idqueryq = "SELECT id FROM users WHERE login LIKE '" + login + "';";
            ids = _database->queryResult(idqueryq);
            secondUserId = ids.at(0);

            query = query.arg("(id_receiver = " + secondUserId +
                              ") OR (id_sender = " + secondUserId + ")");
        } else {
            query = query.arg("id_receiver is null");
        }
        result = _database->queryResult(query).toList();
    }

    return result;
}

void Chat::setActiveUser(const std::shared_ptr<User>& user)
{
    _activeUser = user;
}

void Chat::login(std::string login, std::string password)
{
    bool found = isLoginExist(login);
    if (!found)
        throw BadLogin();
    for (auto& it : _users)
    {
        if (it.second->getLogin() == login) {
            if (it.second->getPassword() == password) {
                setActiveUser(it.second);
            }
            else
                throw BadPassword();
        }
    }
}

void Chat::writeToOne(std::string text, std::shared_ptr<User> recipient)
{
    std::shared_ptr <Message> shp_mess = std::make_shared<Message>(text, getActiveUser()->getLogin(),
                                                                  recipient->getLogin());
    recipient->addMessage(shp_mess);
    std::string id_message;
    if (_database->hasConnection()) {
        std::string query = "SELECT id FROM users WHERE login LIKE '" + getActiveUser()->getLogin() + "';";
        QVector<QString> ids = _database->queryResult(QString::fromStdString(query));
        std::string id_sender = ids.at(0).toStdString();

        query = "SELECT id FROM users WHERE login LIKE '" + recipient->getLogin() + "';";
        ids = _database->queryResult(QString::fromStdString(query));
        std::string id_recipient = ids.at(0).toStdString();

        query = "INSERT INTO messages (id_sender, id_receiver, texting) "
                "VALUES (" + id_sender + ", " + id_recipient + ", '" + text + "');";
        _database->executeQueryWithoutResult(QString::fromStdString(query));

        query = "SELECT id FROM messages WHERE id_sender = " + id_sender + " AND id_receiver = " + id_recipient + " AND texting LIKE '" + text + "';";
        ids = _database->queryResult(QString::fromStdString(query));
        id_message = ids.at(0).toStdString();
    }


}

void Chat::writeToAll(const std::string text)
{
    std::shared_ptr <Message> shp_mess;
    for (auto& it : _users)
    {
        if (it.second->getLogin() != getActiveUser()->getLogin())
        {
            shp_mess = std::make_shared<Message>(text, getActiveUser()->getLogin(),
                                                 it.second->getLogin());
            it.second->addMessage(shp_mess);
        }
    }
    if (_database->hasConnection()) {
        std::string query = "SELECT id FROM users WHERE login LIKE '" + getActiveUser()->getLogin() + "';";
        QVector<QString> ids = _database->queryResult(QString::fromStdString(query));
        std::string id_sender = ids.at(0).toStdString();

        query = "INSERT INTO messages (id_sender, id_receiver, texting) "
                "VALUES (" + id_sender + ", null, '" + text + "');";
        _database->executeQueryWithoutResult(QString::fromStdString(query));
    }
}

bool Chat::isLoginExist(const std::string& login)
{
    for (auto& it : _users)
    {
        if (it.second->getLogin() == login)
            return true;
    }
    return false;
}

std::shared_ptr<User> Chat::getActiveUser()
{
    return _activeUser;
}

std::shared_ptr<User> Chat::getUser(const std::string login)
{
    for (auto& it : _users)
        if (it.second->getLogin() == login)
            return it.second;

    return std::make_shared <User>();
}

QStringList Chat::getAllLogins()
{
    QStringList list;
    for (auto& user : _users)
    {
        list.append(QString::fromStdString(user.second->getLogin()));
    }
    return list;
}

std::string Chat::getNameByLogin(const std::string login)
{
    for (auto& user : _users)
    {

        if (user.second->getLogin() == login)
            return user.second->getName();

    }
    std::cout << "Name by " << login << " is not found!\n";
    return "\0";

}

std::string Chat::getLoginByName(const std::string name)
{
    for (auto& user : _users)
    {
        if (user.second->getName() == name)
            return user.second->getLogin();
    }
    std::cout << "Login by " << name << "is not found!\n";
    return "\0";
}

QString Chat::getLoginById(const std::string id)
{
    QString baza = "to All";
    if (atoi(id.c_str()) == 0)
        return baza;
    std::string query = "SELECT login FROM users WHERE id = '" + id + "';";
    QList<QString> ids = _database->queryResult(QString::fromStdString(query));

    if(!ids.isEmpty()){
        return ids[0];
    }
    std::cout << "Login by " << id << "is not found!\n";
    return "\0";
}

bool Chat::createDBConnection(QStringList params)
{
    if (!_database->connect(params.at(0), params.at(1).toInt(), params.at(2), params.at(3), params.at(4))){

        std::cout << "Database connection is absent!";
        return 0;
    }
    else
        getUsersFromDB();
    return 1;
}

void Chat::getUsersFromDB()
{
    if (!_database->hasConnection()) {
        return;
    }

    std::string name, login, password;
    QVector<QString> userslist = _database->queryResult("SELECT id, name, login, password FROM users;");

    int start = 0, messagesStart = 0;
    std::shared_ptr <User> newUser;
    std::shared_ptr <Message> newMessage;

    while (start < userslist.size()) {
        newUser = std::make_shared <User>(userslist.at(start+1).toStdString(), userslist.at(start+2).toStdString(), userslist.at(start+3).toStdString());
        std::string text = "SELECT message.id, texting, id_sender FROM message join users on id_sender = users.id where id_receiver = " +
                           userslist.at(start).toStdString() + ";";

        QVector<QString> messages = _database->queryResult(QString::fromStdString(text));
        messagesStart = 0;
        while (messagesStart < messages.size()) {
            newMessage = std::make_shared <Message>(messages.at(messagesStart).toStdString(), messages.at(messagesStart + 1).toStdString(), messages.at(messagesStart + 2).toStdString(),
                                                   newUser->getLogin());
            newUser->addMessage(newMessage);
            messagesStart += 4;
        }

        addUser(newUser);
        start += 4;
    }
    std::cout << "Data was succesfully gotten from database" << std::endl;
}


void Chat::banUser(const std::string name){
    _database->queryResult(QString::fromStdString( std::string("update users set banned='T' where login='") + name + "'"));
    std::cout << name + " was banned" << std::endl;
}

void Chat::unBanUser(const std::string name){
    _database->queryResult(QString::fromStdString( std::string("update users set banned='F' where login='") + name + "'"));
    std::cout << name + " was unbanned" << std::endl;
}

void Chat::disableUser(const std::string name){
    _database->queryResult(QString::fromStdString( std::string("update users set disabled='T' where login='") + name + "'"));
    std::cout << name + " was disabled" << std::endl;
}

void Chat::enableUser(const std::string name){
    _database->queryResult(QString::fromStdString( std::string("update users set disabled='F' where login='") + name + "'"));
    std::cout << name + " was enabled" << std::endl;
}
