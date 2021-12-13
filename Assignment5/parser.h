#ifndef PARSER_H
#define PARSER_H

#include "cache.h"              // Local Cache object
#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include "imemory.h"            // Local iMemory Object
#include "iodevice.h"           // Local ioDevice object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // Local Helper Functions
#include <fstream>              // std::ifstream

class Parser {
protected:
    int DEBUG{};                            // Debug output control
private:
    // Clock Singleton
    Cache*      _cache;                     // Cache Device
    Clock*      _clock;                     // Clock Device;
    Cpu*        _cpu;                       // Cpu Device;
    IMemory*    _imemory;                   // Instruction Memory Device
    IODevice*   _iodevice;                  // IODevice Device
    Memory*     _memory;                    // Memory Device

    // Associative Lookup Array
    std::map<std::string, int> deviceList;

public:
    Parser(int);
    // Parser Functions
    void readInputFile(char* fileName);
};

#endif
