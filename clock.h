#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>

class Clock {
private:
    // Class Scope Variables
    uint16_t cycle;

public:
    Clock();

    // Class Methods
    void dump();
    void clockParser(char*,std::string);
    void reset();
    void tick(uint16_t);
};

// Singleton method
extern Clock& getClock();

#endif
