/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/
#include "memory.h"

void Memory::create(uint16_t inputSize) {
    // Constructor
    banks = new int[inputSize];
    bankSize = inputSize;
}

void Memory::dump(int begin, int number_of_elements) {
    /* The dump command shows the contents of memory starting at
    # address <address>, and continuing for <count> bytes. The
    # output should begin with a header showing "Addr", 1 space,
    # and then 00-0F with a single space between each. Subsequent
    # lines are formatted such that each line begins with a 1
    # byte address (0x and 2 digit upper case hex characters)
    # that is an even multiple of 16, followed by a single space.
    # Following that, up to 16 bytes of data, in 2 digit upper
    # case hex is printed. If the address is not a multiple of 16,
    # blank spaces should be printed until the address is reached.
    #   Example: "memory dump 0x04 0x20"
    */
    int displayCursor=0, displayWidth=16, rowCount=0;
    int beginning = (begin) * 2;
    int ending = (begin + number_of_elements) * 2;
    printf("Ending: %d\n", ending);
    printBankHeaders();
    printf("0x%02X", rowCount);
    for (int step = 0; step < bankSize; step++) {

        if (displayCursor == displayWidth) {
            printf("\n0x%02X", rowCount);
            displayCursor = 0;
            rowCount++;
        }
        if (step >= beginning && step < ending) {
            printf(" %02X", *(banks + step));
        } else {
            printf(" %2s", "");
        }
        step++;
        displayCursor++;
    }
    printf("\n");
}

void memoryParser(char* operation,std::string instructionSet) {
    // Handle Instruction Parsing for the Memory Class
}

void Memory::printBankHeaders() {
    std::string bits[16] = {"00", "01", "02", "03", "04", "05",
    "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F"};
    printf("%4s", "Addr");
    for (auto bit : bits){
        printf(" %2s", bit.c_str());
    }
    printf("\n");
}

void Memory::reset() {
    /*
    # The "reset" command causes all of the allocated
    # memory to be set to zero.
    #   Example: "memory reset"
    */
    for (int step = 0; step < bankSize; step++) {
        banks[step] = 0x00;
    }
    bankSize = 0;
}

Memory::~Memory() {
    // Deconstructor
    delete[] banks;
}

extern Memory &getMemory() {
   // Returns a statically derived singleton instance of this object
   static Memory memory;
   return memory;
}
