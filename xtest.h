#ifndef EMULATOR_TEST_H
#define EMULATOR_TEST_H

#include "cache.h"              // Local Cache object
#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include <fstream>              // std::ifstream
#include "imemory.h"            // Local iMemory Object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // Local Helper Functions
#include <stdio.h>

class EmulatorTest {
protected:
    int DEBUG{};
    // Clock Singleton
    Cache*      _cache;         // Cache Device
    Clock*      _clock;         // Clock Device;
    Cpu*        _cpu;           // Cpu Device;
    IMemory*    _imemory;       // Instruction Memory Device
    Memory*     _memory;        // Memory Device
public:
    EmulatorTest(int);          // Construct
    // void constructCsh();
    // void constructCpu();
    // void constructMem();
    // void constructMim();
    void printTest();
    // ~EmulatorTest();            // Destructor

    virtual void setUp(){};
    virtual void tearDown(){};
};

class CpuTest : public EmulatorTest {
public:
    void setUp(){};
    void tearDown(){};
};

#endif
