#include "socket-client.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"

struct sockaddr_in serverAddr;

//create sock
int createSocket(int port) {
    int sock;

    printf("Creating socket...\n");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket:");
        exit(EXIT_FAILURE);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    printf("Socket created.\n");

    //convert IPv4 to binary
    printf("Converting IPv4 to binary\n");
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("Failed to convert IP address:");
        exit(EXIT_FAILURE);
    }
    printf("Converted\n");

    return sock;
}

//connect to server
void connectSocket(int sock) {
    printf("Connecting to server...\n");
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Failed to connect to server:");
        exit(EXIT_FAILURE);
    }
    printf("Server connected.\n");
}

//close socket
void closeSocket(int sock) {
    close(sock);
}


