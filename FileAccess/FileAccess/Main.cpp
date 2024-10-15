#include <string>
#include <filesystem>

#include <vector>
#include "Message.h"
using namespace std;
namespace fs = std::filesystem;

vector <User> RegisteredUsersList;
vector <Message> Messages;

int main() {
	if (!fs::exists("./logs/"))
		fs::create_directories("./logs/");
	if (!fs::exists("./logs/users"))
	{
		fstream user_file("./logs/users", std::ios::app);
		if (!user_file.is_open()) 
		{
			cout << "Could not open file users.txt !" << '\n';
			return 0;

		}
		user_ = new User<std::string, std::vector<std::string>>{ "ChatBot",
			user_->HashPassword("ChatBot", "qwerty"), "Бот", true };
		file << CONVERT_IN(user_->login_ + " " + user_->get_password() +
			" " + user_->name_);
		file.close();
		users_.push_back(*user_);
	}
	else
	{
		U_IFSTREAM file("./logs/users");
		file.LOCALE;
		if (!file.is_open()) ATTENTION;
		U_STRING login, password, name;
		user_ = new User<std::string, std::vector<std::string>>{};
		while (!file.eof())
		{
			file >> login >> password >> name;
			user_->login_ = CONVERT_OUT(login);
			user_->set_password(CONVERT_OUT(password));
			user_->name_ = CONVERT_OUT(name);
			user_->online_ = false;
			users_.push_back(*user_);
		}
		file.close();
		users_[0].online_ = true;
	}
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