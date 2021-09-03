/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "cpu.h"
#include "test.h"

int main() {
    printf("Test Parser!!\n");
    Cpu cpu = getCpu();
    cpu.dump();
    return 0;
}
