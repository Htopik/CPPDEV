#pragma once
#include <string>
#include <fstream>
using namespace std;

class User {
    string _name;
    string _login;
    string _pass;
public:
    User();
    User(string name, string login, string pass) :_name(name), _login(login), _pass(pass) {}

    friend fstream& operator >>(fstream& is, User& obj);
    friend ostream& operator <<(ostream& os, const User& obj);
};
