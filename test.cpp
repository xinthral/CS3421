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
    // Utilities utilz = getUtilities();
    Clock *_clock = Clock::getClock();
    _clock->dump();
    _clock->tick(1);
    _clock->dump();
    _clock->tick(2);
    _clock->dump();
    _clock->reset();
    _clock->dump();
    return 0;
}
