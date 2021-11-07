/**************************************
# Author: Jesse Hassell
# Date: Nov, 2021
# The cache device sits between the CPU and Data Memory, and can improve memory
# performance. The cache contains 8 bytes of high speed memory, and contains
# logic to handle data passing through it from read/lw instructions and write/sw
# instructions.
**************************************/

#include "cache.h"

Cache::Cache(int debug) {
    DEBUG = debug;
}
