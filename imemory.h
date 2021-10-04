#ifndef IMEMORY_H
#define IMEMORY_H

#include "cpu.h"                // Internal CPU object
#include "memory.h"             // Internal Memory Object
#include "utilities.h"          // Utility Functions
#include <fstream>              // std::ifstream
#include <stdint.h>             // uint16_t
#include <stdexcept>            // std::out_of_range
#include <stdio.h>              // printf
#include <string>               // std::string, std::stoi
#include <vector>               // std::vector

// Forward Declarations
class Cpu;
class Memory;

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
    void loadWord(Cpu*,Memory*,int);
    void storeWord(Cpu*,Memory*,int);

    void parseInstructions(Cpu*,Memory*,std::string);
    void printBankHeaders();
    void reset();
    void set(Cpu*,Memory*,int,std::string);
    void set_memory(int,int);
};

#endif
