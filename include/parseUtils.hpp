#ifndef PARSEUTILS_HPP
# define PARSEUTILS_HPP

#include <string>

int         countServers(const char *confFile);
std::string getFirstWord(std::string input);
std::string getLocationPath(std::string input);
std::string getValue(std::string input) ;
int         getValueIndex(std::string line);
std::string getNthWord(std::string s, std::size_t n);
std::string getRequestValue(std::string input);

#endif
