#ifndef XTEST_H
#define XTEST_H

#include <cassert>              // assert, assertm
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
    // void buildClk(int);
    // void buildCpu(int);
    // void buildCsh(int);
    // void buildMem(int);
    // void buildMim(int);
    void printTest();
    // ~EmulatorTest();            // Destructor

    virtual void setUp(){};
    virtual void tearDown(){};
};

class ClkTest : public EmulatorTest {
public:
    ClkTest(int);
    void setUp();
    void tickEmpty();
    void tickReset();
    void tickSingle();
    void tearDown();
    ~ClkTest();
};

class CpuTest : public EmulatorTest {
public:
    CpuTest(int);
    void setUp();
    void tearDown();
    ~CpuTest();
};

class CshTest : public EmulatorTest {
public:
    CshTest(int);
    void setUp();
    void cacheOn();
    void cacheOff();
    void tearDown();
    ~CshTest();
};

class MemTest : public EmulatorTest {
public:
    MemTest(int);
    void setUp();
    void tearDown();
    ~MemTest();
};

class MimTest : public EmulatorTest {
public:
    MimTest(int);
    void setUp();
    void tearDown();
    ~MimTest();
};

#endif
