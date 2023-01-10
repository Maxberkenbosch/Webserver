#include <sys/socket.h>
#include <cstdio>
#include <stdlib.h>
#include "server.hpp"
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int	Server::getPort() {
	return(_Port);
}

void    Server::setAddr(void) {
    memset((char *)&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
    // INADDR_ANY & PORT moeten nog worden aangepast
    // The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
	_addr.sin_port = htons(_Port);
}

// The accept system call grabs the first connection request on the queue of pending connections (set up in listen)
// and creates a new socket for that connection.
// The original socket that was set up for listening is used only for accepting connections, not for exchanging data. 

long    Server::acceptSocket(void)
{
    int addrlen = sizeof(_addr);
    long newSocket;

	newSocket = accept(_serverFd, (struct sockaddr *)&_addr, (socklen_t*)&addrlen);
	if (newSocket == -1)
		std::cerr << "Could not create socket. " << strerror(errno) << std::endl;
	// else
	// {
	// 	fcntl(newSocket, F_SETFL, O_NONBLOCK);
	// 	// _requests.insert(std::make_pair(socket, ""));
	// }
	return (newSocket);
}

void    Server::closeSocket(int socket)
{
	if (socket > 0)
		close(socket);
}

int     Server::setUpServer(int Port) {
	_Port = Port;
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (_serverFd == -1)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    this->setAddr();
    // When a socket is created with socket(), it exists in a name space (address family) but has no address assigned to it.  
    // bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
    if (bind(_serverFd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
	{
		std::cerr << "Could not bind port " << _Port << "." << std::endl;
		return (-1);
	}
    // The listen system call tells a socket that it should be capable of accepting incoming connections.
    // The second parameter, backlog, defines the maximum number of pending
    // connections that can be queued up before connections are refused.
    if (listen(_serverFd, 10) == -1)
	{
		std::cerr << "Could not listen." << std::endl;
		return (-1);
	}
	return (0);
}