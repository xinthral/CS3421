/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This simple CPU device has 8 one byte data
# registers labeled RA through RH. The CPU also has a 1 byte
# program counter (PC) register that holds the address in
# memory of the next CPU instruction to fetch. For this
# assignment, CPU "instructions" will simply be 1 byte of
# data. On each clock cycle, the CPU will shift the contents
# of each register to the next higher register, such that RH
# receives the content of RG, RG receives what is in RF, and
# so on, until finally, RB receives RA. The CPU will then
# fetch the byte from the Memory Device pointed to by the PC,
# place it into RA, and increment the PC by 1. While the CPU
# doesn’t do anything useful, this behavior is a means to
# test the I/O & memory fetch capabilities of the code.
#**************************************/
#include "cpu.h"

Cpu::Cpu(Memory* memory, IMemory* imemory) : _memory(*memory), _imemory(*imemory) {
    _memory = *memory;
    _imemory = *imemory;
    _pc = 0;
    STATE = 0;
    isWorking = false;
    current_instruction = -1;
    int cpu_num = 3;
    char* cpu_operations[cpu_num] = {"dump", "reset", "set"};
    Utilities::loadOptions(cpu_num, cpu_operations, cpuOperations);
    reset();
}

void Cpu::decodeInstruction() {
    // Take in and decode Instruction from Instruction Memory
    current_executable = ((current_instruction >> 17) & 7);

    // DEBUG: This line can be removed after testing
    printf("Cpu::decodeInstruction: Decode {%X} <- {%X}\n", current_executable, current_instruction);
}

void Cpu::doCycleWork() {
    // DEBUG: This line can be removed after testing
    // printf("Cpu::doCycleWork: Pre-emptive state [%d].\n", STATE);

    if (STATE == 1) {
        fetch_memory();         // initiate fetch cycle
        printf("Fetch Done!\n");
        nextState();            // Advance state to DECODE
        decodeInstruction();    // initiate dedcode cycle
        printf("Decode Done!\n");
        nextState();            // Advance state to MEM_REQ
        executeInstruction();   // Memory Request
        printf("Execution Done!\n");
        nextState();            // Advance state to WAIT

    } else if (STATE == 4 && !(isWorking)) {
        // End Wait State
        incrementPC();
        nextState();
    }
}

void Cpu::dump() {
    /*
    # The "dump" command shows the value of all of the CPU
    # registers. A sample output would be as follows:
    # PC: 0xAA
    # RA: 0x23
    # RB: 0x14
    # RC: 0xFF
    # RD: 0x44
    # RE: 0xAA
    # RF: 0x00
    # RG: 0x09
    # RH: 0x18
    */
    printf("PC: 0x%02X\n", _pc);
    for (int step = 0; step < 8; step++) {
        printf("%s: 0x%02X\n", registrar[step].c_str(), _registers[step]);
    }
}

void Cpu::executeInstruction() {
    // Switch to case statement
    if (current_executable == 5) {
        // lw
        loadWord(current_instruction);
    } else if (current_executable == 6) {
        // sw
        storeWord(current_instruction);
    } else {
        // DEBUG: This line can be removed after testing
        printf("Cpu::executeInstruction: Unimplmemented instruction type: 0x%3X\n", current_executable);
    }
}

void Cpu::fetch_memory() {
    /* Fetch new value from imemory banks and place instruction
    #  into the CPU register slot 'RA'
    */
    int fetch_memory = _pc;
    try {
        if (current_instruction != 0) {
            current_instruction = _imemory.get_memory(fetch_memory);
            if (current_instruction > 0) {
                isWorking = true;       // Set Work Flag

                // DEBUG: This line can be removed after testing
                printf("Cpu::fetch_memory: Fetched Instruction: {%X} <- {%d}\n", current_instruction, fetch_memory);
            }
        } else { isWorking = false; }
    } catch (const std::exception& e) { printf("Cpu::fetch_memory: Error fetching\n\t%s\n", e.what()); }
}

int Cpu::find_register(std::string location){
    // Insert value into registry
    transform(location.begin(), location.end(), location.begin(), ::toupper);

    // Locate position of register
    auto itrLoc = find(registrar, registrar+8, location);
    int dist = std::distance(registrar, itrLoc);

    // DEBUG: This line can be removed after testing
    // printf("Cpu::find_register: Located %s @ %d.\n", location.c_str(), dist);
    return dist;
}

int Cpu::get_register(int register_number) {
    // Takes in a register name and returns the current value stored
    return _registers[register_number];
}

void Cpu::loadWord(int instruction) {
    // Load Word Funciton
    fetchRegister = (((instruction >> 14) | 240 ) & 7);         // x
    int targetMemory = (((instruction >> 8 ) | 240 ) & 7);      // y

    // Get Register
    std::string reg = registrar[fetchRegister];

    // DEBUG: This line can be removed after testing
    // printf("Cpu::loadWord: Loading Word into %s <- M[%d].\n", reg.c_str(), targetMemory);

    // Begin fetch
    _memory.startFetch(get_register(targetMemory), 1, &(_registers[fetchRegister]), &isWorking);
}

void Cpu::incrementPC() {
    // Increment the Program Counter
    _pc += 1;

    // DEBUG: This line can be removed after testing
    printf("Cpu::incrementPC: Counter incremented [%d] -> [%d].\n", (_pc - 1), _pc);
}

bool Cpu::isMoreCycleWorkNeeded() {
    // Check if there more work pending in this clock cycle
    return isWorking;
}

void Cpu::nextState() {
    // Advances Finite State Machine to the next state
    int period = sizeof(STATES) + 1;// - 1;
    STATE = (STATE + 1) % period;

    // DEBUG: This line can be removed after testing
    printf("Cpu::nextState: [%d] -> [%d]\n", STATE, ((STATE+1) % period));
}

void Cpu::parseInstructions(std::string instructionSet) {
    // Parse incoming instructions fro the Cpu Device
    // DEBUG: This line can be removed after testing
    // printf("Cpu Instruction: %s\n", instructionSet.c_str());

    char operation[8];
    instructionSet = Utilities::chunkInstruction(instructionSet, operation);
    int op = cpuOperations[operation];

    switch (op) {
        case 0:
            // dump
            dump();
            break;
        case 1:
            // reset
            reset();
            break;
        case 2: {
                // set reg
                char junk[3], element[6];

                instructionSet = Utilities::chunkInstruction(instructionSet, junk);
                instructionSet = Utilities::chunkInstruction(instructionSet, element);

                int bitValue = std::stoi(instructionSet, 0, 16);
                std::string location = element;

                set_reg(location, bitValue);
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
}

void Cpu::reset() {
    // Reset Memory Registers
    for (int step = 0; step < 8; step++) {
        _registers[step] = 0x00;
    }
}

void Cpu::set_reg(std::string location, int hbyte) {
    // Set register to specified integer;
    int register_location = find_register(location);    // Get index value
    _registers[register_location] = hbyte;              // Set the register

    // DEBUG: This line can be removed after testing
    printf("Cpu::set_reg: Setting %s to %X.\n", location.c_str(), hbyte);
}

void Cpu::startTick() {
    /* Called by clock to tell device a new tick has started. Used by devices to
    # do minimal housekeeping, and transition state. Very little actual work
    # should be done in this function, and is instead done in doCycleWork
    # described below.
    */

    if (STATE == 0) {
        nextState();
    } else if (STATE == 4){
        // Set the program counter and increment the state
        if (isWorking) {
            // DEBUG: This line can be removed after testing
            printf("Cpu::startTick: In Wait state.\n");
        }
    } else {
        // DEBUG: This line can be removed after testing
        printf("Cpu::startTick: Invalid start state: %d.\n", STATE);
    }
}

void Cpu::storeWord(int instruction) {
    // Store word function
    fetchRegister = (((instruction >> 11) | 240 ) & 7);             // x
    int destinationMemory = (((instruction >> 8 ) | 240 ) & 7);     // y

    // DEBUG: This line can be removed after testing
    printf("Cpu::storeWord: Storing Word from %s into M[%d].\n", registrar[fetchRegister].c_str(), destinationMemory);

    // Get Value from requested registry
    int regValue = get_register(destinationMemory);

    // Begin store
    _memory.startStore(regValue, 1, &(_registers[fetchRegister]), &isWorking);
}
