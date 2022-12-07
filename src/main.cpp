#include "server.hpp"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "serverConfig.hpp"
#include "parseUtils.hpp"

int ServerConf::readValues = 1;

// https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa
int main(int argc, char const *argv[])
{
    (void)argc;
    // long valread;
    // long newSocket;
    // Server server;
    // char *hello = strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
    int serverCount = countServers(argv[1]);
    ServerConf servers[serverCount - 1];

    for (int i = 0; i < serverCount; i++) {
        ServerConf servers[i];
        servers[i].getServerInfo(argv[1]);
    }

    // server.setUpServer();
    // while(1)
    // {
    //     printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    //     newSocket = server.acceptSocket();

    //     char buffer[30000] = {0};
    //     valread = read( newSocket , buffer, 30000);
    //     printf("%s\n",buffer );
    //     write(newSocket, hello, strlen(hello));
    //     printf("------------------Hello message sent-------------------\n");
    //     close(newSocket);
    // }
    return 0;
}