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
    // printf("Cpu::decodeInstruction: Decode {%X} <- {%X}\n", current_executable, current_instruction);
}

void Cpu::doCycleWork() {
    // DEBUG: This line can be removed after testing
    // printf("Cpu::doCycleWork: Pre-emptive state [%d].\n", STATE);

    if (STATE == 1) {
        // initiate fetch cycle
        fetch_memory();

        // Advance state to DECODE
        nextState();

        // initiate dedcode cycle
        decodeInstruction();

        // Advance state to MEM_REQ
        nextState();

        // Memory Request
        executeInstruction();

        // Advance state to WAIT
        nextState();

    } else if (STATE == 4 && !(isWorking)) {
        // Shift registers in descending alphabetical order
        shift_registers();

        // Set instruction to Registry
        set_reg(registrar[fetchRegister+1], fetchValue);

        // End Wait State
        incrementPC();
        nextState();
    }

    // else if (STATE == 2) {
    //     // initiate dedcode cycle
    // } else if (STATE == 3) {
    //     // Memory Request
    //     executeInstruction();
    // } else if (STATE == 4) {
    //     printf("Cpu::doCycleWork: In Wait state.\n");
    //     if (isWorking) {
    //         isWorking = false;
    //     }
    // }
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
    for (auto reg : registers) {
        const char* idx = reg.first.c_str();
        printf("%2s: 0x%02X\n", idx, reg.second);
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
    int fetchbyte = registers["PC"];
    try {
        if (current_instruction != 0) {
            current_instruction = _imemory.get_memory(fetchbyte);
            if (current_instruction > 0) {
                // Set Work Flag
                isWorking = true;
                // // Shift registers in descending alphabetical order
                // shift_registers();
                // DEBUG: This line can be removed after testing
                printf("Cpu::fetch_imemory: Fetched {%X} <- {%d}\n", current_instruction, fetchbyte);
            }
        } else { isWorking = false; }
    } catch (const std::exception& e) { printf("Cpu::fetch_memory: Error fetching\n\t%s\n", e.what()); }
}

int Cpu::get_register(std::string reg) {
    // Takes in a register name and returns the current value stored
    return registers.at(reg);
}

void Cpu::loadWord(int instruction) {
    // Load Word Funciton
    int targetMemory = ((instruction >> 8 ) | 240 ) & 7;
    fetchRegister = ((instruction >> 14) | 240 ) & 7;

    // DEBUG: This line can be removed after testing
    printf("Cpu::loadWord: Requesting data from M[%d] -> R[%d]\n", targetMemory, fetchRegister);

    // Begin fetch
    _memory.startFetch(targetMemory, 1, &fetchValue, &isWorking);
}

void Cpu::incrementPC() {
    // Increment the Program Counter
    int fetchbyte = registers["PC"];

    // DEBUG: This line can be removed after testing
    printf("Cpu::incrementPC: Counter incremented [%d] -> [%d]\n", fetchbyte, fetchbyte+1);

    // Set PC counter
    set_reg("PC", fetchbyte+1);
    if (fetchbyte > 16) {
        std::abort();
    }
}

bool Cpu::isMoreCycleWorkNeeded() {
    // DEBUG: This line can be removed after testing
    // printf("Cpu::isMoreCycleWorkNeeded not yet implemented\n");
    return isWorking;
}

void Cpu::nextState() {
    // Advances Finite State Machine to the next state
    int period = sizeof(Cpu::STATES) + 1;// - 1;
    // DEBUG: This line can be removed after testing
    // printf("Cpu::nextState: [%d] -> [%d]\n", Cpu::STATE, ((Cpu::STATE+1) % period));
    Cpu::STATE = (Cpu::STATE + 1) % period;
}

void Cpu::parseInstructions(std::string instructionSet) {
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

void Cpu::printRegistry(std::string location) {
    // Prints individual registries rather than whole thing
    std::map<std::string, int>::iterator it = registers.find(location);
    assert(it != registers.end());
    printf("%s: [%d]\n", (it->first).c_str(), it->second);
}

void Cpu::reset() {
    // Reset Memory Registers
    registers.clear();
    int len = 9; //*(&registrar + 1) - registrar;
    for (int step = 0; step < len; step++) {
        registers[registrar[step]] = 0x00;
    }
}

void Cpu::set_reg(std::string location, int hbyte) {
    // Insert value into registry
    transform(location.begin(), location.end(), location.begin(), ::toupper);
    // DEBUG: This line can be removed after testing
    // printf("Setting [%s] = %d\n", location.c_str(), hbyte);
    registers.at(location) = hbyte;
}

void Cpu::shift_registers() {
    /*
    # Shifts the m registry elements in descending
    # Alphanumeric order.
    */
    auto it = registers.begin();
    auto ti = registers.end();
    it--;                           // Decrement to skip element
    ti++;                           // Increment to skip element
    while(--ti != it) {
        set_reg(std::next(ti)->first.c_str(), ti->second);
    }
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
            // printf("Cpu::startTick: In Wait state.\n");
        }
    } else {
        // DEBUG: This line can be removed after testing
        printf("Cpu::startTick: Invalid start state: %d.\n", STATE);
    }
}

void Cpu::storeWord(int instruction) {
    // Store word function
    isWorking = true;
    int targetRegister = ((instruction >> 11) | 240 ) & 7;
    int destinationMemory = ((instruction >> 8 ) | 240 ) & 7;

    // DEBUG: This line can be removed after testing
    printf("Cpu::storeWord: Decode Instruction [%X]\n\tRegister [%d] -> Memory [%d]\n", instruction, targetRegister, destinationMemory);
    std::string reg = registrar[targetRegister];

    unsigned targetValue = get_register(reg);
    _memory.startStore(destinationMemory, 1, &targetValue, &isWorking);
}
