#ifndef CLOCK_H
#define CLOCK_H

#include "cpu.h"                // Internal CPU object
#include "imemory.h"            // Internal Instruction Memory Object
#include "memory.h"             // Internal Memory Object
#include "utilities.h"          // Local Helper Functions
#include <stdio.h>              // printf
#include <string>               // std::string

// Forward Declarations
class Cpu;
class IMemory;
class Memory;

class Clock {
private:
    static Clock* clk_instance;     // Singleton Object

    Cpu* _cpu;
    Memory* _memory;
    IMemory* _imemory;

    int cycle;                      // Current cycle of clock
    bool clock_enabled;             // Track if clock is meant to be running
    std::map<std::string,int> clkOperations;
    Clock(Cpu*,Memory*,IMemory*);   // Forces Private Instantiation
public:
    // Singleton Method
    static Clock* getClock(Cpu*,Memory*,IMemory*);

    // Class Methods
    void doWork();
    void dump();
    void reset();
    int tick(int);
    void parseInstructions(std::string);

    // Deconstructor
    ~Clock();
};

#endif
