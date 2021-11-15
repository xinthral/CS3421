/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

#include "parser.h"

Parser::Parser(int debug) {
    // Set debug flag
    DEBUG = debug;

    // Instantiate Devices
    _memory = new Memory(DEBUG);
    _imemory = new IMemory(DEBUG);
    _cache = new Cache(_memory, DEBUG);
    _cpu = new Cpu(_memory, _imemory, DEBUG);
    _clock = _clock->getClock(_cpu, _memory, _imemory, DEBUG);

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

    if (DEBUG > 3) {
        // DEBUG: This line can be removed after testing
        printf("FileName: %s\n", fileName);
    }

    int device;
    char deviceName[7], operation[8];
    std::string instructions;

    while (!inputFile.eof()) {
        while (getline(inputFile, instructions)) {

            // Convert std::string to char* for ease of handling
            char* instructionSet = const_cast<char*>(instructions.c_str());
            // Extract device name from instruction
            instructions = Utilities::chunkInstruction(instructions, deviceName);

            if (DEBUG > 3) {
                // DEBUG: This line can be removed after testing
                printf("Device :: %s\n%s", deviceName, instructions.c_str());
            }

            // Convert deviceName to switch statement
            device = deviceList[deviceName];

            switch(device) {
                case 0:
                    // Clock Execution
                    _clock->parseInstructions(instructions);
                    break;
                case 1:
                    // CPU Execution
                    _cpu->parseInstructions(instructions);
                    break;
                case 2:
                    // Memory Execution
                    _memory->parseInstructions(instructions);
                    break;
                case 3:
                    // Instruction Memory Execution
                    _imemory->parseInstructions(instructions);
                    break;
                default:
                    // Catch-all condition incase command is invalid.
                    printf("Error: Invalid Device choice < %d:%s >.\n", device, deviceName);
            }

        }
    }
}

int main(int argc, char const *argv[]) {

    int debug_value = 0;

    // Conditional to ensure filename was provided.
    if (argc < 2) {
        printf("Error: Filename\n\tUsage: ./cs3421_emul <filename> <int:optional>.\n");
        return 1;
    } else if (argc > 2) {
        debug_value = std::atoi(argv[2]);
    }

    // Parse commands from input file
    Parser p(debug_value);
    p.readInputFile( const_cast<char *>(argv[1]));
    return 0;
}
