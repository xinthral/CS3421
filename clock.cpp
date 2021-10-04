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
    const int clk_num = 3;
    char* clk_operations[clk_num] = {"dump", "reset", "tick"};
    Utilities::loadOptions(clk_num, clk_operations, clkOperations);
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
    // if (clock_enabled) {
    //     _cpu->doWork();
    //     _memory->doWork();
    // }
    return cycle;
}

void Clock::parseInstructions(Cpu* _cpu, Memory* _memory, std::string instructionSet) {
    // DEBUG: This line can be removed after testing
    // printf("Clock Instruction: %s\n", instructionSet.c_str());

    char operation[8];
    instructionSet = Utilities::chunkInstruction(instructionSet, operation);
    int op = clkOperations[operation];

    switch (op) {
        case 0:
            // dump
            dump();
            break;
        case 1:
            // reset
            reset();
            break;
        case 2: {
                // tick
                char clockCycles[3];
                instructionSet = Utilities::chunkInstruction(instructionSet, clockCycles);
                int cycles = std::stoi(clockCycles, 0, 16);
                int sentinal = 0;
                int current_cycle = _cpu->get_register("PC");
                while (sentinal++ < cycles) {
                    tick(1);
                    current_cycle++;
                    _cpu->fetch_memory(_memory, current_cycle);
                }
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
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
