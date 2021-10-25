#ifndef MEMORY_H
#define MEMORY_H

#include "utilities.h"          // Utility Functions
#include <fstream>              // std::ifstream
#include <stdint.h>             // uint16_t
#include <stdexcept>            // std::out_of_range
#include <stdio.h>              // printf
#include <string.h>             // std::string, std::stoi
#include <vector>               // std::vector

class Memory {
private:
    int* answerPtr;                     // startFetch answer reponse pointer
    int capacity;                       // Size of memory bank
    int instructionType;                // Type of instruction to execute on
    int fetchCount;                     // startFetch number of elements
    int latencyFactor;                  // startTick data memory device delay
    int* registry;                      // Memory Banks
    int startPos;                       // startFetch starting position
    int STATE;                          // State for FSM
    int waitDelay;                      // startTick delay counter
    bool isWorking;                     // Is device busy
    bool* workResponse;                 // startFetch isWorking response pointer
    std::map<std::string, int> memOperations;
    enum STATES {IDLE=0, WAIT=1, MOVE_DATA=2};

public:
    Memory();                           // Forces Public Instantiation

    // Class Methods
    void create(int);
    void doCycleWork();
    void dump(int,int,int);
    int get_memory(int);
    bool isMoreCycleWorkNeeded();
    void nextState();
    void parseInstructions(std::string);
    void printBankHeaders(int);
    void reset();
    void set(int,int,std::string);
    void set_memory(int,int);
    void startFetch(int,int,int*, bool*);
    void startStore(int,int,int*, bool*);
    void startTick();
};

#endif
