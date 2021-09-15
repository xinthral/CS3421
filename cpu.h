#ifndef CPU_H
#define CPU_H

#include <algorithm>            // std::transform
#include <iterator>             // std::next
#include <map>                  // std::map
#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string
#include <cassert>              // assert

class Cpu {
private:
    static Cpu* cpu_instance;
    std::string registrar[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    std::map<std::string, int> registers;
    Cpu();                      // Forces Public Instantiation
public:
    // Singleton Method
    static Cpu* getCpu();
    void dump();
    void printRegistry(std::string);
    void reset();
    void set_reg(std::string, int);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void shift_registers();
    ~Cpu();
};

#endif
