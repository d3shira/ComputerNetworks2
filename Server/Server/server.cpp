#include <WinSock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable : 4996)

#define BUFLEN 512
#define PORT 8889

void writeFile(const string& filename, const string& content)
{
    ofstream file(filename, ios::out | ios::binary);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
    else
    {
        cout << "Error opening file: " << filename << endl;
    }
}
void appendFile(const string& filename, const string& content)
{
    ofstream file(filename, ios::out | ios::app | ios::binary);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
    else
    {
        cout << "Error opening file: " << filename << endl;
    }
}

string readFile(const string& filename)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return content;
    }
    else
    {
        cout << "Error opening file: " << filename << endl;
        return "";
    }
}
void deleteFile(const string& filename)
{
    if (remove(filename.c_str()) != 0)
    {
        cout << "Error deleting file: " << filename << endl;
    }
    else
    {
        cout << "File deleted successfully: " << filename << endl;
    }
}

void handleClient(SOCKET client_socket, sockaddr_in clientAddr, unordered_set<string>& allowedWriteClients)
{
    char message[BUFLEN] = {};

    while (true)
    {
        int message_len = recv(client_socket, message, BUFLEN, 0);
        if (message_len == SOCKET_ERROR)
        {
            cout << "recv() failed with error code: " << WSAGetLastError() << endl;
            closesocket(client_socket);
            break;
        }
        else if (message_len == 0)
        {
            cout << "Connection closed by " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
            closesocket(client_socket);
            break;
        }

        string clientKey = string(inet_ntoa(clientAddr.sin_addr)) + ":" + to_string(ntohs(clientAddr.sin_port));

        if (strncmp(message, "file r: ", 8) == 0)
        {
            string filename = message + 8;
            
            string fileContent = readFile(filename);

            send(client_socket, fileContent.c_str(), fileContent.size(), 0);
        }
        else if (strncmp(message, "file w: ", 8) == 0)
        {
            if (allowedWriteClients.empty() || allowedWriteClients.count(clientKey) > 0)
            {
                string fileWriteCommand = message + 8;
                size_t pos = fileWriteCommand.find(' ');
                if (pos != string::npos)
                {
                    string filename = fileWriteCommand.substr(0, pos);
                    string content = fileWriteCommand.substr(pos + 1);

                    writeFile(filename, content);

                    string successMsg = "Content written to file: " + filename;
                    send(client_socket, successMsg.c_str(), successMsg.size(), 0);

                    allowedWriteClients.insert(clientKey);
                }
            }
            else
            {
                string errorMsg = "Write operation not allowed for this client";
                send(client_socket, errorMsg.c_str(), errorMsg.size(), 0);
            }
        }
        else if (strncmp(message, "file a: ", 8) == 0)
        {
            if (allowedWriteClients.empty() || allowedWriteClients.count(clientKey) > 0)
            {
               
                string fileAppendCommand = message + 8;
                size_t pos = fileAppendCommand.find(' ');
                if (pos != string::npos)
                {
                    string filename = fileAppendCommand.substr(0, pos);
                    string content = fileAppendCommand.substr(pos + 1);

                   
                    appendFile(filename, content);

                   
                    string successMsg = "Content appended to file: " + filename;
                    send(client_socket, successMsg.c_str(), successMsg.size(), 0);

                    allowedWriteClients.insert(clientKey); // Mark that this client is allowed to write
                }
            }
            else
            {
               
                string errorMsg = "Append operation not allowed for this client";
                send(client_socket, errorMsg.c_str(), errorMsg.size(), 0);
            }
        }
        else if (strncmp(message, "file d: ", 8) == 0)
        {
            if (allowedWriteClients.empty() || allowedWriteClients.count(clientKey) > 0)
            {
                
                string filename = message + 8;

                
                deleteFile(filename);

                
                string successMsg = "File deleted: " + filename;
                send(client_socket, successMsg.c_str(), successMsg.size(), 0);

                allowedWriteClients.insert(clientKey); // Mark that this client is allowed to write
            }
            else
            {
               
                string errorMsg = "Delete operation not allowed for this client";
                send(client_socket, errorMsg.c_str(), errorMsg.size(), 0);
            }
        }
        else
        {
            printf("Client says: %s\n", message);

            char serverMessage[BUFLEN];
            printf("Enter message to client: ");
            cin.getline(serverMessage, BUFLEN);

            send(client_socket, serverMessage, strlen(serverMessage), 0);
        }


        memset(message, 0, BUFLEN);
    }
}
int main() {
   
      system("title TCP Server");

    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");

    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.178.28");               

    if (server.sin_addr.s_addr == INADDR_NONE) {
        printf("Invalid IP address: %s", "192.168.178.28");             
        exit(EXIT_FAILURE);
    }
    server.sin_port = htons(PORT);

    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done.");

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Listen failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Waiting for incoming connections...");

    unordered_set<string> allowedWriteClients;

    while (true)
    {
        SOCKET client_socket;
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);

        client_socket = accept(server_socket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (client_socket == INVALID_SOCKET)
        {
            printf("Accept failed with error code: %d", WSAGetLastError());
            closesocket(server_socket);
            WSACleanup();
            exit(EXIT_FAILURE);
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        thread clientThread(handleClient, client_socket, clientAddr, ref(allowedWriteClients));
        clientThread.detach(); 
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}

