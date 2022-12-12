#ifndef SERVERServerConf_HPP
# define SERVERServerConf_HPP

# include <vector>
# include <iostream>

class ServerConf {
public:
    static int  readValues;

    ServerConf  getServerInfo(const char *confFile);
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

    void        getParsedValues();
    int         getListenPort();
    std::string getServerName();
    std::string getRoot();
    std::string getCgi();
    std::string getIndex();

private:
    std::vector <std::string>   _tokens;
    int                         _listenPort;
    std::string                 _serverName;
    std::string                 _root;
    std::string                 _cgi;
    std::string                 _index;
    std::vector<std::string>    _locationPaths;
    std::vector<std::string>    _locationsInfo;
};

#endif