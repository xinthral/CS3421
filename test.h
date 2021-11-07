#ifndef TEST_H
#define TEST_H

#include "cache.h"              // Local Cache object
#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include <fstream>              // std::ifstream
#include "imemory.h"            // Local iMemory Object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // Local Helper Functions
#include <stdio.h>

class TestClass {
private:
    int DEBUG{};
    // Clock Singleton
    Cache* _cache;                          // Cache Device
    Clock*  _clock;                         // Clock Device;
    Cpu*    _cpu;                           // Cpu Device;
    IMemory* _imemory;                      // Instruction Memory Device
    Memory* _memory;                        // Memory Device
public:
    TestClass(int);                         // Construct
    void printTest();
};

// class CpuTestSuite : public CppUnit::TestFixture {
// private:
//     Cache* _cache;                          // Cache Device
//     Clock*  _clock;                         // Clock Device;
//     Cpu*    _cpu;                           // Cpu Device;
//     IMemory* _imemory;                      // Instruction Memory Device
//     Memory* _memory;                        // Memory Device
// public:
//     void setUp();
//     void tearDown();
// };

#endif
