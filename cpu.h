#ifndef CPU_H
#define CPU_H

class Cpu {
public:
    void reset();
    void set_reg(char*, unsigned char);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void dump();
};

// CPU &getCpu() {
//     static CPU cpu;
//     return cpu;
// }
#endif
