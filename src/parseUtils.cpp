#include "parseUtils.hpp"
#include <sstream>
#include <fstream>

int countServers(const char *confFile) {
    std::ifstream fin(confFile);
    int count=0;
    char ch[50]; // Hier nog iets mooiers voor bedenken.
    char *word = strdup("server;");
  
    while(fin) {
        fin>>ch;
        if(strcmp(ch,word)==0)
        count++;
    } 
    fin.close();
    free(word);
    return (count);
}

std::string getFirstWord(std::string input) {
    std::string firstWord = input.substr(0, input.find(" ")); //Leak??

    return (firstWord);
}

std::string getLocationPath(std::string input) {
    std::string firstWord = input.substr(0, input.find("\t")); // Leak?

    return (firstWord);
}

std::string getValue(std::string input) {
    int i = 0;

    while (input[i] != ' ')
        i++;
    std::string value = input.substr(i + 1, input.find("\n")); // Leak?

    return (value);
}

int getValueIndex(std::string line) {
    int index = line.find(" ");
    index++;
    return (index);
}

std::string getNthWord(std::string s, std::size_t n)
{
    std::istringstream iss (s);
    while(n-- > 0 && (iss >> s));
    return s;
}

std::string getRequestValue(std::string input)
{
    std::string result;
    int i = 0;

    while (input[i] != ' ')
        i++;
    i++;
    while (input[i]) {
        result += input[i];
        i++;
    }
    return (result);
}