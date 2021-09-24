/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: The clock device is the heart of the system,
# providing synchronization between all other devices. On
# command, it provides a "tick pulse" to all other devices
# that need a clock. For diagnostic purposes, the clock
# will maintain a monotonically increasing unsigned 16 bit
# count that can be displayed.
**************************************/
#include "clock.h"

Clock::Clock() {
    /* Constructor Method for the Clock Class */
    reset();
}

void Clock::dump() {
    /*
    # The dump command shows "Clock: " followed by the value of the
    # internal clock in decimal. Example: "clock dump" might show:
    # Clock: 148
    */
    printf("\nClock: %d\n", cycle);
}

void Clock::reset() {
    /*
    # The reset command sets the internal counter to zero.
    # Example: "clock reset".
    */
    cycle = 0;
}

int Clock::tick(int variant) {
    /*
    # The tick command accepts a positive decimal integer
    # indicating how many clock ticks should be issued to
    # attached devices. The internal counter is incremented
    # by the specified number of ticks.
    */
    cycle += variant;
    return cycle;
}

Clock* Clock::clk_instance(nullptr);        // Instance Instantiation

Clock* Clock::getClock() {
    // Singleton Method
    if (clk_instance == nullptr) {
        clk_instance = new Clock();
    }
    return clk_instance;
}

Clock::~Clock() {
    // Deconstructor
    delete clk_instance;
    clk_instance = nullptr;
}
