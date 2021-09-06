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
    Parser p;
    p.parseInput(const_cast<char *>(argv[1]));
    return 0;
}
