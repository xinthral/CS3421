/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

#include "parser.h"

Parser::Parser() {
    // Devices Options
    int clk_num = 3, cpu_num = 3, mem_num = 4;
    char* clk_operations[clk_num] = {"dump", "reset", "tick"};
    char* cpu_operations[cpu_num] = {"dump", "reset", "set_reg"};
    char* mem_operations[mem_num] = {"create", "dump", "reset", "set"};

    // Load up device list, and options
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

    printf("%s\n", instructionSet.c_str());
}

void Parser::parseCpu(char* operation, std::string instructionSet) {
    printf("%s\n", instructionSet.c_str());
}

void Parser::parseMemory(char* operation, std::string instructionSet) {
    printf("%s\n", instructionSet.c_str());
}

void Parser::parseInput(char* fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        printf("Error: Failed to open input file < %s >!\n", fileName);
        return;
    }

    char deviceName[7], operation[8];
    std::string instructions;

    while (!inputFile.eof()) {
        for (instructions; std::getline(inputFile, instructions);) {

            char* instructionSet = const_cast<char*>(instructions.c_str());
            Parser::utilz.toLower(instructionSet, instructions.size());

            // Strip out the first two words in the instruction set
            instructions = Parser::utilz.chunkInstruction(instructions, deviceName);
            instructions = Parser::utilz.chunkInstruction(instructions, operation);

            // Convert deviceName to switch statement
            int device = deviceList[deviceName];

            switch(device){
                    case 0:
                        // Clock Execution
                        printf("Clock Execution Sent.\n");
                        parseClock(operation, instructions);
                        break;

                    case 1:
                        // CPU Execution
                        printf("CPU Execution Sent.\n");
                        parseCpu(operation, instructions);
                        break;

                    case 2:
                        // Memory Execution
                        printf("Memory Execution Sent.\n");
                        parseMemory(operation, instructions);
                        break;
                    default:
                        // Catch-all condition incase command is invalid.
                        printf("Nothing to see here!.\n");
                }
        }
    }
}

// std::string chunkInstruction(std::string instructions, char* element) {
//     // Peel off first word and return them both
//     sscanf(instructions.c_str(), "%s", element);
//     return instructions.substr(instructions.find_first_of(" \t") + 1);
// }
//
// int wordCount(char* input) {
//     /*
//     # Count the number of words in a string
//     # This function was derived from the following URL:
//     # https://www.tutorialspoint.com/count-words-in-a-given-string-in-cplusplus
//     */
//     int number_of_words = 0, sentinal = 0;
//     while (*input) {
//         if (*input == ' ' || *input == '\n' || *input == '\t') {
//             sentinal = 0;
//         } else if (sentinal == 0) {
//             sentinal = 1;
//             number_of_words++;
//         }
//         ++input;
//     }
//     return number_of_words;
// }
//
// void toLower(char* input, int inputSize) {
//     // Branchless method for converting a string to lowercase
//     for (int i = 0; i < inputSize; i++) {
//         input[i] += 32 * (input[i] >= 'A' && input[i] <= 'Z');
//     }
// }

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
