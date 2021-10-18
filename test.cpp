/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "test.h"
#include <iostream>

int main(int argc, char const *argv[]) {
    printf("Test Parser!!\n");
    // Memory* _memory = new Memory();
    // IMemory* _imemory = new IMemory();
    // Cpu* _cpu = new Cpu(_memory, _imemory);
    // Clock* _clock = _clock->getClock(_cpu, _memory, _imemory);

    enum STATES { IDLE=0, FETCH=1, DECODE=2, MEM_REQ=3, WAIT=4 };
    printf("Size of enum: %ld\n", sizeof(STATES));
    return 0;
}
