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
    {
        _tokens.push_back(intermediate);
    }
    myFile.close();
}

int getValueIndex(std::string line) {
    int index = line.find(" ");
    index++;
    return (index);
}

// ---------- Setters --------------

void Config::setListenPort() {
    std::stringstream ss;
    std::string line;
    int i = getValueIndex(_tokens[0]);
    while (_tokens[0][i])
        line += _tokens[0][i++];
    ss << line;
    ss >> _listenPort;
}

void Config::setServerName() {
    int i = getValueIndex(_tokens[1]);
    std::string line;

    while (_tokens[1][i])
        line += _tokens[1][i++];
    _serverName.append(line);
}

// ---------- Getters ------------

int Config::getListenPort() {
    return (_listenPort);
}

std::string Config::getServerName() {
    return (_serverName);
}

std::string getFirstWord(std::string input) {
    std::string firstWord = input.substr(0, input.find(" "));
    return (firstWord);
}

void    Config::setValues(std::string varName) {
    if (varName == "listen")
        setListenPort();
    if (varName == "server_name")
        setServerName();
    // if (varName == "root")
}

Config::Config(char const *confFile) {
    tokenize(confFile);
    for (unsigned long i = 0; i < _tokens.size(); i++) {
        setValues(getFirstWord(_tokens[i]));
    }
    // std::cout << getListenPort() << std::endl;
    // std::cout << getServerName() << std::endl;
}

