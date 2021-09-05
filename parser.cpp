/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

#include "parser.h"

Parser::Parser() {
    // Load up device list
    deviceList.insert(std::pair<std::string, int>("clock", 0));
    deviceList.insert(std::pair<std::string, int>("cpu", 1));
    deviceList.insert(std::pair<std::string, int>("memory", 2));
    deviceList.insert(std::pair<std::string, int>("parser", 3));
}

void Parser::parseClock() {
}

void Parser::parseCpu() {
}

void Parser::parseMemory(std::string instructions) {
    // std::string test = "dump";
    // if (instructions == test) {
    //     memory.dump(begin, items);
    // }
}

void Parser::parseInput(std::string fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        printf("Error: Failed to open input file <%s>", fileName.c_str());
        return;
    }
    char deviceName[7];
    std::string operation, instructions;
    while (!inputFile.eof()) {
        for (operation; std::getline(inputFile, operation);) {
            printf("%s\n", operation.c_str());
            sscanf(operation.c_str(), "%s %*s", deviceName, instructions);

            // Convert deviceName to switch statement
            int device = deviceList[deviceName];

            switch(device){
                    case 0:
                        // Clock Execution
                        printf("Clock Execution Sent.\n");
                        break;

                    case 1:
                        // CPU Execution
                        printf("CPU Execution Sent.\n");
                        break;

                    case 2:
                        // Memory Execution
                        printf("Memory Execution Sent.\n");
                        parseMemory(instructions);
                        break;
                    default:
                        // Catch-all condition incase command is invalid.
                        printf("Nothing to see here!.\n");
                }
        }
    }
}

int main(int argc, const char *argv[]) {
    printf("Main Parser!!\n");
    if (argc < 2) {
        printf("Error: Missing Filename\n\tUsage: ./cs3421_emul <filename>.\n");
        return 1;
    }
    // Parser p;
    // printf("Filename: %s\n", argv[1]);
    // p.parseInput(argv[1]);
    // p.memory.create(0x0100);
    // int begin = (int)atol(argv[2]);
    // int items = (int)atol(argv[3]);
    // p.parseMemory(argv[1], begin, items);
    return 0;
}
