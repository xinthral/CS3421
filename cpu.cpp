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

Cpu::Cpu() {
    STATE = 0;
    isWorkPending = false;
    int cpu_num = 3;
    char* cpu_operations[cpu_num] = {"dump", "reset", "set"};
    Utilities::loadOptions(cpu_num, cpu_operations, cpuOperations);
    reset();
}

void Cpu::doCycleWork() {
    // DEBUG: This line can be removed after testing
    printf("Cpu::doCycleWork: Implementation required.\n");
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

void Cpu::fetch_memory(IMemory* _imemory) {
    /* Fetch new value from memory banks and place instruction
    #  into the CPU register slot 'RA'
    */
    int fetchbyte = registers["PC"];
    int response = _imemory->get_memory(fetchbyte);
    //
    // DEBUG: This line can be removed after testing
    // printf("Cpu::fetch_memory: Fetched {%d} <- {%d}\n", response, fetchbyte);

    // Shift registers in descending alphabetical order
    // shift_registers();

    // Set retrieved value to the RA register
    // set_reg("RA", response);

    // Set the program counter
    incrementPC();
    // set_reg("PC", fetchbyte+1);
    // DEBUG: This line can be removed after testing
    // printf("Refactor Cpu::fetch_memory\n");
}

int Cpu::get_register(std::string reg) {
    return registers.at(reg);
}

void Cpu::incrementPC() {
    // Increment the Program Counter
    int fetchbyte = registers["PC"];
    set_reg("PC", fetchbyte+1);
}

bool Cpu::isMoreCycleWorkNeeded() {
    // return ((STATE == 0) && isWorkPending);
    // DEBUG: This line can be removed after testing
    // printf("Cpu::isMoreCycleWorkNeeded not yet implemented\n");
    return false;
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
    # Shifts the CPU registry elements in descending
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
    STATE = (STATE += 1) % sizeof(STATE);

    // DEBUG: This line can be removed after testing
    // printf("Cpu::startTick: State change [%d] -> [%d]\n", STATE - 1, STATE);
}
