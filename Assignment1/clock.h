#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>              // printf
#include <string>               // std::string

class Clock {
private:
    static Clock* clk_instance; // Singleton Object
    int cycle;                  // Current cycle of clock
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
