/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "xtest.h"

EmulatorTest::EmulatorTest(int debug)
    : DEBUG(debug) {

    // Instantiate Devices
    _memory = new Memory(DEBUG);
    _imemory = new IMemory(DEBUG);
    _cache = new Cache(_memory, DEBUG);
    _cpu = new Cpu(_memory, _imemory, DEBUG);
    _clock = _clock->getClock(_cpu, _memory, _imemory, DEBUG);
}

void EmulatorTest::printTest() {
    printf("Test Print.\n");
}

/* ClkTestSuite */
ClkTest::ClkTest(int debug)
    : EmulatorTest(debug) {
    setUp();
}

void ClkTest::setUp(){
    printf("Clock Test SetUp\n");
    _cpu->setClock(false);
    tickEmpty();
    tickReset();
    tickSingle();
}

void ClkTest::tickReset() {
    printf("ClkTest::tickReset: Running...\n");
    _clock->reset();
    assert(0 == _clock->tick(0));
}

void ClkTest::tickEmpty() {
    printf("ClkTest::tickEmpty: Running...\n");
    _clock->reset();
    assert(0 == _clock->tick(0));
}

void ClkTest::tickSingle() {
    printf("ClkTest::tickSingle: Running...\n");
    _clock->reset();
    assert(1 == _clock->tick(1));
}

void ClkTest::tearDown(){
    printf("Clock Test TearDown\n");
}

ClkTest::~ClkTest() {
    tearDown();
}

/* CpuTestSuite */
CpuTest::CpuTest(int debug)
    : EmulatorTest(debug) {
    setUp();
}

void CpuTest::setUp(){
    printf("Cpu Test SetUp\n");
}

void CpuTest::tearDown(){
    printf("Cpu Test TearDown\n");
}

CpuTest::~CpuTest() {
    tearDown();
}

/* CshTestSuite */
CshTest::CshTest(int debug)
    : EmulatorTest(debug) {
    setUp();
}

void CshTest::setUp(){
    printf("Cache Test SetUp\n");
    blockId();
    cacheOn();
    cacheOff();
}

void CshTest::blockId() {
    printf("CshTest::blockId: Running...\n");
    int instruction = 120;
    assert(3 == _cache->blockId(instruction));
}

void CshTest::cacheOn() {
    printf("CshTest::cacheOn: Running...\n");
    _cache->cacheOn();
    assert(true == _cache->isCacheEnabled());
}

void CshTest::cacheOff() {
    printf("CshTest::cacheOff: Running...\n");
    _cache->cacheOff();
    assert(false == _cache->isCacheEnabled());
}

void CshTest::tearDown(){
    printf("Cache Test TearDown\n");
}

CshTest::~CshTest() {
    tearDown();
}

/* MemTestSuite */
MemTest::MemTest(int debug)
    : EmulatorTest(debug) {
    setUp();
}

void MemTest::setUp(){
    printf("Mem Test SetUp\n");
}

void MemTest::tearDown(){
    printf("Mem Test TearDown\n");
}

MemTest::~MemTest() {
    tearDown();
}

/* MimTestSuite */
MimTest::MimTest(int debug)
    : EmulatorTest(debug) {
    setUp();
}

void MimTest::setUp(){
    printf("Mim Test SetUp\n");
}

void MimTest::tearDown(){
    printf("Mim Test TearDown\n");
}

MimTest::~MimTest() {
    tearDown();
}

int main(int argc, char const *argv[]) {
    printf("EmulatorTest Parser!!\n");
    ClkTest clk(0);
    CshTest csh(0);
    return 0;
}
