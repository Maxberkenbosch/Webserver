#include "server.hpp"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    long valread;
    long newSocket;
    Server server;  
    char *hello = strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
    
    server.setUpServer();
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        newSocket = server.acceptSocket();

        char buffer[30000] = {0};
        valread = read( newSocket , buffer, 30000);
        printf("%s\n",buffer );
        write(newSocket, hello, strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(newSocket);
    }
    return 0;
}