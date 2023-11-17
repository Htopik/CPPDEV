#include <string>
#include <filesystem>
#include "User.h"
#include "Message.h"
#include <iostream>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

vector <User> RegisteredUsersList;
vector <Message> Messages;

int main() {
	fstream user_file = fstream("users.txt", ios::in | ios::out);
	if (!user_file)
		// Для создания файла используем параметр ios::trunc
		user_file = fstream("users.txt", ios::in | ios::out | ios::trunc);
	fs::permissions("users.txt",
		fs::perms::group_all | fs::perms::others_all,
		fs::perm_options::remove);
	fstream message_file = fstream("messages.txt", ios::in | ios::out);
	if (!message_file)
		// Для создания файла используем параметр ios::trunc
		user_file = fstream("messages.txt", ios::in | ios::out | ios::trunc);
	fs::permissions("messages.txt",
		fs::perms::group_all | fs::perms::others_all,
		fs::perm_options::remove);
	if (user_file) {
		
		User temp;
		while (user_file >> temp)
			RegisteredUsersList.push_back(temp);
		for (int i = 0; i < RegisteredUsersList.size(); ++i)
			cout << RegisteredUsersList[i] << endl;
	}
	else
	{
		cout << "Could not open file users.txt !" << '\n';
		return 0;

	}
	if (message_file) {
		
		Message temp;
		while (message_file >> temp)
			Messages.push_back(temp);
		for (int i = 0; i < Messages.size(); ++i)
			cout << Messages[i] << endl;
	}
	else
	{
		cout << "Could not open file users.txt !" << '\n';
		return 0;

	}
	return 0;
}