#ifndef REQUESTCONF_HPP
# define REQUESTCONF_HPP

#include <map>
#include <vector>
#include <string>
#include "serverConfig.hpp"

class RequestConf {
public:
    RequestConf(const char *buffer, ServerConf** serverArray, int size);

    void        tokenize(char const *buffer);
    int         getStatusCode(ServerConf** serverArray, int size);

    std::string getMethod ();
    std::string getPath ();
    std::string getHttpVersion ();
    std::string getValue(std::string key);


    void        setRequestAttributes();

    void        printRequestLine();
    void        printRequestInfo();

private:
    int                         _serverIndex;

    std::vector <std::string>   _requestVec;
    std::string                 _method;
    std::string                 _path;
    std::string                 _httpVersion;

    int                         _statusCode;

    std::map<std::string, std::string>  _requestContent;
    ServerConf                  _customServerConf;
    // std::map<std::string, std::string>  _body;
};


#endif