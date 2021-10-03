#ifndef PARSER_H
#define PARSER_H

#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // toLower, wordCount
#include <fstream>              // std::ifstream
#include <map>                  // std::map
#include <stdio.h>              // printf, sscanf
#include <utility>              // std::pair

class Parser {
private:
    Clock*  _clock  = Clock::getClock();
    Cpu*    _cpu    = Cpu::getCpu();
    Memory* _memory = Memory::getMemory();

    // Associative Lookup Arrays
    std::map<std::string, int> deviceList;
    std::map<std::string, int> clkOperations;
    std::map<std::string, int> cpuOperations;
    std::map<std::string, int> memOperations;

public:
    // Public Constructor
    Parser();

    // Instance Methods
    void loadOptions(int,char*[],std::map<std::string, int>&);
    void parseClock(char*,std::string);
    void parseCpu(char*,std::string);
    void parseMemory(char*,std::string);
    void parseInput(char*);
};

#endif
