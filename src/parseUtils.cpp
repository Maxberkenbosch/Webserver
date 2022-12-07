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
    return (count);
}