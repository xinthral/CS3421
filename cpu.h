#ifndef CPU_H
#define CPU_H

#include <stdio.h>

class Cpu {
private:
    const char* registry[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
public:
    void dump();
    void reset();
    void set_reg(char*, unsigned char);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
};

// Singleton Method
extern Cpu& getCpu();

#endif
