/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "test.h"
#include <iostream>

Test::Test() {
    // Instantiate Devices
    _memory = new Memory();
    _imemory = new IMemory();
    _cpu = new Cpu(_memory, _imemory);
    _clock = _clock->getClock(_cpu, _memory, _imemory);
}

void Test::printTest() {
    printf("Test Print.\n");
}

int main(int argc, char const *argv[]) {
    printf("Test Parser!!\n");
    Test t;
    return 0;
}
