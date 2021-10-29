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

Clock::Clock(Cpu* cpu, Memory* memory, IMemory* imemory) {
    /* Constructor Method for the Clock Class */

    Clock::_cpu = cpu;
    Clock::_memory = memory;
    Clock::_imemory = imemory;

    reset();
    clock_enabled = true;
    const int clk_num = 3;
    char* clk_operations[clk_num] = {"dump", "reset", "tick"};
    Utilities::loadOptions(clk_num, clk_operations, clkOperations);
}

void Clock::doWork() {
    // Variable to control workflow
    bool workToDo = true;

    // Tell all devices we are starting a new tick, allowing
    // them to change state, set counters, etc
    _memory->startTick();
    _cpu->startTick();

    // Continue to loop while ANY device has more work to do
    // on this cycle. Devices often have more work to do to
    // finish an instruction, but it may need to wait for a
    // new tick, and nothing remains for this cycle.
    while (workToDo) {

        // give each device a chance to do some work such as
        // issue requests, process results, change state, etc
        _memory->doCycleWork();
        _cpu->doCycleWork();

        // Poll all devices. Will be true if ANY device
        // has more to do on THIS cycle (not instruction).
        workToDo = _cpu->isMoreCycleWorkNeeded() || _memory->isMoreCycleWorkNeeded();

        // DEBUG: This line can be removed after testing
        // printf("CPU: %s\nMEM: %s\n", _cpu->isMoreCycleWorkNeeded() ? "true" : "false", _memory->isMoreCycleWorkNeeded() ? "true" : "false");
    }

    // DEBUG: This line can be removed after testing
    // printf("Clock::doWork has completed!\n");
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
    if (clock_enabled) {
        // DEBUG: This line can be removed after testing
        // printf("Clock::tick: [%d]\n", cycle);
        doWork();
    }
    cycle += variant;
    return cycle;
}

void Clock::parseInstructions(std::string instructionSet) {
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
                char clockCycles[4];
                instructionSet = Utilities::chunkInstruction(instructionSet, clockCycles);
                int cycles = std::stoi(clockCycles, 0, 10);
                int current_cycle = 0;

                while (current_cycle < cycles) {
                    // DEBUG: This line can be removed after testing
                    // printf("Clock::parseInstructions:tick: %s -> [%d]\n", clockCycles, current_cycle);
                    current_cycle = tick(1);
                }
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
}

Clock* Clock::clk_instance(nullptr);        // Instance Instantiation

Clock* Clock::getClock(Cpu* cpu, Memory* memory, IMemory* imemory) {
    // Singleton Method
    if (clk_instance == nullptr) {
        clk_instance = new Clock(cpu, memory, imemory);
    }
    return clk_instance;
}

Clock::~Clock() {
    // Deconstructor
    delete clk_instance;
    clk_instance = nullptr;
}
