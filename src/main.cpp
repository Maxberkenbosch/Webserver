#include "server.hpp"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "serverConfig.hpp"
#include "parseUtils.hpp"
#include "requestConf.hpp"
#include <poll.h>
#include <sys/socket.h>


int ServerConf::readValues = 1;

// What is a web server?
// https://developer.mozilla.org/en-US/docs/Learn/Common_questions/What_is_a_web_server

// Goede bron voor HTTP request vs response :
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages#:~:text=HTTP%20messages%20are%20how%20data,the%20answer%20from%20the%20server.

// Bron om simpele webserver te snappen:
// https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa

// Source to better understand poll() : https://linuxhint.com/use-poll-system-call-c/

// You can test the server with localhost:8080/index.html (the port needs to be the same in the server.hpp and config file)
int main(int argc, char const *argv[])
{
    (void)argv;
    if (argc != 2)
        throw std::invalid_argument( "Wrong amount of arguments" );
    long valread;
    long newSocket;
    // // Add a new file descriptor to be monitored
    pollfd pfd;
    // The hello variable is temporarily being used as the request line
    // char *hello = strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
    int serverCount = countServers(argv[1]);
    // Dinamically creating [serverCount] amount of Server objects
    Server** serverArray = new Server*[serverCount - 1];
    // Dinamically creating [serverCount] amount of ServerConf objects
    ServerConf** serverConfArray = new ServerConf*[serverCount - 1];
    std::vector<struct pollfd> fds;

    for( int  i = 0; i < serverCount; i++ )
    {
        serverConfArray[i] = new ServerConf();
        serverConfArray[i]->setServerInfo(argv[1]);
    }

    for( int  i = 0; i < serverCount; i++ )
    {
        serverArray[i] = new Server();
        serverArray[i]->setUpServer(serverConfArray[i]->getListenPort());
        std::cout << "CHECK PORT: " << serverArray[i]->getPort() << std::endl;
    }

    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");

        // Looping through the accept functions to create a socket for new clients
        for (int i = 0; i < serverCount; i++)
        {
            newSocket = 0;
            newSocket = serverArray[i]->acceptSocket();
            if (newSocket) {
                std::cout << "That's a connection on port: " << serverArray[i]->getPort() << std::endl;
                pfd.fd = newSocket;
                pfd.events = POLLIN;
                fds.push_back(pfd);
            }
        }

        
        // // Right now the whole request is read in one go, this needs to be changed (into reading small bits).
        char buffer[30000] = {0};
        // // Call poll() with the vector as the array of pollfd structures.
        int ret = poll(fds.data(), fds.size(), -1);
        // // an error occurred
        if (ret < 0) {
        } 
            // the call to poll() timed out
        else if (ret == 0) {
        //     // Timeout
        } else {
        // // Process events for each file descriptor
            for (unsigned int i = 0; i < fds.size(); ++i) {
                if (fds[i].revents & POLLIN) {
                    std::cout << "print i = " << i << std::endl;
        //         // Data available to read on pfd.fd
        //         // Valread can be used to determine content-lenght
                    valread = read(newSocket , buffer, 30000);
        //         // The RequestConf objects is initialized using the read request (buffer)
                    // RequestConf requestconf = RequestConf(buffer, serverConfArray, serverCount - 1);
                    // pfd.events = pfd.events & ~POLLIN;  // clear POLLIN
                    // pfd.events |= POLLOUT;  
                }
                if (fds[i].revents & POLLOUT) {
        //             // Write to client
                    // write(newSocket, hello, strlen(hello));
                }
            }
        }
        // // printf("%s\n",buffer );
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

