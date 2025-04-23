#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    int serverSocket, clientSocket;
    struct addrinfo hints, *res;
    struct sockaddr_storage clientStor;
    int yes = 1;
    int addrsize = sizeof(struct sockaddr_storage);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, "1234", &hints, &res);

    serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    bind(serverSocket, res->ai_addr, res->ai_addrlen);
    listen(serverSocket, 1);

    while(1)
    {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientStor, (socklen_t*)&addrsize);

        FILE *file;
        char *buffer;
        char msgBuffer[1024] = {0};
        long filesize;

        file = fopen("a.out", "rb");

        if(file == NULL)
        {
            printf("Error opening file\n");
            return 1;
        }
        fseek(file, 0, SEEK_END);
        filesize = ftell(file);
        rewind(file);

        buffer = (char *)malloc(filesize * sizeof(char));

        fread(buffer, sizeof(char), filesize, file);

        printf("Sending file\n");
        sprintf(msgBuffer, "%ld", filesize);
        send(clientSocket, msgBuffer, strlen(msgBuffer), 0);
        memset(msgBuffer, 0, strlen(msgBuffer));
        memset(msgBuffer, 0, strlen(msgBuffer));


        recv(clientSocket, msgBuffer, 1024, 0);
        printf("Ack filesize: %s\n", msgBuffer);
        memset(msgBuffer, 0, strlen(msgBuffer));

        send(clientSocket, buffer, filesize, 0);
        int recvBytes = recv(clientSocket, msgBuffer, 1024, 0);
        printf("%s\n", msgBuffer);
        memset(msgBuffer, 0, recvBytes);

        free(buffer);
        fclose(file);
    }

    return 0;
}