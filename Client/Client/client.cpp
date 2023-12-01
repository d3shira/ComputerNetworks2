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
    return 0;
}
