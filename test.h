#ifndef TEST_H
#define TEST_H

#include "clock.h"              // Local Clock object
#include "cpu.h"                // Local CPU object
#include <fstream>              // std::ifstream
#include "imemory.h"            // Local iMemory Object
#include "memory.h"             // Local Memory Object
#include "utilities.h"          // Local Helper Functions
#include <stdio.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class TestClass {
private:
    // Clock Singleton
    Clock*  _clock;                         // Clock Device;
    Cpu*    _cpu;                           // Cpu Device;
    IMemory* _imemory;                      // Instruction Memory Device
    Memory* _memory;                        // Memory Device
public:
    TestClass();                                 // Construct
    void printTest();
};

class CpuTestSuite : public CppUnit::TestFixture {
private:
    Clock*  _clock;                         // Clock Device;
    Cpu*    _cpu;                           // Cpu Device;
    IMemory* _imemory;                      // Instruction Memory Device
    Memory* _memory;                        // Memory Device
public:
    void setUp();
    void tearDown();
};

#endif
