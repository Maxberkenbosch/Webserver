#ifndef REQUESTCONF_HPP
# define REQUESTCONF_HPP

#include <map>
#include <vector>
#include <string>

class RequestConf {
public:
    RequestConf(const char *buffer);

    void        tokenize(char const *buffer);
    int         checkBadRequest();

    std::string getMethod ();
    std::string getPath ();
    std::string getHttpVersion ();
    std::string getValue(std::string key);


    void        setRequestAttributes();

    void        printRequestInfo();

private:
    std::vector <std::string>   _requestVec;
    std::string                 _method;
    std::string                 _path;
    std::string                 _httpVersion;

    std::map<std::string, std::string>  _requestContent;
    // std::map<std::string, std::string>  _body;
};


#endif