#include "server.hpp"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "serverConfig.hpp"
#include "parseUtils.hpp"
#include "requestConf.hpp"

int ServerConf::readValues = 1;

// Goede bron voor HTTP request vs response :
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages#:~:text=HTTP%20messages%20are%20how%20data,the%20answer%20from%20the%20server.

// Bron om simpele webserver te snappen:
// https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa
int main(int argc, char const *argv[])
{
    (void)argv;
    (void)argc;
    // if (argc != 2)
    //     throw std::invalid_argument( "Wrong amount of arguments" );
    long valread;
    long newSocket;
    Server server;
    char *hello = strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
    // int serverCount = countServers(argv[1]);
    
    // ServerConf** serverArray = new ServerConf*[serverCount - 1];
    // for( int  i = 0; i < serverCount; i++ )
    // {
    //     serverArray[i] = new ServerConf();
    //     serverArray[i]->getServerInfo(argv[1]);
    // }

    server.setUpServer();
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        newSocket = server.acceptSocket();

        char buffer[30000] = {0};
        valread = read( newSocket , buffer, 30000);
        RequestConf requestconf = RequestConf(buffer);
        (void)requestconf;
        //requestconf.getRequestInfo();
        printf("%s\n",buffer );
        write(newSocket, hello, strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(newSocket);
    }
    // for(int i = 0; i < serverCount; i++) {
    //     std::cout << i << std::endl;
    //     delete serverArray[i];
    // }
    // delete[] serverArray;
    return 0;
}