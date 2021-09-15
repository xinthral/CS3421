#ifndef CPU_H
#define CPU_H

#include <algorithm>            // std::transform
#include <cassert>              // assert
#include "clock.h"              // Internal Clock Object
#include <iterator>             // std::next
#include <map>                  // std::map
#include "memory.h"             // Internal Memory Object
#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string

class Cpu {
private:
    static Cpu* cpu_instance;
    std::string registrar[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    std::map<std::string, int> registers;
    Cpu();                      // Forces Public Instantiation
public:
    static Cpu* getCpu();       // Singleton instantiation
    void doWork(Clock*&, Memory*&);
    void dump();
    void fetch_memory(Memory*&, int);
    void printRegistry(std::string);
    void reset();
    void set_reg(std::string, int);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void shift_registers();
    ~Cpu();
};

#endif
