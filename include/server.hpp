#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>
// #include <xti.h>

class Server {
public:
    int     setUpServer(int Port);
    void    setAddr(void);
    int     bindToClient(void);
    long    acceptSocket(void);
    void    closeSocket(int socket);

    int     getPort();

private:
    int     _Port;
    int     _serverFd;
    struct  sockaddr_in _addr;     
    // t_listen    _listen;
};

#endif