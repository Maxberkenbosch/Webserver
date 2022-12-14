#ifndef PARSEUTILS_HPP
# define PARSEUTILS_HPP

#include <string>

int         countServers(const char *confFile);
std::string getFirstWord(std::string input);
std::string getLocationPath(std::string input);
std::string getValue(std::string input) ;
int         getValueIndex(std::string line);

#endif
