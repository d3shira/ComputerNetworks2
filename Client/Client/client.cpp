#pragma warning(disable: 4996)

#include <WinSock2.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

SOCKET Connection; // This client's connection to the server

void ClientThread()
{
    char buffer[256]; // Create a buffer to hold messages up to 256 characters
    while (true)
    {
        int bytesReceived = recv(Connection, buffer, sizeof(buffer), NULL); // Receive buffer
        if (bytesReceived <= 0)
        {
            std::cout << "Server disconnected" << std::endl;
            closesocket(Connection);
            return;
        }

        std::cout << buffer << std::endl;
    }
}

int main()
{
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0)
    {
        MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }
    
    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(""); // IP Adresa
    addr.sin_port = htons(); // Porti
    addr.sin_family = AF_INET;
    
    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    
    if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0)
    {
        MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
        return 0; // Failed to Connect
    }

    std::cout << "Connected to server: SERVER_IP_ADDRESS" << std::endl;
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);
    char buffer[256] = "test";
    while (true)
    {
        std::cin.getline(buffer, sizeof(buffer));
        send(Connection, buffer, sizeof(buffer), NULL);
        Sleep(10);
    }
    return 0;
}
