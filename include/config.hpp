#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <iostream>

class Config {
public:
    Config(char const *confFile);
    void    tokenize(char const *confFile);
    void    setValues(std::string varName);

    void    setListenPort();
    void    setServerName();
    void    setRoot();

    int         getListenPort();
    std::string getServerName();

private:
    std::vector <std::string> _tokens;
    int _listenPort;
    std::string _serverName;
    std::string _root;

};

#endif