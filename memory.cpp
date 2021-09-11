/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/
#include "memory.h"

Memory::Memory() {
}

void Memory::create(uint16_t inputSize) {
    /* The "create" command accepts a single integer parameter
    # which indicates the size of the memory in bytes.
    #   Example: "memory create 0x10000".
    */
    for (uint16_t i = 0; i < inputSize; i++) {
        registry.push_back(0);
    }
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
    int beginning = (begin);// * 2;
    int ending = (begin + number_of_elements);// * 2;
    printBankHeaders();
    printf("0x%02X", rowCount);
    for (int step = 0; step < registry.size(); step++) {

        if (displayCursor == displayWidth) {
            printf("\n0x%02X", rowCount);
            displayCursor = 0;
            rowCount++;
        }
        if (beginning <= step && step <= ending) {
            printf(" %02X", registry.at(step));
        } else {
            printf(" %2s", "");
        }
        displayCursor++;
    }
    printf("\n");
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
    // for (int step = 0; step < registry.size(); step++) {
    //     registry[step] = 0x00;
    // }
    registry.empty();
}

void Memory::set(int starting, int number_of_elements, std::string elements) {
    /* The set commands initializes memory to a user
    # supplied set of values. The "hex address" specifies
    # where to begin setting memory values, "hex count"
    # is how many bytes will be assigned, and is followed
    # by "hex count" number of hex bytes, separated by a
    # single space. For this assignment, the command will
    # never be used with more than 100 hex bytes.
    #   Example: "memory set 0x10 0x05 0x08 0xDE 0xAD 0xBE 0xEF"
    */
    int ending = (starting + number_of_elements), value;
    char chunk[6];
    for (int i = 0; i < registry.size(); i++) {
        if (starting <= i && i < ending) {
            elements = Utilities::chunkInstruction(elements, chunk);
            value = std::stoi(chunk, 0, 16);
            printf("Set Memory: %d\n", value);
            registry[i] = value;
        }
    }
}

void Memory::set_memory(int position, int hexValue) {
    registry[position] = hexValue;
}

Memory* Memory::mem_instance(nullptr);      // Instance Instantiation
Memory* Memory::getMemory() {
    // Singleton Method
    if (mem_instance == nullptr) {
        mem_instance = new Memory();
    }
    return mem_instance;
}

Memory::~Memory() {
    // Deconstructor
    delete mem_instance;
    mem_instance = nullptr;
}
