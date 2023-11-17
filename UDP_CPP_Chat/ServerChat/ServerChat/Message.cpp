#include "Message.h"


Message::Message(const string& text, User* user) : text(text), user(user) {}
Message::Message(const string& text, const string& userLog) : text(text), userLog(userLog) {}

string Message::getMessage() {
	return this->text;
}

User* Message::getUser() {
	return this->user;
}

void Message::setUser(vector<User>& Users) {
	int indexOfUser = User::getIndexByLogin(Users, userLog);
	this->user = &Users[indexOfUser];
}

istream& operator >>(istream& is, Message& obj)
{
	is >> obj.userLog;
	int size;
	is >> size;
	char *str = new char[size];
	is.get();
	is.get(str, size);
	obj.text.assign(str, size);
	delete[] str;
	return is;
}
ostream& operator <<(ostream& os, const Message& obj)
{
	os << obj.user->getLogin();
	os << ' ';
	os << obj.text.size();
	os << ' ';
	os << obj.text;
	return os;
}