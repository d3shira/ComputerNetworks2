#pragma warning(disable: 4996)

#include <WinSock2.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

SOCKET Connections[100];
int ConnectionCounter = 0;

void ClientHandlerThread(int index)
{
    char buffer[256];
    while (true)
    {
        int bytesReceived = recv(Connections[index], buffer, sizeof(buffer), NULL);
        if (bytesReceived <= 0)
        {
            std::cout << "Client disconnected" << std::endl;
            closesocket(Connections[index]);
            return;
        }

        std::string ClientName = "Client > ";
        std::string Format = buffer;
        std::string Final = ClientName + Format;

        std::cout << Final.c_str() << std::endl;

        for (int i = 0; i < ConnectionCounter; i++)
        {
            if (i == index)
                continue;
            send(Connections[i], buffer, sizeof(buffer), NULL);
        }
    }
}

int main() {

}