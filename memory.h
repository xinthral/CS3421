#ifndef MEMORY_H
#define MEMORY_H

#include "utilities.h"          // Utility Functions
#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string

class Memory {
private:
    int *banks;
    int bankSize;
    Utilities utilz;
public:
    Memory();
    void create(uint16_t);
    void dump(int,int);
    void printBankHeaders();
    void reset();
    void set(int,int,std::string);
    void set_memory(int,int);
    // ~Memory();
};

// Singleton method
extern Memory &getMemory();

#endif
