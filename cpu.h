#ifndef CPU_H
#define CPU_H

#include <algorithm>            // std::transform
#include <cassert>              // assert
#include <cmath>                // log2
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
protected:
    int DEBUG{};                                // Debug output control

private:
    /* Device Objects */
    Memory& _memory;
    IMemory& _imemory;

    /* Binary Handling Variables */
    int previous_instruction{};                 // Previous Cycle Operation Instruction
    int current_executable{};                   // Current CPU instruction
    int current_instruction{};                  // Current Operation Instruction
    int current_DDD{};                          // Current DDD
    int current_SSS{};                          // Current SSS
    int current_TTT{};                          // Current TTT
    int current_III{};                          // Current III
    int current_UHF{};                          // Current Upper Half of III
    int current_LHF{};                          // Current Lower Half of III

    bool _clock_enabled;                        // Control if clock is enabled
    bool isMemoryWorking;                       // Boolean flag while working
    bool isCycleWorkPending;
    int _registers[8] = { 0 };                  // Register Bank
    int STATE{};                                // Current State
    int _pc{};                                  // Program Counter
    std::map<std::string,int> cpuOperations;
    std::map<std::string,int> STATES;

    std::string registrar[8] = {"RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    enum STATEMODE { IDLE, FETCH, DECODE, REQUEST, WAIT };
    enum EXC { ADD, ADDI, MUL, INV, BRANCH, LW, SW, HALT };
    enum EXCB { BEQ, BNEQ, BLT };
    enum BITIES { NNN, DDD, SSS, TTT, III, UHF, LHF };

public:

    Cpu(Memory*,IMemory*,int);          // Constructor
    void decodeInstruction();           // Decode IMemory Instruction
    void doCycleWork();                 // Main Work Loop
    void dump();                        // Display Register Information
    void executeInstruction();          // Execute on current_executable
    void fetch_memory();                // Fetch Instruction from IMemory
    int find_register(std::string);     // Convert register name to index
    int get_register(int);
    void incrementPC();
    bool isClockEnabled();
    bool isMoreCycleWorkNeeded();
    void instruction_add();             // Instruction : add
    void instruction_addi();            // Instruction : addi
    void instruction_branch();          // Instruction : branch
    void instruction_beq();             // Instruction : beq
    void instruction_blt();             // Instruction : blt
    void instruction_bneq();            // Instruction : bneq
    void instruction_inv();             // Instruction : inv
    void instruction_halt();            // Instruction : halt
    void instruction_lw();              // Instruction : lw
    void instruction_mul();             // Instruction : mul
    void instruction_sw();              // Instruction : sw
    int instructionBitSelector(int,int);// Return bitwise sections of IMemory
    void nextState();
    void parseInstructions(std::string);
    void reset();
    void set_reg(std::string,int);      // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void startTick();
};

#endif
