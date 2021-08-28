#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <stdint.h>

class Clock {
private:
    // Class Scope Variables
    uint16_t cycle;

public:
    Clock();
    // Singleton Methods
    Clock& getClock();

    // Class Methods
    void reset();
    void tick(uint16_t);
    void dump();
    ~Clock();
};
#endif
