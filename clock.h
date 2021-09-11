#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>             // uint16_t
#include <stdio.h>              // printf
#include <string>               // std::string

class Clock {
private:
    // Singleton Object
    static Clock* clk_instance;

    // Class Scope Variables
    uint16_t cycle;

    // Private Constructor
    Clock();                    // Forces Public Instantiation

public:
    // Singleton Method
    static Clock * GetInstance();

    // Class Methods
    void dump();
    void reset();
    void tick(int);

    // Deconstructor
    ~Clock();
};

#endif
