#ifndef CPU_H
#define CPU_H

class Cpu {
private:
    const char* registry[9] = {"PC", "RA", "RB", "RC", "RD", "RE", "RF", "RG", "RH"};
public:
    Cpu();
    void reset();
    void set_reg(char*, unsigned char);     // ([RA-RH,PC], HEX) -> (RB, 0xAA)
    void dump();
    ~Cpu();
};
#endif
