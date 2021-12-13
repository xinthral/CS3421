#ifndef CLOCK_H
#define CLOCK_H

#include "cpu.h"                // Internal CPU object
#include "iodevice.h"           // Internal I/O object
#include "imemory.h"            // Internal Instruction Memory Object
#include "memory.h"             // Internal Memory Object
#include "utilities.h"          // Local Helper Functions
#include <stdio.h>              // printf
#include <string>               // std::string

// Forward Declarations
class Cpu;
class IODevice;
class IMemory;
class Memory;

class Clock {
protected:
    int DEBUG;                      // Debug Control

private:
    static Clock* clk_instance;     // Singleton Object

    Cpu* _cpu;
    Memory* _memory;
    IMemory* _imemory;
    IODevice* _iodevice;

    int cycle;                      // Current cycle of clock
    bool clock_enabled;             // CPU tracks if clock is meant to be running
    std::map<std::string,int> clkOperations;
    Clock(Cpu*,Memory*,IMemory*,IODevice*,int);   // Forces Private Instantiation
public:
    // Singleton Method
    static Clock* getClock(Cpu*,Memory*,IMemory*,IODevice*,int);

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
