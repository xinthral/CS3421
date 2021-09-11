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
    reset();
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
        std::printf("%2s: 0x%02X\n", idx, reg.second);
    }
}

void cpuParser(char* operation,std::string instructionSet) {
    // Handle Instruction Parsing for the CPU Class
}

void Cpu::reset() {
    // Reset Memory Registers
    registers.clear();
    int len = *(&registry + 1) - registry;
    for (int step = 0; step < len; step++) {
        registers[registry[step]] = 0x00;
    }
}

void Cpu::set_reg(std::string location, int hbyte) {
    //
    registers.emplace(std::pair<std::string, int>(location, hbyte));
}

Cpu::~Cpu() {
    // Deconstructor
    registers.clear();
}

extern Cpu &getCpu() {
    // Returns a statically derived singleton instance of this object
    static Cpu cpu;
    return cpu;
}