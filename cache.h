#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>              // printf

class Cache {
private:
    int DEBUG{};
public:
    Cache(int);
    void reset();
    void cacheOn();
    void cacheOff();
    void dump();
};

#endif
