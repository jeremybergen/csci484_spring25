#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int argc, char** argv)
{
    int clientSocket;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(1234);
    // address.sin_addr = 
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    int connectStatus = connect(clientSocket, (struct sockaddr*)&address, sizeof(address));
    printf("connectStatus: %d\n", connectStatus);

    char buffer[BUFFSIZE] = {0};
    read(0, buffer, BUFFSIZE);
    send(clientSocket, buffer, strlen(buffer), 0);

    memset(buffer, 0, strlen(buffer));
    recv(clientSocket, buffer, BUFFSIZE, 0);
    printf("Received: %s\n", buffer);


    return 0;
}