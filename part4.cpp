#include <iostream>
#include <winsock2.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib") // Link Winsock library

#define PORT 8080 // Server port
#define BUFFER_SIZE 1024 // Max buffer size


void handleClient(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];
    
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0'; 
        std::string receivedData(buffer);
        
        std::cout << "Client: " << receivedData << std::endl;

        std::string response;
        if (receivedData == "PING") {
            response = "PONG\n";
        } else if (receivedData == "EXIT") {
            response = "Goodbye!\n";
            send(clientSocket, response.c_str(), response.size(), 0);
            break; 
        } else {
            response = "Unknown request\n";
        }

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    closesocket(clientSocket);
    std::cout << "Client disconnected.\n";
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);

    // Initializing Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

   
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);


    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    
    listen(serverSocket, SOMAXCONN);
    std::cout << "Server running on port " << PORT << "...\n";

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == INVALID_SOCKET) continue;

        std::cout << "Client connected!\n";
        std::thread(handleClient, clientSocket).detach(); 
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
