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
// class Cpu;
// class Memory;

class IMemory {
private:
    int DEBUG{};                    // DEBUG level
    int capacity{};                 // Size of memory bank
    int* registry;                  // Memory Banks
    int STATE{};
    std::map<std::string, int> memOperations;
    enum STATES {IDLE=0, WAIT=1, MOVE=2};
public:
    // Constructor
    IMemory(int);

    // Class Methods
    void create(int);
    void dump(int,int,int);
    int get_memory(int);
    void nextState();
    void parseInstructions(std::string);
    void printBankHeaders(int);
    void reset();
    void set(int,std::string);
    void set_memory(int,int);
};

#endif
