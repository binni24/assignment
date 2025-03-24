#include <iostream>
#include <winsock2.h>  
#include <string>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);  

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);  

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);  

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));  // Bind socket
    listen(serverSocket, 5);  

    std::cout << "Server is running on port 8080...\n";

    while (true) {  
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        
        std::cout << "Client connected!\n";

        while (true) {  
            char buffer[1024] = {0};
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                std::cout << "Client disconnected.\n";  
                break;  
            }

            
            std::string receivedData(buffer);
            receivedData.erase(receivedData.find_last_not_of("\r\n") + 1);

            std::cout << "Received: " << receivedData << "\n";  // Debugging

            if (receivedData == "PING") {
                send(clientSocket, "PONG\n", 5, 0);  // response
            } else if (receivedData == "EXIT") {
                send(clientSocket, "Goodbye!\n", 9, 0);
                break;  
            } else {
                send(clientSocket, "Unknown request\n", 16, 0);
            }
        }

        closesocket(clientSocket);  
    }

    closesocket(serverSocket);
    WSACleanup();  // Cleanup Winsock
    return 0;
}
