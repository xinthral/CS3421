/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "test.h"
#include <iostream>

TestClass::Test() {
    // Instantiate Devices
    _memory = new Memory();
    _imemory = new IMemory();
    _cpu = new Cpu(_memory, _imemory);
    _clock = _clock->getClock(_cpu, _memory, _imemory);
}
void TestClass::printTest() {
    printf("Test Print.\n");
}

/* CpuTestSuite */
void CpuTestFixture::setUp() {
    _memory = new Memory();
    _imemory = new IMemory();
    _cpu = new Cpu(_memory, _imemory);
    _clock = _clock->getClock(_cpu, _memory, _imemory);
}

void CpuTestFixture::tearDown() {
    delete _memory;
    delete _imemory;
    delete _cpu;
    delete _clock;
}

int main(int argc, char const *argv[]) {
    printf("Test Parser!!\n");
    TestClass t;
    int input = std::stoi("A5422", 0, 16);
    int NNN = (input >> 17) & 7;
    int DDD = (input >> 14) & 7;
    int SSS = (input >> 11) & 7;
    int TTT = (input >> 8) & 7;
    int III = (input & 255);
    int UHF = (III >> 4) & 15;
    int LHF = III & 15;
    printf("NNN: %X\nDDD: %X\nSSS: %X\nTTT: %X\nIII: %d\n\n", NNN, DDD, SSS, TTT, III);
    printf("UHF: %d\nLHF: %d\n", UHF, LHF);

    /* Test Runner */
    CpuTestSuite cts;
    Test::TextOutput output(Test::TestOutput::Verbose);
    printf(cts.run(output, false));
    return 0;
}
