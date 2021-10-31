#ifndef CPU_H
#define CPU_H

#include <algorithm>            // std::transform
#include <cassert>              // assert
#include "clock.h"              // Internal Clock Object
#include "utilities.h"          // Local Helper Functions
#include <iterator>             // std::next
#include <map>                  // std::map
#include "memory.h"             // Internal Memory Object
#include <stdio.h>              // printf
#include <string.h>             // std::string, strcmp

// Forward Declarations
class Memory;
class IMemory;

class Cpu {
private:
    Memory& _memory;
    IMemory& _imemory;

    int current_executable{};                   // CPU instruction
    int current_instruction{};                  // Entire Operation Instruction
    int fetchRegister{};                        // Location for fetch value
    unsigned int fetchValue;                    // Value fetch from request
    bool isMemoryWorking;                       // Boolean flag while working
    bool isCycleWorkPending;
    int STATE{};

    // std::map<std::string,int> registers;
    int _registers[8] = { 0 };                  // Register Bank
    int _pc{};                                  // Program Counter
    std::map<std::string,int> cpuOperations;
    std::map<std::string,int> STATES;

    std::string registrar[8] = {"RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    enum STATES { IDLE=0, FETCH=1, DECODE=2, REQUEST=3, WAIT=4 };
    enum EXC { ADD=0, ADDI=1, MUL=2, INV=3, BRANCH=4, LW=5, SW=6, HALT=7 };

public:

    Cpu(Memory*, IMemory*);             // Constructor
    void addRegisters(int,int,int);                // Instruction : add
    void decodeInstruction();           // Decode IMemory Instruction
    void doCycleWork();                 // Main Work Loop
    void dump();                        // Display Register Information
    void executeInstruction();          // Execute on current_executable
    void fetch_memory();                // Fetch Instruction from IMemory
    int find_register(std::string);     // Convert register name to index
    int get_register(int);
    void incrementPC();
    bool isMoreCycleWorkNeeded();
    void loadWord(int);                 // Instruction : lw
    void nextState();
    void parseInstructions(std::string);
    void reset();
    void set_reg(std::string,int);      // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void startTick();
    void storeWord(int);                // Instruction : sw
};

#endif
