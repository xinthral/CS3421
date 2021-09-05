#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string

class Memory {
private:
    int *banks;
    int bankSize;
public:
    void create(uint16_t);
    void dump(int,int);
    void printBankHeaders();
    void reset();
    ~Memory();
};

// Singleton method
Memory &getMemory();

#endif
