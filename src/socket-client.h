#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

int createSocket(int port);
void connectSocket(int sock);
void closeSocket(int sock);

#endif //SOCKET_CLIENT_H
