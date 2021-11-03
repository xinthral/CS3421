/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: This simple CPU device has 8 one byte data
# registers labeled RA through RH. The CPU also has a 1 byte
# program counter (PC) register that holds the address in
# memory of the next CPU instruction to fetch. For this
# assignment, CPU "instructions" will simply be 1 byte of
# data. On each clock cycle, the CPU will shift the contents
# of each register to the next higher register, such that RH
# receives the content of RG, RG receives what is in RF, and
# so on, until finally, RB receives RA. The CPU will then
# fetch the byte from the Memory Device pointed to by the PC,
# place it into RA, and increment the PC by 1. While the CPU
# test the I/O & memory fetch capabilities of the code.
# doesn’t do anything useful, this behavior is a means to
#**************************************/
#include "cpu.h"

Cpu::Cpu(Memory* memory, IMemory* imemory, int debug)
    : _memory(*memory), _imemory(*imemory) {
    _memory = *memory;
    _imemory = *imemory;

    const int cpu_option_num = 3;
    const int cpu_states_count = 5;

    char* cpu_states[cpu_states_count] = {"IDLE", "FETCH", "DECODE", "MEM_REQ", "WAIT"};
    char* cpu_operations[cpu_option_num] = {"dump", "reset", "set"};

    Utilities::loadOptions(cpu_states_count, cpu_states, STATES);
    Utilities::loadOptions(cpu_option_num, cpu_operations, cpuOperations);

    _clock_enabled = true;
    _pc = 0;
    DEBUG = debug;                      // Set debug flag
    STATE = 0;
    isMemoryWorking = false;
    isCycleWorkPending = false;
    // current_instruction = -1;
    reset();
}

void Cpu::decodeInstruction() {
    // Take in and decode Instruction from Instruction Memory
    current_executable = (current_instruction >> 17) & 7;
    current_DDD = (current_instruction >> 14 ) & 7;
    current_SSS = (current_instruction >> 11 ) & 7;
    current_TTT = (current_instruction >> 8 ) & 7;
    current_III = (current_instruction & 255);
    current_UHF = (current_III >> 4) & 15;
    current_LHF = (current_III & 15);

    if (DEBUG > 1) {
    // DEBUG: This line can be removed after testing
    printf("Cpu::decodeInstruction: Decode {%X} <- {%X}\n", current_executable, current_instruction);
        if (DEBUG > 3) {
            printf("\nDDD: %X\nSSS: %X\nTTT: %X\nIII: %X\n", current_DDD, current_SSS, current_TTT, current_III);
        }
    }
}

void Cpu::doCycleWork() {
    // Perform Cycle Work

    // Pre-process if work is needed
    bool workCheck = (isCycleWorkPending || isMemoryWorking);

    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::doCycleWork: Are we waiting? [%s].\n", workCheck ? "true" : "false");
    }

    if ((FETCH == STATE) && (!workCheck)) {
        fetch_memory();         // initiate fetch cycle
        nextState();
    } else if ((DECODE == STATE) && (isCycleWorkPending)) {
        decodeInstruction();    // initiate dedcode cycle
        nextState();
        executeInstruction();   // Memory Request
        nextState();
    } else if (WAIT == STATE) {
        if ((!isMemoryWorking) && (!isCycleWorkPending)) {
            // End Wait State
            // current_instruction = -1;
            nextState();
            incrementPC();
        }
    }
}

void Cpu::dump() {
    /*
    # The "dump" command shows the value of all of the CPU
    # registers. A sample output would be as follows:
    # PC: 0xAA
    # RA: 0x23
    # RB: 0x14
    # RC: 0xFF
    # RD: 0x44
    # RE: 0xAA
    # RF: 0x00
    # RG: 0x09
    # RH: 0x18
    */
    printf("PC: 0x%02X\n", _pc);
    for (int step = 0; step < 8; step++) {
        printf("%s: 0x%02X\n", registrar[step].c_str(), _registers[step]);
    }
    printf("\n");
}

void Cpu::executeInstruction() {
    // Switch to case statement
    if (DEBUG > 2) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::executeInstruction: Case %d\n", current_executable);
    }
    switch (current_executable) {
        case ADD:
            instruction_add();
            break;
        case ADDI:
            instruction_addi();
            break;
        case MUL:
            instruction_mul();
            break;
        case INV:
            instruction_inv();
            break;
        case BRANCH:
            // instruction_branch();
            switch (current_DDD) {
                case BEQ:
                    instruction_beq();
                    break;
                case BNEQ:
                    instruction_bneq();
                    break;
                case BLT:
                    instruction_blt();
                    break;
            }
            break;
        case LW:
            instruction_lw();
            break;
        case SW:
            instruction_sw();
            break;
        case HALT:
            instruction_halt();
            break;
        default:
            // DEBUG: This line can be removed after testing
            printf("Cpu::executeInstruction: Unimplmemented instruction type: %d\n", current_executable);
            break;
    }
}

void Cpu::fetch_memory() {
    /* Fetch new value from imemory banks and place instruction
    #  into the CPU register slot 'RA'
    */
    int fetch_memory = _pc;
    try {
        previous_instruction = current_instruction;
        current_instruction = _imemory.get_memory(fetch_memory);
        if (current_instruction > 0) {
            // isMemoryWorking = true;         // Set Work Flag
            isCycleWorkPending = true;      // Set Work Flag

            if (DEBUG > 0) {
                // DEBUG: This line can be removed after testing
                printf("Cpu::fetch_memory: Fetched Instruction: {%05X} <- {%d}\n", current_instruction, fetch_memory);
            }
        } else { isMemoryWorking = false; }
    } catch (const std::exception& e) { printf("Cpu::fetch_memory: Error fetching\n\t%s\n", e.what()); }
}

int Cpu::find_register(std::string location){
    /* Insert value into registry */
    transform(location.begin(), location.end(), location.begin(), ::toupper);

    // Locate position of register
    auto itrLoc = find(registrar, registrar+8, location);
    int dist = std::distance(registrar, itrLoc);

    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::find_register: Located %s @ %d.\n", location.c_str(), dist);
    }
    return dist;
}

int Cpu::get_register(int register_number) {
    /* Takes in a register name and returns the current value stored */
    return _registers[register_number];
}

void Cpu::incrementPC() {
    /* Increment the Program Counter */
    _pc += 1;
    if (DEBUG > 0) {
        // DEBUG: This line can be removed after testing
        printf("\nCpu::incrementPC: Counter incremented [%X] -> [%X].\n\n", (_pc - 1), _pc);
    }
}

bool Cpu::isClockEnabled() {
    /* Returns true if clock is enabled */
    return _clock_enabled;
}

bool Cpu::isMoreCycleWorkNeeded() {
    /* Check if there more work pending in this clock cycle */
    return isCycleWorkPending;
}

void Cpu::instruction_add() {
    /* Adds the source & target register words, storing the result in the destination register. All values
    # should be treated as 8 bit two’s compliment numbers.
    */

    int inp1 = get_register(current_SSS);
    int inp2 = get_register(current_TTT);
    int summ = inp1 + inp2;

    if (DEBUG > 1) {
    // DEBUG: This line can be removed after testing
    printf("Cpu::instruction_add %X : %s <- %d \n", current_instruction, registrar[current_DDD].c_str(), summ);
        if (DEBUG > 3) {
            printf("\t: %d + %d = %d\n", inp1, inp2, summ);
        }
    }
    // Store result
    set_reg(registrar[current_DDD], summ);
    isCycleWorkPending = false;
}

void Cpu::instruction_addi() {
    /* Add the value in two registers and store in aforementioned register. */

    int inp1 = get_register(current_SSS);
    int inp2 = current_III;
    int summ = inp1 + inp2;

    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_addi %X : %s <- %d\n", current_instruction, registrar[current_DDD].c_str(), summ);
        if (DEBUG > 3) {
            printf("\t: %d + %d = %d\n", inp1, inp2, summ);
        }
    }
    // Store result
    set_reg(registrar[current_DDD], summ);
    isCycleWorkPending = false;
}

void Cpu::instruction_branch() {
    /* Manages the decoding and parsing of the instruction */
    // set_reg("RB", 6);
    isCycleWorkPending = false;

}

void Cpu::instruction_beq() {
    /* If the words in the source & target registers are equal, assign the PC
    # to the immediate-specified imemory address, otherwise increment the PC.
    # Note the use of the destination register field to distinguish from other
    # branch instructions.
    */
    if (DEBUG > 2) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_beq %X\n", current_instruction);
    }
    int inp1 = get_register(current_SSS);
    int inp2 = get_register(current_TTT);
    if (inp1 == inp2) {
        _pc = current_III;
    } else {
        incrementPC();
        current_instruction = previous_instruction;
    }
    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_beq [%d] == [%d] |  PC:{%d}\n", inp1, inp2, _pc);
    }
    isCycleWorkPending = false;
}

void Cpu::instruction_blt() {
    /* If the word in the source register is less than the word in the target
    # registers, assign the PC to the immediate-specified imemory address,
    # otherwise increment the PC. The numbers should be treated as two’s
    # complement numbers. Note the use of the destination register field to
    # distinguish from other branch instructions.
    */
    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_blt %X\n", current_instruction);
    }
    isCycleWorkPending = false;
}

void Cpu::instruction_bneq() {
    /* If the words in the source & target registers are not equal, assign the
    # PC to the immediate-specified imemory address, otherwise increment the PC.
    # Note the use of the destination register field to distinguish from other
    # branch instructions.
    */
    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_bneq %X\n", current_instruction);
    }
    isCycleWorkPending = false;
}

void Cpu::instruction_halt() {
    /* Halts execution of the processor after incrementing PC. After halting,
    # the CPU will ignore all future clock ticks, but will cooperate in
    # supporting all parser commands such as "cpu dump".
    */
    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_halt %X\n", current_instruction);
    }

    incrementPC();
    _clock_enabled = false;
    isCycleWorkPending = false;
}

void Cpu::instruction_inv() {
    /* Inverts all the bits in the source register word, storing the result in
    # the destination register.
    */
    int output = get_register(current_SSS);
    int sentinal = 8; //log2(output) + 1;
    for (int i = 0; i < sentinal; i++) {
        output = (output ^ (1 << i));
    }
    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_inv %X: %d -> %d\n", current_instruction, get_register(current_SSS), output);
    }

    set_reg(registrar[current_DDD], output);
    isCycleWorkPending = false;
}

void Cpu::instruction_lw() {
    /* Loads a word into the destination register, from data memory at the
    # address specified in the target register
    */
    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_lw: Loading Word into %s <- M[%d].\n", registrar[current_DDD].c_str(), get_register(current_TTT));
    }

    // Begin fetch
    _memory.startFetch(get_register(current_TTT), 1, &(_registers[current_DDD]), &isMemoryWorking);
    isMemoryWorking = true;
    isCycleWorkPending = false;
}

void Cpu::instruction_mul() {
    /* Takes the upper 4 bits and lower 4 bits of the source register,
    # multiplies those values together, and stores the result in the destination
    # register. Interprets its inputs as UNSIGNED. I.e., 1001 is interpreted as
    # decimal 9, not decimal -7. The fact that the multiplier is NOT a two's
    # complement multiplier can yield mathematically incorrect results.
    # For example, 1111 * 1111, or 15x15, would yield a result of 11100001,
    # which the CPU will interpret as -31. This is fine; it is the intended
    # behavior.
    */

    unsigned int sourceRegisterValue = get_register(current_SSS);
    unsigned int inp1 = instructionBitSelector(UHF, sourceRegisterValue);
    unsigned int inp2 = instructionBitSelector(LHF, sourceRegisterValue);
    unsigned int summ = inp1 * inp2;

    int result = (int) summ;

    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_mul %X : %s <- %d\n", current_instruction, registrar[current_DDD].c_str(), result);
        if (DEBUG > 3) {
            printf("\t: %d * %d = %d\n", inp1, inp2, result);
        }
    }

    // Store result
    set_reg(registrar[current_DDD], result);
    isCycleWorkPending = false;
}

void Cpu::instruction_sw() {
    /* Stores the source register word into data memory at the address
    # specified in the target register
    */

    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::instruction_sw: Storing Word from %s -> M[%d].\n", registrar[current_SSS].c_str(), get_register(current_TTT));
    }

    // Begin store
    _memory.startStore(get_register(current_SSS), 1, &(_registers[current_TTT]), &isMemoryWorking);
    isMemoryWorking = true;
    isCycleWorkPending = false;
}

int Cpu::instructionBitSelector(int option, int instruction) {

    int response = -1;
    switch (option) {
        case NNN:
            response = (instruction >> 17) & 7;
            break;
        case DDD:
            response = (instruction >> 14) & 7;
            break;
        case SSS:
            response = (instruction >> 11) & 7;
            break;
        case TTT:
            response = (instruction >> 8) & 7;
            break;
        case III:
            response = instruction & 255;
            break;
        case UHF:
            response = (instruction >> 4) & 15;
            break;
        case LHF:
            response = instruction & 15;
            break;
        default:
            break;
    }

    return response;
}

void Cpu::nextState() {
    // Advances Finite State Machine to the next state
    int period = STATES.size();
    int previousState = STATE;
    STATE = (STATE + 1) % period;               // Cycle States

    if (DEBUG > 1) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::nextState: [%d] -> [%d]\n", previousState, STATE);
    }
}

void Cpu::parseInstructions(std::string instructionSet) {
    // Parse incoming instructions fro the Cpu Device
    if (DEBUG > 2) {
        // DEBUG: This line can be removed after testing
        printf("Cpu Instruction: %s\n", instructionSet.c_str());
    }

    char operation[8];
    instructionSet = Utilities::chunkInstruction(instructionSet, operation);
    int op = cpuOperations[operation];

    switch (op) {
        case 0:
            // dump
            dump();
            break;
        case 1:
            // reset
            reset();
            break;
        case 2: {
                // set reg
                char junk[4], element[8];

                instructionSet = Utilities::chunkInstruction(instructionSet, junk);
                instructionSet = Utilities::chunkInstruction(instructionSet, element);

                int bitValue = std::stoi(instructionSet, 0, 16);
                std::string location = element;

                set_reg(location, bitValue);
            }
            break;
        default:
            printf("Error: Parser::parseClock recieved a bad operation < %s >.\n", operation);
    }
}

void Cpu::reset() {
    // Reset Memory Registers
    for (int step = 0; step < 8; step++) {
        _registers[step] = 0x00;
    }
}

void Cpu::set_reg(std::string location, int hbyte) {
    // Set register to specified integer;
    if ("PC" != location) {
        int register_location = find_register(location);    // Get index value
        _registers[register_location] = hbyte;              // Set the register
    } else {
        _pc = hbyte;
    }
    if (DEBUG > 2) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::set_reg: Setting %s to %X.\n", location.c_str(), hbyte);
    }
}

void Cpu::startTick() {
    /* Called by clock to tell device a new tick has started. Used by devices to
    # do minimal housekeeping, and transition state. Very little actual work
    # should be done in this function, and is instead done in doCycleWork
    # described below.
    */
    if (DEBUG > 3) {
        // DEBUG: This line can be removed after testing
        printf("Cpu::startTick: Current State %d : %s.\n", STATE, isMemoryWorking ? "true" : "false");
    }

    if (STATE == IDLE) {
        nextState();
    } else if (STATE == WAIT){
        // Wait state, chillin
    } else {
        // DEBUG: This line can be removed after testing
        printf("Cpu::startTick: Invalid start state: %d.\n", STATE);
        STATE = IDLE;
    }
}
