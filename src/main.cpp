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
    // long valread;
    long newSocket;
    // // Add a new file descriptor to be monitored
    pollfd pfd;
    pollfd reset;
    // The hello variable is temporarily being used as the request line
    char *hello = strdup("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
    int serverCount = countServers(argv[1]);
    // Dinamically creating [serverCount] amount of Server objects
    Server** serverArray = new Server*[serverCount - 1];
    // Dinamically creating [serverCount] amount of ServerConf objects
    ServerConf** serverConfArray = new ServerConf*[serverCount - 1];
    std::vector<struct pollfd> fds;
    std::vector<struct pollfd> fds2;

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

    for (int i = 0; i < serverCount; i++)
    {
        pfd = reset;
        pfd.fd = serverArray[i]->_serverFd;
        pfd.events = POLLIN;
        fds.push_back(pfd);
    }

    while(1)
    {
        // printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        // Looping through the accept functions to create a socket for new clients
        
        // for (int i = 0; i < serverCount; i++)
        // {
        //     newSocket = 0;
        //     pfd = reset;
        //     newSocket = serverArray[i]->acceptSocket();
        //     if (newSocket > 0) {
        //         // std::cout << "That's a connection on port: " << serverArray[i]->getPort() << std::endl;
        //         pfd.fd = newSocket;
        //         pfd.events = POLLIN;
        //         pfd.revents = 0;
        //         fds.push_back(pfd);
        //     }
        // }

        // newSocket = serverArray[0]->acceptSocket();
        // if (newSocket > 0) {
        //     // std::cout << "That's a connection on port: " << serverArray[i]->getPort() << std::endl;
        //     pfd.fd = newSocket;
        //     pfd.events = POLLIN;
        //     // pfd.revents = 0;
        //     fds.push_back(pfd);
        // }
    
        // int pid = fork();

        // if (pid == 0)
        // {
        //     newSocket = serverArray[0]->acceptSocket();
        //     if (newSocket > 0) {
        //     // std::cout << "That's a connection on port: " << serverArray[i]->getPort() << std::endl;
        //         pfd.fd = newSocket;
        //         pfd.events = POLLIN;
        //         pfd.revents = 0;
        //         fds.push_back(pfd);
        //     }
        //     exit (0);
        // }
        
        // // Right now the whole request is read in one go, this needs to be changed (into reading small bits).
        // char buffer[30000] = {0};

        // // Call poll() with the vector as the array of pollfd structures.
        int ret = poll(fds.data(), fds.size(), 100);
        // // an error occurred
        if (ret < 0) { 
            // the call to poll() timed out
            std::cout<< "poll timed out" << std::endl;
        } else if (ret == 0) {
            // Timeout
            continue;
        } else {
        // // Process events for each file descriptor
            for (int i = 0; i < serverCount; i++)
            {
                newSocket = 0;
                pfd = reset;
                newSocket = serverArray[i]->acceptSocket(serverArray[i]->_serverFd, serverArray[i]->_addr);
                if (newSocket > 0) {
                    pfd.fd = newSocket;
                    pfd.events = POLLIN;
                    pfd.revents = 1;
                    fds2.push_back(pfd);
                }
            }
            for (std::vector<struct pollfd>::iterator it = fds2.begin(); it != fds2.end(); it++)
            {
                std::cout << "Voor de POLLINNN! : " << it->fd << "de poll is: " << it->revents << std::endl;
                if (it->revents & POLLIN)
                {
                    // Data available to read on pfd.fd
                    // Valread can be used to determine content-lenght
                    // valread = read(it->fd , buffer, 100);
                    // if (valread == -1)
                    //     continue;
                    //     // Error handling still needed
                    // std::cout << "valread = " << valread << std::endl;
                    // // The RequestConf objects is initialized using the read request (buffer)
                    // RequestConf *requestconf =  new RequestConf(buffer, serverConfArray, serverCount - 1);
                    // requestconf->printRequestLine();

                    // it->events = it->events & ~POLLIN;
                    // it->events |= POLLOUT;
                    it->events ^= POLLIN | POLLOUT;
                    it->revents = 4;
                    // delete requestconf;
                }
                if (it->revents & POLLOUT) {
        //          Write to client
                    std::cout << "It goes in hereee!" << std::endl;
                    int bytes_sent = send(it->fd, hello, strlen(hello), 0);
                    if (bytes_sent <= 0)
                        std::cout << "A Send error occured" << std::endl;
                    // fds2.erase(it);
                    close(it->fd);
                }
            }
        }
        // printf("%s\n",buffer );
        // printf("------------------Hello message sent-------------------\n");
    }
    // for(int i = 0; i < serverCount; i++) {
    //     std::cout << i << std::endl;
    //     delete serverArray[i];
    // }
    // delete[] serverArray;
    return 0;
}



// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     int pipefd[2];
//     int ret;
//     int num = 5;
//     int read_num;
    
//     ret = pipe(pipefd);
//     if (ret == -1) {
//         perror("pipe");
//         exit(1);
//     }
//     // fork the process
//     ret = fork();
//     if (ret == -1) {
//         perror("fork");
//         exit(1);
//     } else if (ret == 0) {
//         // child process
//         close(pipefd[0]); // close the read end of the pipe
//         // write the integer to the write end of the pipe
//         ret = write(pipefd[1], &num, sizeof(int));
//         if (ret == -1) {
//             perror("write");
//             exit(1);
//         }
//         // close the write end of the pipe
//         close(pipefd[1]);
//         exit(0);
//     } else {
//         // parent process
//         close(pipefd[1]); // close the write end of the pipe
//         // read the integer from the read end of the pipe
//         ret = read(pipefd[0], &read_num, sizeof(int));
//         if (ret == -1) {
//             perror("read");
//             exit(1);
//         }
//         // close the read end of the pipe
//         close(pipefd[0]);
//         printf("Received number: %d\n", read_num);
//     }
//     return 0;
// }



