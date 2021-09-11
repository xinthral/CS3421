#ifndef MEMORY_H
#define MEMORY_H

#include "utilities.h"          // Utility Functions
#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string
#include <vector>               // std::vector

class Memory {
private:
    static Memory* mem_instance;    // Singleton Object
    std::vector<int> registry;      // Memory Banks
    Memory();                       // Forces Public Instantiation
public:
    // Singleton method
    static Memory* getMemory();

    // Class Methods
    void create(uint16_t);
    void dump(int,int);
    void printBankHeaders();
    void reset();
    void set(int,int,std::string);
    void set_memory(int,int);

    // Deconstructor
    ~Memory();
};

#endif
