#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>               // std::string

namespace Utilities {
    // Helper Functions
    std::string chunkInstruction(std::string,char*);
    void toLower(char*,int);
    int wordCount(char*);
};

#endif
