#ifndef REQUESTCONF_HPP
# define REQUESTCONF_HPP

#include <map>
#include <vector>
#include <string>

class RequestConf {
public:
    RequestConf(const char *buffer);

    void    tokenize(char const *buffer);
    void    checkBadRequest();

    void    setRequestAttributes();

    void    getRequestInfo();

private:
    std::vector <std::string>   _requestVec;
    std::string                 _method;
    std::string                 _path;
    std::string                 _httpVersion;

    std::map<std::string, std::string>  _header;
    // std::map<std::string, std::string>  _body;
};


#endif