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
}

void EmulatorTest::printTest() {
    printf("Test Print.\n");
}

// EmulatorTest::~EmulatorTest() {
// }

/* CshTestSuite */
CshTest::CshTest(int debug) : EmulatorTest(debug) {
    setUp();
}

void CshTest::setUp(){
    printf("Cache Test SetUp\n");
}

void CshTest::tearDown(){
    printf("Cache Test TearDown\n");
}

/* ClkTestSuite */
ClkTest::ClkTest(int debug) : EmulatorTest(debug) {
    setUp();
}

void ClkTest::setUp(){
    printf("Clock Test SetUp\n");
    tickEmpty();
    tickReset();
    tickSingle();
}

void ClkTest::tickReset() {
    printf("ClkTest::tickReset: Running...\n");
    _clock->tick(1);
    _clock->reset();
    assert(0 == _clock->tick(0));
}

void ClkTest::tickEmpty() {
    printf("ClkTest::tickEmpty: Running...\n");
    _clock->reset();
    int intialValue = 0;
    assert(intialValue == _clock->tick(0));
}

void ClkTest::tickSingle() {
    printf("ClkTest::tickSingle: Running...\n");
    _clock->reset();
    int intialValue = 1;
    assert(intialValue == _clock->tick(1));
}

void ClkTest::tearDown(){
    printf("Clock Test TearDown\n");
}

/* CpuTestSuite */
CpuTest::CpuTest(int debug) : EmulatorTest(debug) {
    setUp();
}

void CpuTest::setUp(){
    printf("Cpu Test SetUp\n");
}

void CpuTest::tearDown(){
    printf("Cpu Test TearDown\n");
}

/* MemTestSuite */
MemTest::MemTest(int debug) : EmulatorTest(debug) {
    setUp();
}

void MemTest::setUp(){
    printf("Mem Test SetUp\n");
}

void MemTest::tearDown(){
    printf("Mem Test TearDown\n");
}

int main(int argc, char const *argv[]) {
    printf("EmulatorTest Parser!!\n");
    // EmulatorTest t(0);
    // int input = std::stoi("A5422", 0, 16);
    // int NNN = (input >> 17) & 7;
    // int DDD = (input >> 14) & 7;
    // int SSS = (input >> 11) & 7;
    // int TTT = (input >> 8) & 7;
    // int III = (input & 255);
    // int UHF = (III >> 4) & 15;
    // int LHF = III & 15;
    // printf("NNN: %X\nDDD: %X\nSSS: %X\nTTT: %X\nIII: %d\n\n", NNN, DDD, SSS, TTT, III);
    // printf("UHF: %d\nLHF: %d\n", UHF, LHF);
    ClkTest clk(0);
    return 0;
}
