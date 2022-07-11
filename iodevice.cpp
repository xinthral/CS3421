/**************************************
# Author: Jesse Hassell
# Date: Dec, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

#include "iodevice.h"

IODevice::IODevice(int debug) : DEBUG(debug) {
    // _register = 0;
    reset();
    const int iod_option_num = 3;
    char* iod_operations[iod_option_num] = {"reset", "load", "dump"};
    Utilities::loadOptions(iod_option_num, iod_operations, iodOperations);
}

void IODevice::dump() {
    /* The "dump" command prints the contents of the register in hex, followed
    by a blank line. With a register contents of 0x23, the command "iodev dump"
    would produce the following:
        IO Device: 0x23
    */
    printf("IO Device: 0x%X\n\n", 35);
}

void IODevice::load(std::string fileName) {
    /* The "load" command takes the name of a file that contains a list of "I/O
    schedule events" (no more than 100). An I/O schedule event is as follows:
        <clock tick> <read|write> <address> [value]
    The "clock tick" is a base 10 number that indicates on what clock tick the
    operation is to begin execution. Ticks will always be increasing in value.
    The "read" or "write" indicate the type of operation to perform on Data
    Memory. For a read operation, the value returned from memory is stored in
    the register. A write does not modify the register. The "address" is a hex
    value that indicates the address in memory on which to operate. The "value"
    is hex number included only with the "write" operation, and indicates the
    data to be written to memory. For example:
        6 read 0x10
        16 read 0xA0
        23 write 0xEE 0x27
        30 read 0xEE
    Reads and writes to memory will take the usual 5 clock ticks to complete.
    The programmer may assume sufficient time between I/O schedule events is
    given for each to complete. The programmer may also assume that only a
    single device is ever accessing Data Memory at a time. Note the CPU may be
    access cache while the I/O device accesses memory.
    */

    // NEEDS WORK
}

void IODevice::parseInstructions(std::string instructionSet) {
    if (DEBUG > 3) {
        // DEBUG: This line can be removed after testing
        printf("IODevice::parseInstructions: Instruction Set: %s\n", instructionSet.c_str());
    }

    char operation[10];
    instructionSet = Utilities::chunkInstruction(instructionSet, operation);
    int op = iodOperations[operation];

    switch (op) {
        case 0:
            // Reset
            reset();
            break;
        case 1:
            // Load
            load(instructionSet);
            break;
        case 2:
            // Dump
            dump();
            break;
        default:
            // Catch-all condition incase command is invalid.
            printf("Error: IODevice::parseInstructions recieved a bad operation < %s >.\n", operation);
    }
}

void IODevice::reset() {
    /* The "reset" command causes the I/O Device to be reset, and sets the 8 bit
    register to zero.
    */
    _register = 0;
}

void IODevice::startTick(int cycle) {
    int jobs[]{6, 7, 11};
    for (int task : jobs) {
        if (task == cycle) {
            // printf("%d\n", task);
        }
    }
}
