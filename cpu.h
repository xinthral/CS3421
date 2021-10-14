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
#include <string.h>             // std::string, strcmp

// Forward Declarations
class IMemory;

class Cpu {
private:
    int STATE;
    bool isWorkPending;
    std::map<std::string,int> registers;
    std::map<std::string,int> cpuOperations;

    std::string registrar[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    enum STATES { IDLE=0, FETCH=1, DECODE=2, MEM_REQ=3, WAIT=4 };

public:

    Cpu();                              // Constructor
    void doCycleWork();
    void dump();
    void fetch_memory(IMemory*);
    int get_register(std::string);
    void incrementPC();
    bool isMoreCycleWorkNeeded();
    void parseInstructions(std::string);
    void printRegistry(std::string);
    void reset();
    void set_reg(std::string,int);      // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void shift_registers();
    void startTick();
};

#endif
