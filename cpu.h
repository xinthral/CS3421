#ifndef CPU_H
#define CPU_H

// #include <iomanip>      // std::setiosflags, std::resetiosflags
// #include <iostream>     // std::cout, std::hex, std::endl
#include <map>          // std::map
#include <stdio.h>      // std::prinf
#include <string>       // std::string

class Cpu {
public:
    std::string registry[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
    std::map<std::string, int> registers;

    Cpu();
    void dump();
    void reset();
    void set_reg(std::string, int);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    ~Cpu();
};

// Singleton Method
extern Cpu& getCpu();

#endif
