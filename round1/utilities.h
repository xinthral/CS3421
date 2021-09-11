#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {
public:
    // Helper Functions
    std::string chunkInstruction(std::string,char*);
    void toLower(char*,int);
    int wordCount(char*);
};

// Singleton Method
extern Utilities &getUtilities();
#endif
