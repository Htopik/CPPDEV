#include <stdlib.h>
#include <cstring>
#ifdef _WIN64
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#elif __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "mysql.h"
#include "Logger.h"
using namespace std;
#define MESSAGE_BUFFER 4096 // Максимальный размер буфера для приема и передачи
#define PORT 7777 // Номер порта, который будем использовать для приема и передачи 

static vector <User> RegisteredUsersList; //Список зарегистрированных на сервере пользователей.
static vector <Message> Messages; //Список сообщений на сервере.
static vector <struct sockaddr_in> LoginUsersList; //Список адресов залогинившихся пользователей.
static vector <bool> isLoggedList; 
MYSQL mysql; // Дескриптор соединения c MySql

Logger logger;

char buffer[MESSAGE_BUFFER]; 
char message[MESSAGE_BUFFER];
int socket_file_descriptor, message_size;
socklen_t length;
struct sockaddr_in serveraddress, client;

void setStr(char* src, char* to, int srclen){
	for(int i  = 0;i < srclen;i++){
		to[i] = src[i]; 
	}
}

void sendMessage(char* msg, string name){
    string send;
    send += '<';
    send += name;
    send += '>';
    send += ' ';
    send += msg;
    char sendChar[MESSAGE_BUFFER];
    strcpy(sendChar, send.c_str());
    for (int i = 0; i < LoginUsersList.size(); ++i) {
        struct sockaddr_in to;
        to = LoginUsersList[i];
        if(isLoggedList[i]) sendto(socket_file_descriptor, sendChar, MESSAGE_BUFFER, 0, (struct sockaddr*)&to, sizeof(to));   
    }
}

int reg(){
    char separator = '_';
    int i = 0;
    int arg = 0;
    string args[4];

    string s; 
    while (buffer[i] != '\0') {
        if (buffer[i] != separator) {
            s += buffer[i]; 
        } else {
            if(arg == 3) return -3;
            args[arg] = s;
            arg++;
            s.clear();
        }
        i++;
    }
    args[arg] = s;
    s.clear();
    if(arg != 3) return -3;

    string log = args[1];
    string pas = args[2];
    string nam = args[3];
    cout << log << '\n';
    cout << pas << '\n';
    cout << nam << '\n';

    int indexOfUser;
    if(User::isUserExist(RegisteredUsersList, log)){
        return -1;
    }
    User New(log, pas, nam);

    struct sockaddr_in NewSockaddr;
    mysql_query(&mysql, ("INSERT INTO users (user_id, login, password, name) values(default, '" + log + "', '" + pas + "', '" + nam + "')").c_str()); 
    //Добавление нового пользователя в БД
    RegisteredUsersList.push_back(New);
    LoginUsersList.push_back(NewSockaddr);
    isLoggedList.push_back(false);

    indexOfUser = User::checkUser(RegisteredUsersList, log, pas);
    return indexOfUser;
}

int login(){
	char separator = '_';
    int i = 0;
    int arg = 0;
    string args[3];

    string s; 
    while (buffer[i] != '\0') {
        if (buffer[i] != separator) {
            s += buffer[i]; 
        } else {
        	if(arg == 2) return -3;
            args[arg] = s;
            arg++;
            s.clear();
        }
        i++;
    }
    args[arg] = s;
    s.clear();
    if(arg != 2) return -3;

    string log = args[1];
    string pas = args[2];
    cout << log << '\n';

	int indexOfUser;
	if(!User::isUserExist(RegisteredUsersList, log)){
		return -1;
	}
	indexOfUser = User::checkUser(RegisteredUsersList, log, pas);
	if (indexOfUser == -1) {
		return -2;
	}
    LoginUsersList[indexOfUser] = client;
    isLoggedList[indexOfUser] = true;
	return indexOfUser;
}

void request(){
	char outMsg1[] = "Command not found!";
	char outMsg2[] = "Command error!";
	char outMsg3[] = "User not exists!";
	char outMsg4[] = "Wrong password!";
	char outMsg5[] = "Ex. /login_[login]_[password]";
    char outMsg6[] = "This login is already taken!";
    char outMsg7[] = "Ex. /register_[login]_[password]_[name]";

	length = sizeof(client);
    message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
    if (message_size == SOCKET_ERROR) {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
    }
    buffer[message_size] = '\0';
    
    if(buffer[0] == '/'){
    	int answ = 0;
    	bool truecmd = true;

    	char logincmd[] = "login";
    	int logincmdln = 5;
        char regcmd[] = "register";
        int regcmdln = 8;

    	for(int i = 1;i < logincmdln + 1;i++){
    		if(buffer[i] != logincmd[i - 1]) truecmd = false;
    	}
    	if(truecmd){
    		answ = login();
    		if(answ == -1){
	    		setStr(outMsg3, message, sizeof(outMsg3) / sizeof(outMsg3[0]));
    		}else if(answ == -2){
	    		setStr(outMsg4, message, sizeof(outMsg4) / sizeof(outMsg4[0]));
    		}else if(answ == -3){
	    		setStr(outMsg5, message, sizeof(outMsg5) / sizeof(outMsg5[0]));
    		}else if(answ < 0){
	    		setStr(outMsg2, message, sizeof(outMsg2) / sizeof(outMsg2[0]));
    		}

    		sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
    		return;
    	}

        answ = 0;
        truecmd = true;

        for(int i = 1;i < regcmdln + 1;i++){
            if(buffer[i] != regcmd[i - 1]) truecmd = false;
        }
        if(truecmd){
            answ = reg();
            if(answ == -1){
                setStr(outMsg6, message, sizeof(outMsg6) / sizeof(outMsg6[0]));
            }else if(answ == -3){
                setStr(outMsg7, message, sizeof(outMsg7) / sizeof(outMsg7[0]));
            }else if(answ < 0){
                setStr(outMsg2, message, sizeof(outMsg2) / sizeof(outMsg2[0]));
            }

            sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
            return;
        }

    	setStr(outMsg1, message, sizeof(outMsg1) / sizeof(outMsg1[0]));
		sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
        return;
    }else{
        string username = "";
        string login = "";
        MYSQL_RES* res;
        MYSQL_ROW row;
        char* mes = new char[message_size + 1];
        strcpy(mes, buffer);
        for (int i = 0; i < LoginUsersList.size(); ++i) {
            if(client.sin_addr.s_addr == LoginUsersList[i].sin_addr.s_addr && client.sin_port == LoginUsersList[i].sin_port){
                username = RegisteredUsersList[i].getName();
                login = RegisteredUsersList[i].getLogin();
            }
        }
        mysql_query(&mysql, ("SELECT user_id FROM users where login='" + login+"'").c_str()); //Получение ID по логину
        res = mysql_store_result(&mysql);
        row = mysql_fetch_row(res);//содержит user_id
        mysql_query(&mysql, ("INSERT INTO message(message_id, user_id, text) values(default, "+(string)row[0]+", '" + mes + "')").c_str()); 
        //Добавление нового сообщения в БД
        sendMessage(buffer, username);
        return;
    }

    sendto(socket_file_descriptor, buffer, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
}

void dbconnect() {
    MYSQL_RES* res;
    MYSQL_ROW row;
    string voidd = "";
    mysql_query(&mysql, "SHOW TABLES LIKE 'users'"); //Делаем запрос к таблице
    if (res = mysql_store_result(&mysql)) {
        if (!(row = mysql_fetch_row(res))) { //Если таблицы не существует, создать
            mysql_query(&mysql, ("CREATE TABLE `users` (" + voidd +
                "`user_id` int NOT NULL AUTO_INCREMENT," +
                "`login` varchar(45) NOT NULL," +
                "`password` varchar(45) NOT NULL," +
                "`name` varchar(45) NOT NULL," +
                "PRIMARY KEY(`user_id`)," +
                "UNIQUE KEY `login_UNIQUE` (`login`)" +
                ")").c_str());
        }
        mysql_query(&mysql, "SELECT * FROM users"); //Делаем запрос к таблице

        //Записываем в локальные переменные все что есть в таблице через цикл
        if (res = mysql_store_result(&mysql)) {
            while (row = mysql_fetch_row(res)) {
                string log = row[1];
                string pas = row[2];
                string nam = row[3];
                User New(log, pas, nam);
                struct sockaddr_in NewSockaddr;
                RegisteredUsersList.push_back(New);
                LoginUsersList.push_back(NewSockaddr);
                isLoggedList.push_back(false);
            }
        }

    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&mysql);
    mysql_query(&mysql, "SHOW TABLES LIKE 'message'"); //Делаем запрос к таблице
    if (res = mysql_store_result(&mysql)) {
        if (!(row = mysql_fetch_row(res))) { //Если таблицы не существует, создать
            mysql_query(&mysql, ("CREATE TABLE `message` (" + voidd +
                "`message_id` int NOT NULL AUTO_INCREMENT," +
                "`user_id` int NOT NULL," +
                "`text` varchar(45) NOT NULL," +
                "PRIMARY KEY(`message_id`)," +
                "KEY `user_id_idx` (`user_id`)," +
                "CONSTRAINT `user_id` FOREIGN KEY(`user_id`) REFERENCES `users` (`user_id`)" +
                ")").c_str());
        }
        mysql_query(&mysql, "SELECT * FROM message"); //Делаем запрос к таблице

        //Записываем в локальные переменные все что есть в таблице через цикл
        if (res = mysql_store_result(&mysql)) {
            while (row = mysql_fetch_row(res)) {
                string user_id = row[1];
                string message = row[2];
                mysql_query(&mysql, ("SELECT login FROM users where user_id=" + user_id).c_str()); //Получение логина по ID
                res = mysql_store_result(&mysql);
                row = mysql_fetch_row(res);//содержит login
                string log = row[1];
                User us;
                Message New_Mes(message, us.getUserByLogin(RegisteredUsersList, log));
                Messages.push_back(New_Mes);
            }
        }
    }
    else
        cout << "Ошибка MySql номер " << mysql_error(&mysql);
}

void startChat() {
#ifdef _WIN64
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: \n" << iResult << std::endl;
        return;
    }
#endif
    mysql_init(&mysql);

    if (&mysql == NULL) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        cout << "Error: can't create MySQL-descriptor" << endl;
    }
    string root = "root", pass = "210303", dbname = "chatbd";
    int port = 3306;
    /*cout << "Please, tell the name of user (root)";
    cin >> root;
    cout << "Please, tell the password of user";
    cin >> pass;
    cout << "Please, tell the name of your database (schema)";
    cin >> pass;
    cout << "Please, tell the port";
    cin >> port;*/
    // Подключаемся к серверу
    if (!mysql_real_connect(&mysql, "localhost", root.c_str(), pass.c_str(), dbname.c_str(), port, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    }
    else {
        // Если соединение успешно установлено выводим фразу — "Success!"
        cout << "Success!" << endl;
    }
    mysql_set_character_set(&mysql, "utf8");
    //Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
    cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
    
    
	//cout << " Welcome to our chat, wanderer! Please, sign/log in because you are the first today!\n";
	socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    std::memset(&serveraddress, 0, sizeof(serveraddress));
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим порт для соединения
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет 
    if (bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) == -1) {
        std::cerr << "Failed to bind socket to address\n";
        return;
    }
    dbconnect();
    logger.outString("Chat Started!");
    while (true) request();
    logger.outString("Chat Closed!");
#ifdef _WIN64
    closesocket(socket_file_descriptor);
#else
    close(socket_descriptor);
#endif
#ifdef _WIN64
    WSACleanup();
#endif
    // Закрываем соединение с базой данных
    mysql_close(&mysql);
}

int main() {
	setlocale(LC_ALL, "");

	startChat();
	
	return 0;
}