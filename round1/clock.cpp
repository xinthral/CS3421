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
    printf("Clock: %u\n", cycle);
}

void clockParser(char* operation,std::string instructionSet) {
    // Handle Instruction Parsing for Clock Class
}

void Clock::reset() {
    /*
    # The reset command sets the internal counter to zero.
    # Example: "clock reset".
    */
    cycle = 0x0000;
}

void Clock::tick(uint16_t variant) {
    /*
    # The tick command accepts a positive decimal integer
    # indicating how many clock ticks should be issued to
    # attached devices. The internal counter is incremented
    # by the specified number of ticks.
    */
    cycle += variant;
}

extern Clock &getClock() {
    // Returns a statically derived singleton instance of this object
    static Clock clock;
    return clock;
};
