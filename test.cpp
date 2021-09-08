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
    Memory* memory = new Memory();
    memory->create(0x08);
    memory->reset();
    memory->set(0x00, 0x08, testStr);
    memory->dump(0x00, 0x08);
    return 0;
}
