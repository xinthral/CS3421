#ifndef MEMORY_H
#define MEMORY_H

#include "utilities.h"          // Utility Functions
#include <stdint.h>             // uint16_t
#include <stdexcept>            // std::out_of_range
#include <stdio.h>              // printf
#include <string>               // std::string
#include <vector>               // std::vector

class Memory {
private:
    static Memory* mem_instance;    // Singleton Object
    int* registry;                  // Memory Banks
    int capacity;                   // Size of memory bank
    Memory();                       // Forces Public Instantiation
public:
    // Singleton method
    static Memory* getMemory();

    // Class Methods
    void create(int);
    void dump(int,int);
    int get_memory(int);
    void printBankHeaders();
    void reset();
    void set(int,int,std::string);
    void set_memory(int,int);

    // Deconstructor
    ~Memory();
};

#endif
