#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <iostream>

class Config {
public:
    Config(char const *confFile);
    void    tokenize(char const *confFile);
    void    setValues(std::string varName, int i);

    void    setListenPort(int i);
    void    setServerName(int i);
    void    setRoot(int i);
    void    setCgi(int i);
    void    setIndex(int i);
    void    setLocations(int i);

    void        getParsedValues();
    int         getListenPort();
    std::string getServerName();
    std::string getRoot();
    std::string getCgi();
    std::string getIndex();
    std::string getLocations();

private:
    std::vector <std::string> _tokens;
    int _listenPort;
    std::string _serverName;
    std::string _root;
    std::string _cgi;
    std::string _index;
    std::string _locations;

};

#endif