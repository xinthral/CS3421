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
    static Clock* clk_instance; // Singleton Object
    int cycle;                  // Current cycle of clock
    std::map<std::string, int> clkOperations;
    Clock();                    // Forces Private Instantiation
public:
    // Instance Scope Attributes
    bool clock_enabled;         // Track if clock is meant to be running

    // Singleton Method
    static Clock* getClock();

    // Class Methods
    void dump();
    void reset();
    int tick(int);
    void parseInstructions(Cpu*, Memory*, std::string);

    // Deconstructor
    ~Clock();
};

#endif
