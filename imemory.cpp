/**************************************
# Author: Jesse Hassell
# Date: Oct, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/
#include "imemory.h"

IMemory::IMemory() {
    // create(0x0F);
    capacity = 0;
    int mem_num = 4;
    char* mem_operations[mem_num] = {"create", "dump", "reset", "set"};
    Utilities::loadOptions(mem_num, mem_operations, memOperations);
}

void IMemory::create(int inputSize) {
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

void IMemory::dump(int begin, int number_of_elements, int column_span) {
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
    int headSize = 2;
    int dataSize = 5;
    int displayWidth=column_span, rowCount=0;
    int ending = (begin + number_of_elements);
    printBankHeaders(column_span);
    int startRow = int(begin / column_span) + 1;
    int endRow = int(ending / column_span) + 1;
    // DEBUG: This line can be removed after testing
    // printf("IMemory::dump: Start [%d] -> End [%d]\n", startRow, endRow);

    for (int step = 0; step < capacity; step++) {
        if (step % column_span == 0) {
            rowCount++;
        }

        // Condition to print instruction memory if in requested range
        if (rowCount >= startRow && rowCount <= endRow) {
            if (step % column_span == 0) {
                printf("\n0x%*X", headSize, step);
            }
            if (step < begin || step >= ending) {
                printf(" %*s", dataSize, "");
            }
        }
        if (step >= begin && step < ending) {
            printf(" %*X", dataSize, registry[step]);
        }
    }
    printf("\n");
}
/*
void IMemory::loadWord(Cpu* _cpu, Memory* _memory, int instruction) {
    // Load Word Funciton
    int destinationRegister = ((instruction >> 14) | 240 ) & 7;
    int targetMemory = ((instruction >> 8 ) | 240 ) & 7;

    // DEBUG: This line can be removed after testing
    printf("IMemory::loadWord: Memory [%d] -> Register [%d]\n", targetMemory, destinationRegister);

    int targetValue = _memory->get_memory(targetMemory);
    _cpu->set_reg(_cpu->registrar[destinationRegister], targetValue);
}

void IMemory::storeWord(Cpu* _cpu, Memory* _memory, int instruction) {
    // Store word function
    int targetRegister = ((instruction >> 11) | 240 ) & 7;
    int destinationMemory = ((instruction >> 8 ) | 240 ) & 7;

    // DEBUG: This line can be removed after testing
    printf("IMemory::storeWord: Register [%d] -> Memory [%d]\n", targetRegister, destinationMemory);
    std::string reg = _cpu->registrar[targetRegister];

    int targetValue = _cpu->get_register(reg);
    _memory->set_memory(destinationMemory, targetValue);
}
*/

void IMemory::nextState() {
    // Advances Finite State Machine to the next state
    int period = sizeof(STATE) - 1;
    // DEBUG: This line can be removed after testing
    // printf("IMemory::nextState: [%d] -> [%d]\n", STATE, ((STATE+1) % period));
    STATE = (STATE + 1) % period;
}

void IMemory::parseInstructions(std::string instructionSet) {
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
            // dump 1 9
            char startPos[8], elementCount[8];
            instructionSet = Utilities::chunkInstruction(instructionSet, startPos);
            instructionSet = Utilities::chunkInstruction(instructionSet, elementCount);
            int memStart = std::stoi(startPos, 0, 16);
            int memCount = std::stoi(elementCount, 0, 16);
            dump(memStart, memCount, 8);
            }
            break;
        case 2:
            // reset
            reset();
            break;
        case 3: {
            // set file <filename>.txt
            char startPos[3], junk[4];
            instructionSet = Utilities::chunkInstruction(instructionSet, startPos);
            instructionSet = Utilities::chunkInstruction(instructionSet, junk);
            int starting = std::stoi(startPos, 0, 16);
            set(starting, instructionSet);
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
}

void IMemory::printBankHeaders(int count) {
    std::string bits[16] = {"0", "1", "2", "3", "4", "5",
    "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    printf("%4s", "Addr");
    for (int i = 0; i < count; i++) {
        printf(" %5s", bits[i].c_str());
    }
    // printf("\n");
}

void IMemory::reset() {
    /*
    # The "reset" command causes all of the allocated
    # memory to be set to zero.
    #   Example: "memory reset"
    */
    for (int i = 0; i < capacity; i++) {
        registry[i] = 0;
    }
}

void IMemory::set(int starting, std::string instructionSet) {
    /*
    # Instruction Memory
    # The instruction memory device (imemory) provides instruction storage for the CPU. Unlike data memory
    # which has a word size of 8 bits/1 byte, instruction memory has a word size of 20 bits. This 20 bits
    # matches the size of a CPU instruction. Each fetch would retrieve a word (20 bits), and is indexed in word-
    # size increments. For instance “instr_memory[0]” indexes the first CPU instruction, and identifies a 20 bit
    # quantity. The next instruction would be at “instr_memory[1]”, and again identifies a 20 bit quantity.
    # Conceptually, it is an array of 20 bit words. The actual implementation need not match that model, and
    # the student should consider an array of 32 bit words, and simply ignore the extra 12 bits.
    # Prior to use, it must be created with the “create” command, which specifies the size (in hex) of the
    # number of 20 bit words to create. At that point, memory is in an undefined condition. The “reset”
    # command is used to initialize all of memory to zeros. The contents of memory can be displayed via the
    # “dump” command, and assigned with the “set” command.
    #   Example: "imemory set 0x10 file filename.txt"
    */
    char fileName[20];
    instructionSet = Utilities::chunkInstruction(instructionSet, fileName);

    std::ifstream inputFile(fileName);
    if (!inputFile) {
        printf("Error: Failed to open input file < %s >!\n", fileName);
        return;
    }

    int idx = starting;
    std::string instructions;
    while (!inputFile.eof()) {
        while (getline(inputFile, instructions)) {

            // Convert std::string to char* for ease of handling
            char* instructionSet = const_cast<char*>(instructions.c_str());
            // Set all characters to lowercase
            // Utilities::toLower(instructionSet, instructions.size());
            int instruction = std::stoi(instructionSet, 0, 16);

            // DEBUG: This line can be removed after testing
            // printf("IMemory::set Idx: [%d] <- Value: [%X]\n", idx, instruction);
            set_memory(idx, instruction);

            idx++;
            // int whichType = (instruction >> 17) & 7;
            // if (whichType == 5) {
            //     // lw
            //     loadWord(_cpu, _memory, instruction);
            // } else if (whichType == 6) {
            //     // sw
            //     storeWord(_cpu, _memory, instruction);
            // } else {
            //     printf("Instruction Memory: Unimplmemented instruction type: 0x%3X\n", whichType);
            // }

        }
    }
}

void IMemory::set_memory(int position, int hexValue) {
    // Set value of position in memory banks based on index value
    registry[position] = hexValue;

    // DEBUG: This line can be removed after testing
    // printf("IMemory::set_memory Idx: [%d] <- Value: [%X]\n", position, registry[position]);
}

int IMemory::get_memory(int position) {
    // Return the value of index in bank
    try {
        int response = registry[position];
        return response;
    } catch (const std::out_of_range& exc) {
        throw exc.what();
    }
}
