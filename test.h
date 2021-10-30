#ifndef TEST_H
#define TEST_H

#include "utilities.h"
#include <stdio.h>

#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include "imemory.h"            // Local iMemory Object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // Local Helper Functions
#include <fstream>              // std::ifstream

class Test {
private:
    // Clock Singleton
    Clock*  _clock;                         // Clock Device;
    Cpu*    _cpu;                           // Cpu Device;
    IMemory* _imemory;                      // Instruction Memory Device
    Memory* _memory;                        // Memory Device
public:
    Test();                                 // Construct
    void printTest();
};

#endif
