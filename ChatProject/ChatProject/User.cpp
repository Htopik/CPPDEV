#include "User.h"

User::User(const string& log, const string& pass, const string& nam) : login(log), name(nam), password(pass) {}

string User::getLogin() {
	return this->login;
}

string User::getPassword() {
	return this->password;
}

string User::getName() {
	return this->name;
}

void User::setAdmin(bool isAdmin) {
	this->permission = isAdmin;
}

bool User::isAdmin() {
	return permission == 1;
}

bool User::isUserExist(vector<User> Users, string log) {
	for (int i = 0; i < Users.size(); ++i) {
		if (Users[i].getLogin() == log)
			return true;
	}
	return false;
}

int User::checkUser(vector<User> Users, string log, string pass) {
	for (int i = 0; i < Users.size(); ++i) {
		if (Users[i].getLogin() == log && Users[i].getPassword() == pass)
			return i;
	}
	return -1;
}

int User::getIndexByName(vector<User> Users, string nameOfAddressee) {
	for (int i = 0; i < Users.size(); ++i) {
		if (Users[i].getName() == nameOfAddressee)
			return i;
	}
	return -1;
}

int User::getIndexByLogin(vector<User> Users, string loginOfAddressee) {
	for (int i = 0; i < Users.size(); ++i) {
		if (Users[i].getLogin() == loginOfAddressee)
			return i;
	}
	return -1;
}

User* User::getUserByLogin(vector<User> Users, string login) {
	for (int i = 0; i < Users.size(); ++i) {
		if (Users[i].getLogin() == login)
			return &Users[i];
	}
	return nullptr;
}

istream& operator >>(istream& is, User& obj)
{
	is >> obj.name;
	is >> obj.login;
	is >> obj.password;
	return is;
}
ostream& operator <<(ostream& os, const User& obj)
{
	os << obj.name;
	os << ' ';
	os << obj.login;
	os << ' ';
	os << obj.password;
	return os;
}