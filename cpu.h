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

    int STATE;
    int current_executable;                     // CPU instruction
    int current_instruction;                    // Entire Operation Instruction
    bool isWorking;                             // Boolean flag while working
    unsigned int fetchValue;                    // Value fetch from request
    int fetchRegister;                          // Location for fetch value 

    std::map<std::string,int> registers;
    std::map<std::string,int> cpuOperations;

    std::string registrar[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    enum STATES { IDLE=0, FETCH=1, DECODE=2, MEM_REQ=3, WAIT=4 };

public:

    Cpu(Memory*, IMemory*);             // Constructor
    void decodeInstruction();           // Decode IMemory Instruction
    void doCycleWork();                 // Main Work Loop
    void dump();                        // Display Register Information
    void executeInstruction();          // Execute on current_executable
    void fetch_memory();                // Fetch Instruction from IMemory
    int get_register(std::string);
    void incrementPC();
    bool isMoreCycleWorkNeeded();
    void loadWord(int);
    void nextState();
    void parseInstructions(std::string);
    void printRegistry(std::string);
    void reset();
    void set_reg(std::string,int);      // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void shift_registers();
    void startTick();
    void storeWord(int);
};

#endif
