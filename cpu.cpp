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
# test the I/O & memory fetch capabilities of the code.
# doesn’t do anything useful, this behavior is a means to
#**************************************/
#include "cpu.h"

Cpu::Cpu(Memory* memory, IMemory* imemory) : _memory(*memory), _imemory(*imemory) {
    _memory = *memory;
    _imemory = *imemory;

    const int cpu_option_num = 3;
    const int cpu_states_count = 5;

    char* cpu_states[cpu_states_count] = {"IDLE", "FETCH", "DECODE", "MEM_REQ", "WAIT"};
    char* cpu_operations[cpu_option_num] = {"dump", "reset", "set"};

    Utilities::loadOptions(cpu_states_count, cpu_states, STATES);
    Utilities::loadOptions(cpu_option_num, cpu_operations, cpuOperations);

    _pc = 0;
    STATE = 0;
    isMemoryWorking = false;
    isCycleWorkPending = false;
    current_instruction = -1;
    reset();
}

void Cpu::decodeInstruction() {
    // Take in and decode Instruction from Instruction Memory
    current_executable = ((current_instruction >> 17) & 7);

    // DEBUG: This line can be removed after testing
    // printf("Cpu::decodeInstruction: Decode {%X} <- {%X}\n", current_executable, current_instruction);
}

void Cpu::doCycleWork() {
    // DEBUG: This line can be removed after testing
    // printf("Cpu::doCycleWork: Are we waiting? [%s].\n", isMemoryWorking ? "true" : "false");
    if (STATE == 1 && (!isMemoryWorking)) {
        fetch_memory();         // initiate fetch cycle
        nextState();
        decodeInstruction();    // initiate dedcode cycle
        nextState();
        executeInstruction();   // Memory Request
        nextState();
        isCycleWorkPending = false;
    } else if (4 == STATE) {
        if (false == isMemoryWorking) {
            // End Wait State
            current_instruction = -1;
            isCycleWorkPending = false;
            nextState();
            incrementPC();
        }
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
    printf("\n");
}

void Cpu::executeInstruction() {
    // Switch to case statement
    // DEBUG: This line can be removed after testing
    // printf("Cpu::executeInstruction: Case %d\n", current_executable);
    switch (current_executable) {
        case 0: {
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstrucion:add %X\n", current_instruction);
            }
            break;
        case 1: {
            // addi
            // add
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstrucion:addi %X\n", current_instruction);
            }
            break;
        case 2: {
            // mul
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstrucion:mul %X\n", current_instruction);

            }
            break;
        case 3: {
            // inv
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstrucion:inv %X\n", current_instruction);

            }
            break;
        case 4: {
            // branch
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstrucion:branching %X\n", current_instruction);

            }
            break;
        case 5: {
            // lw
            // DEBUG: This line can be removed after testing
            // printf("Cpu::executeInstrucion:loadWord %X\n", current_instruction);
            loadWord(current_instruction);
            }
            break;
        case 6: {
            // sw
            // DEBUG: This line can be removed after testing
            // printf("Cpu::executeInstrucion:storeWord %X\n", current_instruction);
            storeWord(current_instruction);
            }
            break;
        case 7: {
            // halt
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstrucion:halt %X\n", current_instruction);
            }
            break;
        default:
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstruction: Unimplmemented instruction type: %d\n", current_executable);
            break;
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
                isMemoryWorking = true;       // Set Work Flag
                isCycleWorkPending = true;

                // DEBUG: This line can be removed after testing
                // printf("Cpu::fetch_memory: Fetched Instruction: {%X} <- {%d}\n", current_instruction, fetch_memory);
            }
        } else { isMemoryWorking = false; }
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

    // DEBUG: This line can be removed after testing
    // std::string reg = registrar[fetchRegister];
    // printf("Cpu::loadWord: Loading Word into %s <- M[%d].\n", reg.c_str(), targetMemory);

    // Begin fetch
    _memory.startFetch(get_register(targetMemory), 1, &(_registers[fetchRegister]), &isMemoryWorking);
}

void Cpu::incrementPC() {
    // Increment the Program Counter
    _pc += 1;

    // DEBUG: This line can be removed after testing
    // printf("\nCpu::incrementPC: Counter incremented [%X] -> [%X].\n\n", (_pc - 1), _pc);
}

bool Cpu::isMoreCycleWorkNeeded() {
    // Check if there more work pending in this clock cycle
    // DEBUG: This line can be removed after testing
    // printf("Cpu::isMoreCycleWorkNeeded: isCycleWorkPending %s\n", isCycleWorkPending ? "true" : "false");

    return isCycleWorkPending;
}

void Cpu::nextState() {
    // Advances Finite State Machine to the next state
    int period = STATES.size();
    int previousState = STATE;

    STATE = (STATE + 1) % period;               // Cycle States

    // DEBUG: This line can be removed after testing
    // printf("Cpu::nextState: [%d] -> [%d]\n", previousState, STATE);
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
                char junk[4], element[8];

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
    if ("PC" != location) {
        int register_location = find_register(location);    // Get index value
        _registers[register_location] = hbyte;              // Set the register
    } else {
        _pc = hbyte;
    }
    // DEBUG: This line can be removed after testing
    // printf("Cpu::set_reg: Setting %s to %X.\n", location.c_str(), hbyte);
}

void Cpu::startTick() {
    /* Called by clock to tell device a new tick has started. Used by devices to
    # do minimal housekeeping, and transition state. Very little actual work
    # should be done in this function, and is instead done in doCycleWork
    # described below.
    */
    // DEBUG: This line can be removed after testing
    // printf("Cpu::startTick: Current State %d : %s.\n", STATE, isMemoryWorking ? "true" : "false");

    if (STATE == 0) {
        nextState();
    } else if (STATE == 4){
        // Wait state, chillin
    } else {
        // DEBUG: This line can be removed after testing
        printf("Cpu::startTick: Invalid start state: %d.\n", STATE);
        // STATE = 1;
    }
}

void Cpu::storeWord(int instruction) {
    // Store word function
    fetchRegister = ((instruction >> 11) | 240 ) & 7;             // x
    int destinationMemory = ((instruction >> 8 ) | 240 ) & 7;     // y

    int targetIdx = get_register(fetchRegister);
    int targetVal = get_register(destinationMemory);

    // DEBUG: This line can be removed after testing
    // printf("Cpu::storeWord: Storing Word from %s into M[%d].\nIdx: %d\tVal: %d\n", registrar[fetchRegister].c_str(), destinationMemory, targetIdx, targetVal);

    // Begin store
    _memory.startStore(targetIdx, 1, &(_registers[destinationMemory]), &isMemoryWorking);
}
