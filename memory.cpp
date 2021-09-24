/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/
#include "memory.h"

Memory::Memory() {
    // create(0x0F);
    capacity = 0;
}

void Memory::create(int inputSize) {
    /* The "create" command accepts a single integer parameter
    # which indicates the size of the memory in bytes.
    #   Example: "memory create 0x10000".
    */
    // for (int i = 0; i < inputSize; i++) {
    //     registry.push_back(0x00);
    // }
    registry = new int[inputSize];
    capacity = inputSize;
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
    int displayCursor=16, displayWidth=16, rowCount=0;
    int beginning = (begin);
    int ending = (begin + number_of_elements);
    printBankHeaders();
    int startRow = (begin + 1) / 16;
    int endRow = ending / 16;

    for (int step = 0; step < capacity; step++) {
        // Condition to print row header if in range of values
        if (rowCount >= startRow && rowCount <= endRow) {
            if (displayCursor == displayWidth) {
                printf("\n0x%02X", rowCount);
                displayCursor = 0;
                rowCount++;
            }
            if (step < beginning || step > ending) {
                printf(" %2s", "");
            }
        }
        if (step >= beginning && step <= ending) {
            printf(" %02X", registry[step]);
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
    // printf("\n");
}

void Memory::reset() {
    /*
    # The "reset" command causes all of the allocated
    # memory to be set to zero.
    #   Example: "memory reset"
    */
    for (int i = 0; i < capacity; i++) {
        registry[i] = 0;
    }
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
    int value;
    int ending = (starting + number_of_elements);
    char chunk[6];
    for (int i = 0; i < capacity; i++) {
        if (i >= starting && i < ending) {
            elements = Utilities::chunkInstruction(elements, chunk);
            value = std::stoi(chunk, 0, 16);
            registry[i] = value;
        }
    }
}

void Memory::set_memory(int position, int hexValue) {
    // Set value of position in memory banks based on index value
    registry[position] = hexValue;
}

int Memory::get_memory(int position) {
    // Return the value of index in bank
    try {
        int response = registry[position];
        return response;
    } catch (const std::out_of_range& exc) {
        throw exc.what();
    }
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
