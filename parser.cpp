/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

#include "parser.h"
Parser::Parser() {
    // Instantiate Devices
    _cpu = new Cpu();
    _imemory = new IMemory();
    _memory = new Memory();

    // Devices Options
    const int dev_num = 4;
    char* device_objects[dev_num] = {"clock", "cpu", "memory", "imemory"};

    // Load up device list, and options
    Utilities::loadOptions(dev_num, device_objects, deviceList);
}

void Parser::readInputFile(char* fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        printf("Error: Failed to open input file < %s >!\n", fileName);
        return;
    }

    // DEBUG: This line can be removed after testing
    // printf("FileName: %s\n", fileName);

    int device;
    char deviceName[7], operation[8];
    std::string instructions;

    while (!inputFile.eof()) {
        while (getline(inputFile, instructions)) {

            // Convert std::string to char* for ease of handling
            char* instructionSet = const_cast<char*>(instructions.c_str());
            // Set all characters to lowercase
            // Utilities::toLower(instructionSet, instructions.size());
            // Extract device name from instruction
            instructions = Utilities::chunkInstruction(instructions, deviceName);

            // DEBUG: This line can be removed after testing
            // printf("Device :: %s\n%s", deviceName, instructions.c_str());

            // Convert deviceName to switch statement
            device = deviceList[deviceName];

            switch(device) {
                case 0:
                    // Clock Execution
                    // DEBUG: This line can be removed after testing
                    // printf("Clock Execution Sent.\n");
                    _clock->parseInstructions(_cpu, _memory, instructions);
                    break;
                case 1:
                    // CPU Execution
                    // DEBUG: This line can be removed after testing
                    // printf("CPU Execution Sent.\n");
                    _cpu->parseInstructions(instructions);
                    break;
                case 2:
                    // Memory Execution
                    // DEBUG: This line can be removed after testing
                    // printf("Memory Execution Sent.\n");
                    _memory->parseInstructions(instructions);
                    break;
                case 3:
                    // Instruction Memory Execution
                    // DEBUG: This line can be removed after testing
                    // printf("iMemory Execution Sent.\n");
                    _imemory->parseInstructions(_cpu, _memory, instructions);
                    break;
                default:
                    // Catch-all condition incase command is invalid.
                    printf("Error: Invalid Device choice < %d:%s >.\n", device, deviceName);
            }

        }
    }
}

int main(int argc, char const *argv[]) {
    // Conditional to ensure filename was provided.
    if (argc < 2) {
        printf("Error: Filename\n\tUsage: ./cs3421_emul <filename>.\n");
        return 1;
    }

    // Parse commands from input file
    Parser p;
    p.readInputFile( const_cast<char *>(argv[1]));
    return 0;
}
