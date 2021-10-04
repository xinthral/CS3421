#ifndef IMEMORY_H
#define IMEMORY_H

#include "utilities.h"          // Utility Functions
#include <fstream>              // std::ifstream
#include <stdint.h>             // uint16_t
#include <stdexcept>            // std::out_of_range
#include <stdio.h>              // printf
#include <string>               // std::string, std::stoi
#include <vector>               // std::vector

class IMemory {
private:
    int* registry;                  // Memory Banks
    int capacity;                   // Size of memory bank
    std::map<std::string, int> memOperations;
public:
    // Constructor
    IMemory();

    // Class Methods
    void create(int);
    void dump(int,int,int);
    int get_memory(int);
    void loadWord(int,int,int);
    void storeWord(int,int,int);

    void parseInstructions(std::string);
    void printBankHeaders();
    void reset();
    void set(int,std::string);
    void set_memory(int,int);
};

#endif
