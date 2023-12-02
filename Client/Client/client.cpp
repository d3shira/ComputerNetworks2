#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#define SERVER "192.168.238.195"
#define BUFLEN 512
#define PORT 8889

int main()
{

    system("title TCP Client");


    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");


    SOCKET client_socket;
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("socket() failed with error code: %d", WSAGetLastError());
        return 2;
    }


    sockaddr_in server;
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);


    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("connect() failed with error code: %d", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        return 3;
    } 
    
    while (true)
    {
        char message[BUFLEN];
        printf("Enter message: ");
        cin.getline(message, BUFLEN);

        if (send(client_socket, message, strlen(message), 0) == SOCKET_ERROR)
        {
            printf("send() failed with error code: %d", WSAGetLastError());
            closesocket(client_socket);
            WSACleanup();
            return 4;
        }

        char answer[BUFLEN] = {};
        int answer_length;
        if (answer_length = recv(client_socket, answer, BUFLEN, 0) == SOCKET_ERROR)
        {
            printf("recv() failed with error code: %d", WSAGetLastError());
            closesocket(client_socket);
            WSACleanup();
            return 5;
        }

        cout << "Server says: " << answer << "\n";
    }
    closesocket(client_socket);
    WSACleanup();
    return 0;
}
