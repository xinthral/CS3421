#ifndef PARSER_H
#define PARSER_H

#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include "memory.h"             // Local Memory Object
#include <fstream>              // std::ifstream
#include <map>                  // std::map
#include <stdio.h>              // printf, sscanf
#include <utility>              // std::pair

class Parser {
private:
    // List of Available Devices
    std::map<std::string, int> deviceList;

public:
    // Establish Singleton Objects
    Clock clock     = getClock();
    Cpu cpu         = getCpu();
    Memory memory   = getMemory();

    Parser();
    void parseClock();
    void parseCpu();
    void parseInput(std::string);
    void parseMemory(std::string);
};

#endif
