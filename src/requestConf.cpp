#include "requestConf.hpp"
#include "parseUtils.hpp"
#include <sstream>
#include <iostream>

void    RequestConf::tokenize(char const *buffer) {
    std::string tmp; 
    std::stringstream ss(buffer);

    while(getline(ss, tmp, '\n')){
        _requestVec.push_back(tmp);
    }
}

void    RequestConf::checkBadRequest() {
    // WIP
}


// ------------ Getters ---------------

void    RequestConf::getRequestInfo() {
    // for (size_t i = 0; i < _requestVec.size(); i++) {
    //     std::cout << _requestVec[i] << std::endl;
    // }
    std::map<std::string, std::string>::iterator itr;
    for(itr=_header.begin();itr!=_header.end();itr++)
    {
        std::cout<<itr->first<<" "<<itr->second<<std::endl;
    }
}

// ------------ Setters ---------------

void    RequestConf::setRequestAttributes() {
    std::vector<std::string>::iterator it = _requestVec.begin();
    // Setting the Request line items
    _method = getNthWord(*it, 1);
    _path = getNthWord(*it, 2);
    _httpVersion = getNthWord(*it, 3);

    // Setting the header !needs fixing!
    *it++;
    while (*it != "\n") {
        _header.insert(std::make_pair(getNthWord(*it, 1), getNthWord(*it, 2)));
        *it++;
    }
    // Setting the body
    // *it++;
    // if (_method == "GET") {
    //     while (it != _requestVec.end()) {
    //         _header.insert(std::pair<std::string, std::string>(getNthWord(*it, 1), getNthWord(*it, 2)));
    //         *it++;
    //     }
    // }
}


// ---------- Constructor -------------

RequestConf::RequestConf(const char *buffer) {
    tokenize(buffer);
    setRequestAttributes(); // WIP
    checkBadRequest(); 
}
