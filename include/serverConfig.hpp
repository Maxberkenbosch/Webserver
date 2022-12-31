#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP

# include <vector>
# include <iostream>
# include <map>

// using namespace std;

class ServerConf {
public:
    ServerConf();
    ~ServerConf();
    ServerConf(const ServerConf* ref);
    ServerConf& operator=(const ServerConf* obj);

    static int  readValues;

    void    tokenize(char const *confFile);
    void    checkEmptyValues();

    void    setValues(std::string varName, int i);
    void    setListenPort(int i);
    void    setServerName(int i);
    void    setRoot(int i);
    void    setCgi(int i);
    void    setIndex(int i);
    void    setLocationPaths(int i);
    void    setLocationsInfo(int i);
    void    setLocationAttributes(std::string path);

    ServerConf  setServerInfo(const char *confFile);

    void        getParsedValues();
    int         getListenPort();
    std::string getServerName();
    std::string getRoot();
    std::string getCgi();
    std::string getIndex();
    std::string getAllowedMethod();
    std::vector<std::string> getLocationPaths();

private:
    std::vector <std::string>   _tokens;
    int                         _listenPort;
    std::string                 _serverName;
    std::string                 _root;
    std::string                 _cgi;
    std::string                 _index;
    std::vector<std::string>    _locationPaths;
    std::vector<std::string>    _locationsInfo;
    std::string                 _allowedMethod;
    // int                         _clientBufferSize;
};

#endif