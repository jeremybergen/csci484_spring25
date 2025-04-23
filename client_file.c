#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
    recv(clientSocket, buffer, 1024, 0);
    printf("file size: %s\n", buffer);

    ssize_t filesize = atol(buffer);
    char* fileBuff;
    fileBuff = (char *)malloc(filesize * sizeof(char));
    memset(fileBuff, 0, filesize);
    // read(0, buffer, BUFFSIZE);
    // send(clientSocket, buffer, strlen(buffer), 0);

    send(clientSocket, "Recv", strlen("Recv"), 0);

    // memset(buffer, 0, strlen(buffer));
    recv(clientSocket, fileBuff, filesize, 0);
    // printf("Received: %s\n", buffer);
    printf("Received file\n");

    FILE* file;
    file = fopen("clientFile", "wb");

    fwrite(fileBuff, 1, filesize, file);
    fclose(file);
    free(fileBuff);
    return 0;
}