#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <thread>
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

using namespace std;


// ћаксимальный размер буфера дл€ приема и передачи
#define MESSAGE_BUFFER 4096
#define PORT 7777 // номер порта, который будем использовать дл€ приема и передачи 


char buffer[MESSAGE_BUFFER];
char message[MESSAGE_BUFFER];
string mes;
int socket_descriptor;
struct sockaddr_in serveraddress;

void request() {
    while (true) {
        recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
        cout << "Message Received From Server: " << endl;
        cout << buffer << endl;
    }
}

void sendRequest() {
#ifdef _WIN64
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return;
    }
#endif
    
    std::memset(&serveraddress, 0, sizeof(serveraddress));
    
    // «ададим номер порта дл€ соединени€ с сервером
    serveraddress.sin_port = htons(PORT);
    // »спользуем IPv4
    serveraddress.sin_family = AF_INET;
    // ”кажем адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_pton(AF_INET, "192.168.1.136", &serveraddress.sin_addr);
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    // ”становим соединение с сервером
    if (connect(socket_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) < 0) {
        cout << endl << " Something went wrong Connection Failed" << endl;
        exit(1);
    }

    thread t(request);
    t.detach();

    while (1) {
        cin >> mes;
        if (message == "/end") {
            sendto(socket_descriptor, mes.c_str(), mes.size(), 0, nullptr, sizeof(serveraddress));
            cout << "Client work is done!" << endl;
#ifdef _WIN64
            closesocket(socket_descriptor);
#else
            close(socket_descriptor);
#endif
            exit(0);
        }
        else {
            sendto(socket_descriptor, mes.c_str(), mes.size(), 0, nullptr, sizeof(serveraddress));
        }
    }
    // closing socket, ending connection
#ifdef _WIN64
    closesocket(socket_descriptor);
#else
    close(socket_descriptor);
#endif
#ifdef _WIN64
    WSACleanup();
#endif
}

int main() {
    cout << "CLIENT IS ESTABLISHING A CONNECTION WITH SERVER THROUGH PORT: " << PORT << endl;
    sendRequest();
    return 0;
}