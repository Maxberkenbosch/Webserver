#ifndef SERVER_HPP
# define SERVER_HPP

#include <netinet/in.h>
// #include <xti.h>

class Server {
public:
    static const int PORT = 8005;
    int     setUpServer(void);
    void    setAddr(void);
    int     bindToClient(void);
    long    acceptSocket(void);
    void    closeSocket(int socket);

private:
    int         _serverFd;
    struct      sockaddr_in _addr;     
    // t_listen    _listen;
};

#endif