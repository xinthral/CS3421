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
    int mem_num = 4;
    char* mem_operations[mem_num] = {"create", "dump", "reset", "set"};
    Utilities::loadOptions(mem_num, mem_operations, memOperations);
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

void Memory::dump(int begin, int number_of_elements, int column_span) {
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
    int displayCursor=column_span, displayWidth=column_span, rowCount=0;
    int beginning = (begin);
    int ending = (begin + number_of_elements);
    printBankHeaders();
    int startRow = (begin + 1) / column_span;
    int endRow = ending / column_span;

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
        if (step >= beginning && step < ending) {
            printf(" %02X", registry[step]);
        }
        displayCursor++;
    }
    printf("\n");
}

void Memory::parseInstructions(std::string instructionSet) {
    // DEBUG: This line can be removed after testing
    // printf("Memory Instruction: %s\n", instructionSet.c_str());

    char operation[8];
    instructionSet = Utilities::chunkInstruction(instructionSet, operation);
    int op = memOperations[operation];
    switch (op) {
        case 0: {
            // create 0x100
            char memSizeStr[6];
            instructionSet = Utilities::chunkInstruction(instructionSet, memSizeStr);
            int memSize = std::stoi(memSizeStr, 0, 16);
            create(memSize);
            }
            break;
        case 1: {
                // dump 0 8
                char startPos[3], elementCount[3];
                instructionSet = Utilities::chunkInstruction(instructionSet, startPos);
                instructionSet = Utilities::chunkInstruction(instructionSet, elementCount);
                int memStart = std::stoi(startPos, 0, 16);
                int memCount = std::stoi(elementCount, 0, 16);
                dump(memStart, memCount, 16);
            }
            break;
        case 2:
            // reset
            reset();
            break;
        case 3: {
            // set 0x00 0x03 0x03 0x02 0x01
            char startPos[3], elementCount[3];
            instructionSet = Utilities::chunkInstruction(instructionSet, startPos);
            instructionSet = Utilities::chunkInstruction(instructionSet, elementCount);

            int starting = std::stoi(startPos, 0, 16);
            int number_of_elements = std::stoi(elementCount, 0, 16);

            set(starting, number_of_elements, instructionSet);
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
}

void Memory::printBankHeaders() {
    std::string bits[16] = {"00", "01", "02", "03", "04", "05",
    "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F"};
    printf("%4s", "Addr");
    for (auto bit : bits){
        printf(" %2s", bit.c_str());
    }
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
    for (int i = starting; i < ending; i++) {
        elements = Utilities::chunkInstruction(elements, chunk);
        value = std::stoi(chunk, 0, 16);
        // DEBUG: This line can be removed after testing
        printf("Memory::set: Setting [0x%2X] -> [%d]\n", value, i);
        set_memory(i, value);
    }
    // DEBUG: This line can be removed after testing
    printf("Memory::set: Setting [0x%2X] -> [%d]\n", value, i);
    set_memory(i, value);
}

void Memory::set_memory(int position, int hexValue) {
    // Set value of position in memory banks based on index value

    // DEBUG: This line can be removed after testing
    printf("Memory::set_memory: Setting Value [0x%2X] -> Location [%d]\n", hexValue, position);

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
