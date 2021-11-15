#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>              // printf
#include "memory.h"             // Internal Memory Object

// Forward Declarations
class Memory;

class Cache {
private:
    Memory& _memory;
    int DEBUG{};
    bool _cache_enabled{};      // true if cache is enabled

public:
    Cache(Memory*, int);
    void cacheOn();
    void cacheOff();
    void dump();
    bool isCacheEnabled();
    void reset();
};

#endif
