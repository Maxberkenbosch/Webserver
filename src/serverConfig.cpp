#include "serverConfig.hpp"
#include "parseUtils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void ServerConf::tokenize(char const *confFile) {
    // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
    // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    std::ifstream myFile(confFile);
    std::stringstream buffer;
    std::string intermediate;
    buffer << myFile.rdbuf();

    while(getline(buffer, intermediate, ';'))
        _tokens.push_back(intermediate);
    myFile.close();
    for (size_t i = 0; i < _tokens.size(); i++)
        _tokens[i].erase(remove(_tokens[i].begin(), _tokens[i].end(), '\n'), _tokens[i].end());
}

void    ServerConf::checkEmptyValues() {
    if (!_listenPort)
        _listenPort = 80;
    if (_root.empty())
        throw std::invalid_argument( "root is empty" );
    if (_serverName.empty())
        _serverName = _root;
    // Moet nog worden uitgebreid
}

// ---------- Setters --------------

void    ServerConf::setValues(std::string varName, int i) {
    if (varName == "listen")
        setListenPort(i);
    if (varName == "server_name")
        setServerName(i);
    if  (varName == "root")
        setRoot(i);
    if (varName == "cgi")
        setCgi(i);
    if (varName == "index")
        setIndex(i);
    if  (varName == "location") {
        setLocationPaths(i);
        setLocationsInfo(i);
    }
}

void ServerConf::setListenPort(int i) {
    std::stringstream ss;
    std::string line;
    int j = getValueIndex(_tokens[i]);
    while (_tokens[i][j])
        line += _tokens[i][j++];
    ss << line;
    ss >> _listenPort;
}

void ServerConf::setServerName(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _serverName.append(line);
}

void ServerConf::setRoot(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _root.append(line);
}

void    ServerConf::setCgi(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _cgi.append(line);
}

void    ServerConf::setIndex(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _index.append(line);
}

void    ServerConf::setLocationPaths(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;
    while (_tokens[i][j] != ' ' && _tokens[i][j])
        line += _tokens[i][j++];
    _locationPaths.push_back(getLocationPath(line));
    line.clear();
}

void    ServerConf::setLocationsInfo(int i) {
    std::string tmp; 
    std::stringstream ss((std::string)_tokens[i]);

    while(getline(ss, tmp, '\t')){
        _locationsInfo.push_back(tmp);
    }
    _locationsInfo.push_back("\n");
}

void    ServerConf::setLocationAttributes (const char *path) {
    std::stringstream ss;
    ss << "location " << path ;
    std::string s = ss.str();
    std::vector<std::string>::iterator it;

    it = std::find (_locationsInfo.begin(), _locationsInfo.end(), s);
    if (it != _locationsInfo.end()) {
        while (*it != "\n") {
            if (getFirstWord(*it) == "allow_methods")
                _allowedMethod = getValue(*it);
            if (getFirstWord(*it) == "index")
                _index = getValue(*it);
            if (getFirstWord(*it) == "root")
                _root = getValue(*it);
            if (getFirstWord(*it) == "cgi")
                _cgi = getValue(*it);
            // if (getFirstWord(*it) == "client_body_buffer_size")
            //     _clientBufferSize = getValue(*it);
            *it++;
        }
    }
    else {
        throw std::invalid_argument( "Path argument in setLocationAttributes function is incorrect" );
    }
}

// ---------- Getters ------------

void    ServerConf::getParsedValues() {
    std::cout << "_____________________________________" << std::endl << std::endl;
    std::cout << "Listen port     = " << getListenPort() << std::endl;
    std::cout << "Server name     = " << getServerName() << std::endl;
    std::cout << "Root            = " << getRoot() << std::endl;
    std::cout << "Cgi             = " << getCgi() << std::endl;
    std::cout << "Index           = " << getIndex() << std::endl;
    std::cout << "Allowed methods = " << getAllowedMethod() << std::endl;
    std::cout << "Location paths  = \n";
    for (size_t i = 0; i < _locationPaths.size(); i++) {
        std::cout << "                 " << _locationPaths[i] << std::endl;
    }
    std::cout << "Locations       = \n";
    for (size_t i = 0; i < _locationsInfo.size(); i++) {
        std::cout << "                 " << _locationsInfo[i] << std::endl;
    }
    std::cout << "_____________________________________" << std::endl << std::endl;
}

int ServerConf::getListenPort() {
    return (_listenPort);
}

std::string ServerConf::getServerName() {
    return (_serverName);
}

std::string ServerConf::getRoot() {
    return (_root);
}

std::string ServerConf::getCgi() {
    return (_cgi);
}

std::string ServerConf::getIndex() {
    return (_index);
}

std::string ServerConf::getAllowedMethod() {
    return (_allowedMethod);
}

// ----------- Setting up the ServerConf object ----------------

ServerConf ServerConf::getServerInfo(const char *confFile) {
    tokenize(confFile);

    while (readValues < (int)_tokens.size()) {
        std::string tmp = getFirstWord(_tokens[readValues]);
        if (!tmp.empty())
            setValues(getFirstWord(_tokens[readValues]), readValues);
        readValues++;
        if (getFirstWord(_tokens[readValues]) == "server") {
            readValues++;
            break;
        }
    }
    checkEmptyValues();
    setLocationAttributes("/directory"); // Right now this is hardcoded, but it needs the right location path.
    getParsedValues();
    return (*this);
}

