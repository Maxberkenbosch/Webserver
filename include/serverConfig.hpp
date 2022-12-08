#ifndef SERVERCONF_HPP
# define SERVERCONF_HPP

# include <vector>
# include <iostream>
#include <map>

class ServerConf {
public:
    static int  readValues;

    // ServerConf(char const *confFile);
    void    tokenize(char const *confFile);
    void    parseLocations();

    void    setValues(std::string varName, int i);
    void    setListenPort(int i);
    void    setServerName(int i);
    void    setRoot(int i);
    void    setCgi(int i);
    void    setIndex(int i);
    void    setLocations(int i);
    void    setLocationsMap(int i);

    ServerConf  getServerInfo(const char *confFile);

    void        getParsedValues();
    int         getListenPort();
    std::string getServerName();
    std::string getRoot();
    std::string getCgi();
    std::string getIndex();
    std::string getLocationsString();

private:
    std::vector <std::string>   _tokens;
    int                         _listenPort;
    std::string                 _serverName;
    std::string                 _root;
    std::string                 _cgi;
    std::string                 _index;
    std::string                 _locationsString;
    std::vector<std::string>    _locationsVec;
    std::map<std::string, std::string> locationsMap;
    std::vector <std::string> _locationsConfigArr;
};

#endif