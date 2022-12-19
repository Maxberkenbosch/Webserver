#include "requestConf.hpp"
#include "parseUtils.hpp"
#include <sstream>
#include <iostream>

// #include <exception>


// Great source describing the Http request:
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages

void    RequestConf::tokenize(char const *buffer) {
    std::string tmp; 
    std::stringstream ss(buffer);

    while(getline(ss, tmp, '\n')){
        _requestVec.push_back(tmp);
    }
}

int    RequestConf::checkBadRequest() {
    // WIP!
    // Only Get, Post and Delete need to be supported
    if (_method == "GET" || _method == "POST" || _method == "DELETE")
        return (200);
    return (400);
}


// ------------ Getters ---------------

void    RequestConf::printRequestInfo() {
    std::map<std::string, std::string>::iterator itr;
    
    std::cout << "Request line items:" << std::endl;
    std::cout << _method << std::endl;
    std::cout << _path << std::endl;
    std::cout << _httpVersion << std::endl << std::endl;
    std::cout << "Map:" << std::endl;
    for (itr = _requestContent.begin(); itr != _requestContent.end(); ++itr) {
        std::cout << itr->first << ' ' << itr->second
             << '\n';
    }
}

std::string RequestConf::getMethod () {
    return(_method);
}

std::string RequestConf::getPath () {
    return(_path);
}

std::string RequestConf::getHttpVersion () {
    return(RequestConf::_httpVersion);
}

// Gets the value of the given key, don't forget to add ":" at the end of the key
std::string RequestConf::getValue(std::string key) {
    std::map<std::string,std::string>::iterator it;

    it = _requestContent.find(key);
    if (it != _requestContent.end())
        return (it->second);
    throw std::invalid_argument("getValue() error: The given variable does not exits in the request map");
}

// ------------ Setters ---------------

void    RequestConf::setRequestAttributes() {
    // Setting the Request line items
    _method = getNthWord(_requestVec[0], 1);
    _path = getNthWord(_requestVec[0], 2);
    _httpVersion = getNthWord(_requestVec[0], 3);

    // Setting the Header and/or Body variables in a map
    for (size_t i = 1; i < _requestVec.size() - 1; ++i) {
        _requestContent.insert(std::pair<std::string, std::string>(getNthWord(_requestVec[i], 1), getRequestValue(_requestVec[i])));
    }
    // Setting the body
    // *it++;
    // if (_method == "POST") {
    //     while (it != _requestVec.end()) {
    //         _header.insert(std::pair<std::string, std::string>(getNthWord(*it, 1), getRequestInfo(*it)));
    //         *it++;
    //     }
    // }
}


// ---------- Constructor -------------

RequestConf::RequestConf(const char *buffer) {
    // Putting the request in a vector
    tokenize(buffer);

    // Splitting vector into variables and map
    setRequestAttributes();

    // Checking Valid request and returning a status code
    int statusCode = checkBadRequest(); 
}
