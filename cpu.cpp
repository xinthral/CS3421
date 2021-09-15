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

void Cpu::doWork(Clock*& clock, Memory*& memory) {
    // Do the thing
    shift_registers();
    int fetchbyte = registers["PC"];
    fetch_memory(memory, fetchbyte);
    int current_cycle = clock->tick(1);
    set_reg("PC", current_cycle);
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
    registers[location] = hbyte;
}

void Cpu::shift_registers() {
    /*
    # Shifts the CPU registry elements in ascending
    # Alphanumeric order.
    */
    auto it = registers.begin();
    auto ti = registers.end();
    ti++;                           // Increment to skip element

    while(--ti != it) {
        set_reg(std::next(ti)->first.c_str(), ti->second);
    }
}

void Cpu::fetch_memory(Memory*& memory, int position) {
   /* Fetch new value from memory banks and place instruction
   #  into the CPU register slot 'RA'
   */
   int response = memory->get_memory(position);
   // DEBUG: This line can be removed after testing
   printf("CPU Fetched Value: %d\n", response);
   set_reg("RA", response);
}

Cpu* Cpu::cpu_instance(nullptr);        // Instance Instantiation
Cpu* Cpu::getCpu() {
    // Singleton Method
    if (cpu_instance == nullptr) {
        cpu_instance = new Cpu();
    }
    return cpu_instance;
}

Cpu::~Cpu() {
    // Deconstructor
    delete cpu_instance;
    cpu_instance = nullptr;
}
