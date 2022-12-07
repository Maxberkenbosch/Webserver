#include "serverConfig.hpp"
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
    _locationsString.clear(); // empties locations string from previous servers. 
    _locationsVec.clear();

    while(getline(buffer, intermediate, ';'))
        _tokens.push_back(intermediate);
    myFile.close();
    for (size_t i = 0; i < _tokens.size(); i++)
        _tokens[i].erase(remove(_tokens[i].begin(), _tokens[i].end(), '\n'), _tokens[i].end());
}

// void    ServerConf::parseLocations() {
//     std::stringstream buffer;
//     std::string intermediate;
//     buffer << _locationsString;
//     while(getline(buffer, intermediate, ' '))
//         _locationsVec.push_back(intermediate);
//     for (size_t i = 0; i < _locationsVec.size(); i++) {
//         std::cout << _locationsVec[i] << std::endl;
//     }
// }

std::string getFirstWord(std::string input) {
    std::string firstWord = input.substr(0, input.find(" "));
    return (firstWord);
}

int getValueIndex(std::string line) {
    int index = line.find(" ");
    index++;
    return (index);
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
    if  (varName == "location")
        setLocations(i);
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

void    ServerConf::setLocations(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;
    line.clear();
    while (_tokens[i][j] != ' ')
        line += _tokens[i][j++];
    line += "\n";
    std::cout << "line = " << line;
    _locationsVec.push_back(line);
    // _locationsString.append(line);

}

// ---------- Getters ------------

void    ServerConf::getParsedValues() {
    std::cout << "Listen port = " << getListenPort() << std::endl;
    std::cout << "Server name = " << getServerName() << std::endl;
    std::cout << "Root        = " << getRoot() << std::endl;
    std::cout << "Cgi         = " << getCgi() << std::endl;
    std::cout << "Index       = " << getIndex() << std::endl;
    // std::cout << "Locations   = " << getLocationsString() << std::endl;
    for (size_t i = 0; i < _locationsVec.size(); i++) {
        std::cout << _locationsVec[i] << std::endl;
    }
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

std::string ServerConf::getLocationsString() {
    return (_locationsString);
}

// -------- Constructor -------------

// ServerConf::ServerConf(char const *confFile) {
//     tokenize(confFile);

//     while (readValues < (int)_tokens.size()) {
//         setValues(getFirstWord(_tokens[readValues]), readValues);
//         std::cout << getFirstWord(_tokens[readValues]) << std::endl;
//         readValues++;
//         if (getFirstWord(_tokens[readValues]) == "server") {
//             readValues++;
//             break;
//         }
//     }
//     std::cout << readValues << std::endl;
//     // parseLocations();
//     // getParsedValues();
// }

ServerConf ServerConf::getServerInfo(const char *confFile) {
    tokenize(confFile);

    while (readValues < (int)_tokens.size()) {
        setValues(getFirstWord(_tokens[readValues]), readValues);
        // std::cout << getFirstWord(_tokens[readValues]) << std::endl;
        readValues++;
        if (getFirstWord(_tokens[readValues]) == "server") {
            readValues++;
            break;
        }
    }
    // parseLocations();
    getParsedValues();
    return (*this);
}

