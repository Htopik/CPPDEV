#pragma once
#include "User.h"
//#include <istream>

class Message {
private:
	string text;
	User* user;
	string userLog;
public:
	Message() = default;
	Message(const string& text, User* user);
	Message(const string& text, const string& userLog);
	string getMessage();
	User* getUser();
	void setUser(vector<User>& Users);

	friend istream& operator >>(istream& is, Message& obj);
	friend ostream& operator <<(ostream& os, const Message& obj);
};