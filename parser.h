#ifndef PARSER_H
#define PARSER_H

#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include "imemory.h"            // Local iMemory Object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // Local Helper Functions
#include <fstream>              // std::ifstream

class Parser {
private:
    // Clock Singleton
    Clock*  _clock  = Clock::getClock();
    Cpu*    _cpu;                           // Cpu Device;
    IMemory* _imemory;                      // Instruction Memory Device
    Memory* _memory;                        // Memory Device

    // Associative Lookup Array
    std::map<std::string, int> deviceList;

public:
    Parser();
    // Parser Functions
    void readInputFile(char* fileName);
};

#endif
