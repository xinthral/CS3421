/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "xtest.h"

EmulatorTest::EmulatorTest(int debug) {
    DEBUG = debug;
    // Instantiate Devices
    _cache = new Cache(DEBUG);
    _memory = new Memory(DEBUG);
    _imemory = new IMemory(DEBUG);
    _cpu = new Cpu(_memory, _imemory, DEBUG);
    _clock = _clock->getClock(_cpu, _memory, _imemory, DEBUG);
    setUp();
}
void EmulatorTest::printTest() {
    printf("Test Print.\n");
}

// EmulatorTest::~EmulatorTest() {
//     // Order of deconustruction matters here
//     tearDown();
//     delete _clock;
//     delete _cpu;
//     delete _imemory;
//     delete _memory;
// }

/* CpuTestSuite */

int main(int argc, char const *argv[]) {
    printf("EmulatorTest Parser!!\n");
    EmulatorTest t(0);
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
    return 0;
}
