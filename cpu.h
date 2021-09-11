#ifndef CPU_H
#define CPU_H

#include <map>                  // std::map
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
    // Singleton Method
    static Cpu* getCpu();
    void dump();
    void reset();
    void set_reg(std::string, int);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    ~Cpu();
};

#endif
