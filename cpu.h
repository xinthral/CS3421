#ifndef CPU_H
#define CPU_H

#include <algorithm>            // std::transform
#include <cassert>              // assert
#include "clock.h"              // Internal Clock Object
#include "utilities.h"          // Local Helper Functions
#include <iterator>             // std::next
#include <map>                  // std::map
#include "memory.h"             // Internal Memory Object
#include <stdio.h>              // printf
#include <string>               // std::string

class Cpu {
private:
    std::string registrar[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    std::map<std::string, int> registers;
    std::map<std::string, int> cpuOperations;

public:
    Cpu();                      // Forces Public Instantiation
    // void doWork(Memory, int);
    void dump();
    void fetch_memory(Memory*, int);
    int get_register(std::string);
    void parseInstructions(std::string);
    void printRegistry(std::string);
    void reset();
    void set_reg(std::string, int);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void shift_registers();
};

#endif
