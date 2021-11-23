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

Clock::Clock(Cpu* cpu, Memory* memory, IMemory* imemory, int debug) {
    /* Constructor Method for the Clock Class */
    _cpu = cpu;
    _memory = memory;
    _imemory = imemory;

    const int clk_option_num = 3;
    char* clk_operations[clk_option_num] = {"dump", "reset", "tick"};
    Utilities::loadOptions(clk_option_num, clk_operations, clkOperations);

    DEBUG = debug;                      // Set debug flag
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

        if (DEBUG > 2) {
            // DEBUG: This line can be removed after testing
            printf("Clock::doWork: CPU: %s\tMEM: %s\n",
                _cpu->isMoreCycleWorkNeeded() ? "true" : "false",
                _memory->isMoreCycleWorkNeeded() ? "true" : "false"
            );
        }
    }
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
    clock_enabled = _cpu->isClockEnabled();
    if (clock_enabled) {
        if (DEBUG > 3) {
            // DEBUG: This line can be removed after testing
            printf("Clock::tick: [%d]\n", cycle);
        }
        doWork();
    }
    cycle += variant;
    return cycle;
}

void Clock::parseInstructions(std::string instructionSet) {
    if (DEBUG > 3) {
        // DEBUG: This line can be removed after testing
        printf("Clock::parseInstructions: Instruction Set: %s\n", instructionSet.c_str());
    }

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
                int junk = 0;

                while (current_cycle < cycles) {
                    if (DEBUG > 0) {
                        // DEBUG: This line can be removed after testing
                        printf("Clock::parseInstructions:tick: %s -> [%d]\n", clockCycles, current_cycle);
                    }
                    junk = tick(1);
                    current_cycle++;
                }
            }
            break;
        default:
            printf("Error: Clock::parseInstructions recieved a bad operation < %s >.\n", operation);
    }
}

Clock* Clock::clk_instance(nullptr);        // Instance Instantiation

Clock* Clock::getClock(Cpu* cpu, Memory* memory, IMemory* imemory, int debug) {
    // Singleton Method
    if (clk_instance == nullptr) {
        clk_instance = new Clock(cpu, memory, imemory, debug);
    }
    return clk_instance;
}

Clock::~Clock() {
    // Deconstructor
    delete clk_instance;
    clk_instance = nullptr;
}
