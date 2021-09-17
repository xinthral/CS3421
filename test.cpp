/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "test.h"

int main(int argc, char const *argv[]) {
    printf("Test Parser!!\n");
    std::string testStr = "0x08 0x07 0x06 0x05 0x04 0x03 0x02 0x01";
    int start = 0x00, end = 0x08;
    // Utilities utilz = getUtilities();
    Clock* _clock = Clock::getClock();
    Cpu* _cpu = Cpu::getCpu();
    Memory* _memory = Memory::getMemory();
    _memory->create(0x100);
    _memory->set(start, end, testStr);
    _cpu->set_reg("rA", 0x00);
    _cpu->set_reg("Rb", 0x02);
    _cpu->set_reg("rc", 0x03);
    _cpu->set_reg("rd", 0x04);
    _cpu->set_reg("re", 0x05);
    _cpu->set_reg("rh", 0x06);
    _cpu->dump();
    for (size_t i = 0; i < 5; i++) {
        _cpu->doWork(*_clock, *_memory);
    }
    _cpu->dump();
    return 0;
}
