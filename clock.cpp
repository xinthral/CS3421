/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: The clock device is the heart of the system,
# providing synchronization between all other devices. On
# command, it provides a “tick pulse” to all other devices
# that need a clock. For diagnostic purposes, the clock
# will maintain a monotonically increasing unsigned 16 bit
# count that can be displayed.
**************************************/
#include "clock.h"

Clock::Clock() {
    /* Constructor Method for the Clock Class */
    Clock::reset();
}

Clock& Clock::getClock() {
    extern Clock clock;
    return clock;
}

void Clock::reset() {
    /*
    # The reset command sets the internal counter to zero.
    # Example: "clock reset".
    */
    Clock::cycle = 0;
}

void Clock::tick(uint16_t variant) {
    /*
    # The tick command accepts a positive decimal integer
    # indicating how many clock ticks should be issued to
    # attached devices. The internal counter is incremented
    # by the specified number of ticks.
    */
    Clock::cycle += variant;
}

void Clock::dump() {
    /*
    # The dump command shows "Clock: " followed by the value of the
    # internal clock in decimal. Example: "clock dump" might show:
    # Clock: 148
    */
    //const char* cycle_str = reinterpret_cast<const char*>(Clock::cycle);
    printf("Clock: %u", cycle);
}

Clock::~Clock() {}
