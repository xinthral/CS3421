#ifndef UTILITIES_H
#define UTILITIES_H

#include <map>                  // std::map
#include <string>               // std::string

namespace Utilities {
    // Helper Functions
    std::string chunkInstruction(std::string,char*);
    void toLower(char*,int);
    void toUpper(char*,int);
    int wordCount(char*);
    void loadOptions(int, char**, std::map<std::string, int>&);
}

#endif
