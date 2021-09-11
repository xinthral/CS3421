/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

#include "parser.h"

Parser::Parser() {

    clock   = getClock();
    cpu     = getCpu();
    memory  = getMemory();
    utilz   = getUtilities();

    // Devices Options
    int dev_num = 3, clk_num = 3, cpu_num = 3, mem_num = 4;
    char* device_objects[dev_num] = {"clock", "cpu", "memory"};
    char* clk_operations[clk_num] = {"dump", "reset", "tick"};
    char* cpu_operations[cpu_num] = {"dump", "reset", "set_reg"};
    char* mem_operations[mem_num] = {"create", "dump", "reset", "set"};

    // Load up device list, and options
    loadOptions(dev_num, device_objects, deviceList);
    loadOptions(clk_num, clk_operations, clkOperations);
    loadOptions(cpu_num, cpu_operations, cpuOperations);
    loadOptions(mem_num, mem_operations, memOperations);
}

void Parser::loadOptions(int inputSize, char* options[], std::map<std::string, int> &kvpairs) {
    // Load options into object mappings for quick lookups
    for (int i = 0; i < inputSize; i++) {
        kvpairs.insert(std::pair<std::string, int>(options[i], i));
    }
}

void Parser::parseClock(char* operation, std::string instructionSet) {
    int op = clkOperations[operation];

    switch (op) {
        case 0:
            // dump
            clock.dump();
            break;
        case 1:
            // reset
            clock.reset();
            break;
        case 2:
            // tick
            clock.tick(0x0002);
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
    // DEBUG: This line can be removed after testing
    // printf("%s\n", instructionSet.c_str());
}

void Parser::parseCpu(char* operation, std::string instructionSet) {
    int op = cpuOperations[operation];

    switch (op) {
        case 0:
            // dump
            cpu.dump();
            break;
        case 1:
            // reset
            cpu.reset();
            break;
        case 2: {
            // set reg
            std::string values = "0x08 0x08 0x07 0x06 0x05 0x04 0x03 0x02 0X01";
            cpu.set_reg(values, 0x0002);
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
    // DEBUG: This line can be removed after testing
    // printf("%s\n", instructionSet.c_str());
}

void Parser::parseMemory(char* operation, std::string instructionSet) {
    int op = memOperations[operation];

    switch (op) {
        case 0: {
            // create
            char memSizeStr[6];
            instructionSet = utilz.chunkInstruction(instructionSet, memSizeStr);
            uint16_t memSize = (uint16_t)atoi(memSizeStr);
            memory.create(memSize);
            }
            break;
        case 1:
            // dump
            memory.dump(0x00, 0x08);
            break;
        case 2:
            // reset
            memory.reset();
            break;
        case 3: {
            // set
            std::string values = "0x08 0x07 0x06 0x05 0x04 0x03 0x02 0X01";
            memory.set(0x00, 0x08, values);
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
    // DEBUG: This line can be removed after testing
    printf("%s\n", instructionSet.c_str());
}

void Parser::parseInput(char* fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        printf("Error: Failed to open input file < %s >!\n", fileName);
        return;
    }

    int device;
    char deviceName[7], operation[8];
    std::string instructions;

    while (!inputFile.eof()) {
        while (getline(inputFile, instructions)) {

            char* instructionSet = const_cast<char*>(instructions.c_str());
            utilz.toLower(instructionSet, instructions.size());

            // Strip out the first two words in the instruction set
            instructions = utilz.chunkInstruction(instructions, deviceName);
            instructions = utilz.chunkInstruction(instructions, operation);

            // Convert deviceName to switch statement
            device = deviceList[deviceName];
            switch(device) {
                    case 0:
                        // Clock Execution
                        // DEBUG: This line can be removed after testing
                        // printf("Clock Execution Sent.\n");
                        parseClock(operation, instructions);
                        break;

                    case 1:
                        // CPU Execution
                        // DEBUG: This line can be removed after testing
                        printf("CPU Execution Sent.\n");
                        parseCpu(operation, instructions);
                        break;

                    case 2:
                        // Memory Execution
                        // DEBUG: This line can be removed after testing
                        printf("Memory Execution Sent.\n");
                        parseMemory(operation, instructions);
                        break;
                    default:
                        // Catch-all condition incase command is invalid.
                        printf("Error: Invalid Device choice < %d:%s >.\n", device, deviceName);
                }
        }
    }
}

int main(int argc, const char *argv[]) {
    printf("Main Parser!!\n");
    // Conditional to ensure filename was provided.
    if (argc < 2) {
        printf("Error: Filename\n\tUsage: ./cs3421_emul <filename>.\n");
        return 1;
    }
    Parser p;
    p.parseInput( const_cast<char *>(argv[1]) );
    // p.memory.create(0x0100);
    // int begin = (int)atol(argv[2]);
    // int items = (int)atol(argv[3]);
    // p.parseMemory(argv[1], begin, items);
    return 0;
}
