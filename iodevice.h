#ifndef IODEVICE_H
#define IODEVICE_H

#include <map>                  // std::map
#include <stdio.h>              // printf
#include <string>               // std::string
#include "utilities.h"          // Local Helper Functions

class IODevice {
    int _register{};
private:
    int DEBUG{};                                // Debug Control
    std::map<std::string,int> iodOperations;    // Cache Operations

public:
    IODevice(int);
    void dump();
    void load(std::string);
    void parseInstructions(std::string);
    void reset();
    void startTick(int);
};

#endif
