#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string

class Clock {
private:
    static Clock* clk_instance; // Singleton Object
    uint16_t cycle;             // Current cycle of clock
    Clock();                    // Forces Public Instantiation
public:
    // Singleton Method
    static Clock* getClock();

    // Class Methods
    void dump();
    void reset();
    int tick(int);

    // Deconstructor
    ~Clock();
};

#endif
