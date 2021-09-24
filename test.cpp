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
    std::string testStr = "0x08 0x07 0x06 0x05 0x04 0x03 0x02 0x01";
    int start = 0x00, end = 0x08;
    // Utilities utilz = getUtilities();
    Clock* _clock = Clock::getClock();
    Cpu* _cpu = Cpu::getCpu();
    Memory* _memory = Memory::getMemory();
    _memory->create(0x10);
    _memory->set(start, end, testStr);
    _cpu->fetch_memory(_memory, 3);
    _cpu->dump();
    _memory->dump(0x0, 0x08);
    return 0;
}
