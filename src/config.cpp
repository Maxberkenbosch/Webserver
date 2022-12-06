#include "config.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void Config::tokenize(char const *confFile) {
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

// void    Config::parseLocations() {
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

void    Config::setValues(std::string varName, int i) {
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

void Config::setListenPort(int i) {
    std::stringstream ss;
    std::string line;
    int j = getValueIndex(_tokens[i]);
    while (_tokens[i][j])
        line += _tokens[i][j++];
    ss << line;
    ss >> _listenPort;
}

void Config::setServerName(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _serverName.append(line);
}

void Config::setRoot(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _root.append(line);
}

void    Config::setCgi(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _cgi.append(line);
}

void    Config::setIndex(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j])
        line += _tokens[i][j++];
    _index.append(line);
}

void    Config::setLocations(int i) {
    int j = getValueIndex(_tokens[i]);
    std::string line;

    while (_tokens[i][j] != ' ')
        line += _tokens[i][j++];
    line += "\n";
    _locationsVec.push_back(line);
    _locationsString.append(line);

}

// ---------- Getters ------------

void    Config::getParsedValues() {
    std::cout << "Listen port = " << getListenPort() << std::endl;
    std::cout << "Server name = " << getServerName() << std::endl;
    std::cout << "Root        = " << getRoot() << std::endl;
    std::cout << "Cgi         = " << getCgi() << std::endl;
    std::cout << "Index       = " << getIndex() << std::endl;
    // std::cout << "Locations   = " << getLocationsString() << std::endl;
    std::cout << location
    for (size_t i = 0; i < _locationsVec.size(); i++) {
        std::cout << _locationsVec[i] << std::endl;
    }
}

int Config::getListenPort() {
    return (_listenPort);
}

std::string Config::getServerName() {
    return (_serverName);
}

std::string Config::getRoot() {
    return (_root);
}

std::string Config::getCgi() {
    return (_cgi);
}

std::string Config::getIndex() {
    return (_index);
}

std::string Config::getLocationsString() {
    return (_locationsString);
}

// -------- Constructor -------------

Config::Config(char const *confFile) {
    tokenize(confFile);

    for (size_t i = 0; i < _tokens.size(); i++) 
        setValues(getFirstWord(_tokens[i]), i);
    // parseLocations();
    getParsedValues();
}

