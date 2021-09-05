#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf

class Clock {
private:
    // Class Scope Variables
    uint16_t cycle;

public:
    Clock();

    // Class Methods
    void reset();
    void tick(uint16_t);
    void dump();
};

// Singleton method
extern Clock& getClock();

#endif
