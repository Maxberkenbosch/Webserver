#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>
// #include <xti.h>

class Server {
public:
    int     _serverFd;
    struct  sockaddr_in _addr;     

    int     setUpServer(int Port);
    void    setAddr(void);
    int     bindToClient(void);
    long    acceptSocket(int socket, struct  sockaddr_in _addr);
    void    closeSocket(int socket);

    int     getPort();

private:
    int     _Port;
    // t_listen    _listen;
};

#endif