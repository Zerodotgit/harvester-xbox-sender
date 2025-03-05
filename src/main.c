#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#include "socket-client.h"
#include "xbox.h"

#define SERVER_PORT 8000
#define BUFFER_SIZE 1024

static volatile int keepRunning = 1;

void sigintHandler(int sig) {
    keepRunning = 0;
}



int main() {

    int x = 1;

    signal(SIGINT, sigintHandler);

    struct libevdev *xbox = NULL;
    xbox = openXboxController(xbox);

    //create socket and connect to server
    int sock = createSocket(SERVER_PORT);

    connectSocket(sock);

    char buffer[BUFFER_SIZE] = "0"; //get message
    char *message = (char *)malloc(BUFFER_SIZE * sizeof(char));   //send message


    if (message == NULL) {
        perror("malloc failed:");
        closeSocket(sock);
        exit(EXIT_FAILURE);
    }

    struct input_event ev;


    while (keepRunning) {

        int rc = libevdev_next_event(xbox, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc == LIBEVDEV_READ_STATUS_SUCCESS) {
            if (ev.code == 17 && ev.value == -1) {
                x = 1;
                printf("前进\n");
            }
            if (ev.code == 17 && ev.value == 1) {
                x = -1;
                printf("后退\n");
            }

            if (ev.code == 9) {
                snprintf(message, BUFFER_SIZE, "%d", ev.value * x);
                printf("ev.value:%d\n", ev.value * x);

                ssize_t bytesSend = send(sock, message, strlen(message), 0);
                if (bytesSend < 0) {
                    perror("Failed to send message:");
                    break;
                }
                printf("Message sent\n");

                ssize_t bytesRead = read(sock, buffer, BUFFER_SIZE - 1);
                if (bytesRead < 0) {
                    perror("Failed to read from server:");
                    break;
                }
                buffer[bytesRead] = '\0';
                printf("Server:%s\n", buffer);
            }
        }


    }

    closeSocket(sock);
    free(message);
    return 0;
}