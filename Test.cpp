/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This file is meant to serve as a testing
# bed for new functionality and ensure stability
# through high entropy.
**************************************/

#include "clock.h"
#include "cpu.h"
#include "memory.h"

int main(int argc, char const *argv[]) {
    extern Clock clk;
    Clock clk1 = clk.getClock();
    clk1.dump();
    return 0;
}
