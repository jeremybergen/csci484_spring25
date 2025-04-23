#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFSIZE 1024

int main(int argc, char** argv)
{
    int serverSocket;
    int clientSocket;
    int yes = 1;
    // struct sockaddr_in address;
    struct addrinfo hints, *res;
    struct sockaddr_storage address;
    int bindStatus;
    int listenStatus;
    int addrsize = sizeof(struct sockaddr_storage);
    // int serverSocket2;


    // printf("Socket2: %d\n", serverSocket2);

    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(1234);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "1234", &hints, &res);
    // serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // serverSocket2 = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    printf("Socket: %d\n", serverSocket);

    // bindStatus = bind(serverSocket, (struct sockaddr*) &address, sizeof(address));
    bindStatus = bind(serverSocket, res->ai_addr, res->ai_addrlen);

    printf("bindStatus: %d\n", bindStatus);

    listenStatus = listen(serverSocket, 5);
    printf("listenStatus: %d\n", listenStatus);

    clientSocket = accept(serverSocket, (struct sockaddr *) &address, (socklen_t *)&addrsize);
    printf("clientSocket: %d\n", clientSocket);

    char buffer[BUFFSIZE] = {0};
    ssize_t recvBytes = recv(clientSocket, buffer, BUFFSIZE, 0);
    printf("Received: %s\n", buffer);

    send(clientSocket, buffer, recvBytes, 0);
    // while(1)
    // {

    // }

    return 0;
}