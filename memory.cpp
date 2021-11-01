/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/
#include "memory.h"

Memory::Memory() {
    // create(0x0F);
    const int mem_states_count = 3;
    char* mem_states[mem_states_count] = {"IDLE", "WAIT", "EXEC"};
    Utilities::loadOptions(mem_states_count, mem_states, STATES);

    const int mem_operation_count = 4;
    char* mem_operations[mem_operation_count] = {"create", "dump", "reset", "set"};
    Utilities::loadOptions(mem_operation_count, mem_operations, memOperations);

    STATE = 0;                  // FSM
    capacity = 0;               // Data Memory Size
    fetchCount = 0;             // Number of elements
    isWorking = false;          // FSM Trigger
    isCycleWorkPending = false; // Cycle Work Sentinal
    latencyFactor = 5;          // Device Processing Time
    startPos = 0;               // Memory Cursor
    waitDelay = 0;              // Current Cycle in Delay (step)
}

void Memory::create(int inputSize) {
    /* The "create" command accepts a single integer parameter
    # which indicates the size of the memory in bytes.
    #   Example: "memory create 0x10000".
    */
    registry = new int[inputSize];
    capacity = inputSize;
}

void Memory::doCycleWork() {
    // Completed WAIT state, and advanced into the MOVE_DATA state

    if ((EXEC == STATE) && (0 == waitDelay)) {
        // memcpy(answerPtr, registry + startPos, fetchCount);
        // printf("Memory::doCycleWork: Current Operation: %d\n", current_operation);
        if (5 == current_operation) {
            // DEBUG: This line can be removed after testing
            printf("Memory::doCycleWork: Loading R[%d] with %d.\n", startPos, get_memory(startPos));
            // copy data back to caller
            *answerPtr = get_memory(startPos);
        }
        if (6 == current_operation) {
            // DEBUG: This line can be removed after testing
            printf("Memory::doCycleWork: Storing %X -> M[%d].\n", startPos, *answerPtr);
            // copy data back to caller
            set_memory(*answerPtr, startPos);
        }
        // Tell caller memory operation is complete
        answerPtr = nullptr;
        current_operation = 0;
        fetchCount = 0;
        startPos = 0;
        *workResponse = false;
        isWorking = false;
        nextState();
    }
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
    int headSize = 2;
    int dataSize = 2;
    int displayWidth=column_span, rowCount=0;
    int ending = (begin + number_of_elements);
    printBankHeaders(column_span);
    int startRow = int(begin / column_span) + 1;
    int endRow = int(ending / column_span) + 1;
    // DEBUG: This line can be removed after testing
    printf("Memory::dump: Start [%d] -> End [%d]\n", startRow, endRow);

    for (int step = 0; step < capacity; step++) {
        if (step % column_span == 0) {
            rowCount++;
        }

        // Condition to print instruction memory if in requested range
        if (rowCount >= startRow && rowCount <= endRow) {
            if (step % column_span == 0) {
                printf("\n0x%0*X", headSize, step);
            }
            if (step < begin || step >= ending) {
                printf(" %*s", dataSize, "");
            }
        }
        if (step >= begin && step < ending) {
            printf(" %0*X", dataSize, registry[step]);
        }
    }
    printf("\n");
    printf("\n");
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

bool Memory::isMoreCycleWorkNeeded() {
    // Check if there more work pending in this clock cycle
    // DEBUG: This line can be removed after testing
    printf("Memory::isMoreCycleWorkNeeded: isCycleWorkPending %s\n", isCycleWorkPending ? "true" : "false");
    return isCycleWorkPending;
}

void Memory::nextState() {
    // Advances Finite State Machine to the next state
    int period = STATES.size();
    int previousState = STATE;

    STATE = (STATE + 1) % period;               // Cycle States

    // DEBUG: This line can be removed after testing
    printf("Memory::nextState: [%d] -> [%d]\n", previousState, STATE);

}

void Memory::parseInstructions(std::string instructionSet) {
    // DEBUG: This line can be removed after testing
    printf("Memory Instruction: %s\n", instructionSet.c_str());
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
            char startPos[6], elementCount[6];
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
            char startPos[6], elementCount[6];
            instructionSet = Utilities::chunkInstruction(instructionSet, startPos);
            instructionSet = Utilities::chunkInstruction(instructionSet, elementCount);

            int starting = std::stoi(startPos, 0, 16);
            int number_of_elements = std::stoi(elementCount, 0, 16);

            // DEBUG: This line can be removed after testing
            printf("Memory::parseInstructions: Starting [0x%2X] -> Number [0x%2X]\nInstructions: [%s]\n", starting, number_of_elements, instructionSet.c_str());

            set(starting, number_of_elements, instructionSet);
            }
            break;
        default:
            printf("Error: Memory::parseInstructions recieved a bad operation < %s >.\n", operation);
    }
}

void Memory::printBankHeaders(int count) {
    std::string bits[16] = {"00", "01", "02", "03", "04", "05",
    "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F"};
    printf("%4s", "Addr");
    for (int i = 0; i < count; i++) {
        printf(" %2s", bits[i].c_str());
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
        printf("Memory::set: Position [%d] <- [0x%2X]\n", i, value);
        set_memory(i, value);
    }
}

void Memory::set_memory(int position, int hexValue) {
    // DEBUG: This line can be removed after testing
    printf("Memory::set_memory: Position [%d] <- Value [0x%X]\n", position, hexValue);

    // Set value of position in memory banks based on index value
    registry[position] = hexValue;
}

void Memory::startFetch(int start, int number_of_elements, int* dataPtr, bool* isWorkPending) {
    // This API is called by memory clients to initiate a fetch (read) from memory
    nextState();
    current_operation = 5;
    isWorking = true;
    startPos = start;
    fetchCount = number_of_elements;
    answerPtr = dataPtr;
    workResponse = isWorkPending;
    // DEBUG: This line can be removed after testing
    printf("Memory::startFetch: Fetching from M[%d]\n", startPos);
}

void Memory::startStore(int start, int number_of_elements, int* dataPtr, bool* isWorkPending) {
    // This API is called by memory clients to initiate store (write) to memory
    nextState();
    current_operation = 6;
    isWorking = true;
    startPos = start;
    fetchCount = number_of_elements;
    answerPtr = dataPtr;
    workResponse = isWorkPending;
    // DEBUG: This line can be removed after testing
    printf("Memory::startStore: Storing %d @ M[%d]\n", *answerPtr, startPos);
}

void Memory::startTick() {
    /* Called by clock to tell device a new tick has started. Used by devices to
    # do minimal housekeeping, and transition state. Very little actual work
    # should be done in this function, and is instead done in doCycleWork
    # described below.
    */
    // DEBUG: This line can be removed after testing
    printf("Memory::startTick: Current State %d : %s.\n", STATE, isWorking ? "true" : "false");

    if (WAIT == STATE) {
        if (waitDelay < (latencyFactor - 1)) {
            waitDelay += 1;
            // DEBUG: This line can be removed after testing
            printf("Memory::startTick: Waiting: %d\n", waitDelay);
        } else {
            // isWorking = false;
            waitDelay = 0;
            nextState();
        }
    }
}
