#ifndef MEMORY_H
#define MEMORY_H

#include "utilities.h"          // Utility Functions
#include <fstream>              // std::ifstream
#include <stdint.h>             // uint16_t
#include <stdexcept>            // std::out_of_range
#include <stdio.h>              // printf
#include <string>               // std::string, std::stoi
#include <vector>               // std::vector

class Memory {
private:
    int* registry;                  // Memory Banks
    int capacity;                   // Size of memory bank
    std::map<std::string, int> memOperations;
public:
    Memory();                       // Forces Public Instantiation

    // Class Methods
    void create(int);
    void dump(int,int,int);
    int get_memory(int);
    void parseInstructions(std::string);
    void printBankHeaders();
    void reset();
    void set(int,int,std::string);
    void set_memory(int,int);
};

#endif
