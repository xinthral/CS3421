/**************************************
# Author: Jesse Hassell
# Date: Nov, 2021
# The cache device sits between the CPU and Data Memory, and can improve memory
# performance. The cache contains 8 bytes of high speed memory, and contains
# logic to handle data passing through it from read/lw instructions and write/sw
# instructions.
**************************************/

#include "cache.h"

Cache::Cache(Memory* memory, int debug)
    : _memory(*memory), DEBUG(debug) {
    // Constructor Method
    _CLO = -1;
    _cache_enabled = false;

    const int csh_option_num = 4;
    char* csh_operations[csh_option_num] = {"dump", "on", "off", "reset"};
    Utilities::loadOptions(csh_option_num, csh_operations, cshOperations);
}

int Cache::blockId(int instruction) {
    /* Identify the CLO for the block */
    int response = (instruction >> 3) & 3;
    return response;
}

void Cache::cacheData() {
    int element = *answerPtr;
    // printf("Cache::cacheData: %d\n", element);
    // NEEDS WORK
}

void Cache::cacheOn() {
    /* The "on" command enables the cache, causing it to keep copies of data
    # transferred between the CPU and Data Memory. The coder may assume cache
    # will only be enabled when the CPU is idle (about to start a new
    # instruction). */
    _cache_enabled = true;
}

void Cache::cacheOff() {
    /* The "off" command disables the cache, causing the system to act as if no
    # cache were present. Any data written to the cache should be written to
    # memory (cache flush). The coder may assume cache will only be disabled
    # when the CPU is idle (about to start a new instruction). */
    _cache_enabled = false;
    reset();
}

void Cache::dump() {
    /* The dump command will show the contents of cache, and the states of those
    # contents. The first line shows the 5 bit CLO as two hex digits. The second
    # line shows the contents of the 8 cache bytes in hex. The third line shows
    # the flags indicating the state of each byte, with "I" meaning invalid, "V"
    # meaning valid, and "W" meaning it has been written. Two examples follow:
    #       CLO         : 0x04
    #       cache data  : 0x00 0x18 0x22 0xFF 0xEE 0x27 0x1E 0xAE
    #       Flags       :   I    W    I    I    I    W    I    I
    #
    #       CLO         : 0x01
    #       cache data  : 0x00 0x18 0x22 0xFF 0xEE 0x27 0x1E 0xAE
    #       Flags       :   V    V    W    W    V    V    V    V
    */
    int cacheSize = 8;
    printf("%13s: 0x%02X\n", "CLO", _CLO);
    printf("%13s:", "cache data");
    for (int i = 0; i < cacheSize; i++) {
        printf(" 0x%02X", _registry[i]);
    }
    printf("\n");
    printf("%13s:", "Flags");
    for (int j = 0; j < cacheSize; j++) {
        printf("   %c ", _flags[j]);
    }
    printf("\n");
    printf("\n");
}

bool Cache::isBlockValid(int inputValue) {
    /* Check if the input value is in the current cached block */
    return blockId(inputValue) == _CLO;
}

bool Cache::isCacheEnabled() {
    /* Return true if the cache is enabled */
    return _cache_enabled;
}

void Cache::invalidateCache() {
    for (int i = 0; i < cacheSize; i++) {
        _flags[i] = 'I';
    }
}

void Cache::memoryFetch() {
    if (DEBUG > 0) {
        // DEBUG: This line can be removed after testing
        printf("Cache::memoryFetch: Fetching from M[%d]\n", startPos);
    }
    _CLO = blockId(startPos);
    _memory.startFetch(startPos, 8, &_registry[0], workResponse);
}

void Cache::memoryStore() {
    if (DEBUG > 0) {
        // DEBUG: This line can be removed after testing
        printf("Cache::memoryStore: Storing to M[%d]\n", startPos);
    }
    _CLO = blockId(startPos);
}

void Cache::parseInstructions(std::string instructionSet) {
    if (DEBUG > 3) {
        // DEBUG: This line can be removed after testing
        printf("Cache::parseInstructions: Instruction Set: %s\n", instructionSet.c_str());
    }

    char operation[8];
    instructionSet = Utilities::chunkInstruction(instructionSet, operation);
    int op = cshOperations[operation];

    switch (op) {
        case 0:
            // dump
            dump();
            break;
        case 1:
            // on
            cacheOn();
            break;
        case 2:
            // on
            cacheOff();
            break;
        case 3:
            // reset
            reset();
            break;
        default:
            printf("Error: Cache::parseInstructions recieved a bad operation < %s >.\n", operation);
    }
}

void Cache::reset() {
    /* The "reset" command resets the cache to disabled, setting CLO to zero,
    # and data to be invalid.
    */
    int cacheSize = 8;
    _CLO = -1;
    invalidateCache();
    if (DEBUG > 2) {
        // DEBUG: This line can be removed after testing
        printf("Cache::reset: Cache has been invalidated. %s\n", _flags);
    }
}

void Cache::startFetch(int start, int number_of_elements, int* dataPtr, bool* isWorkPending) {
    // This API is called by the cpu to initiate a fetch (read) from cache

    if (!_cache_enabled) {
        _memory.startFetch(start, number_of_elements, dataPtr, isWorkPending);
    } else {
        startPos = start;
        fetchCount = number_of_elements;
        answerPtr = dataPtr;
        workResponse = isWorkPending;
        if (isBlockValid(start)) {
            if (DEBUG > 0) {
                // DEBUG: This line can be removed after testing
                printf("Cache::startFetch: Fetching from C[%d]\n", startPos);
            }
            *answerPtr = _registry[startPos];
            *workResponse = false;
        } else {
            if (DEBUG > 0) {
                // DEBUG: This line can be removed after testing
                printf("Cache::startFetch: Fetching from M[%d]\n", startPos);
            }
            memoryFetch();
        }
    }
}

void Cache::startStore(int start, int number_of_elements, int* dataPtr, bool* isWorkPending) {
    // This API is called by memory clients to initiate store (write) to cache
    if (!_cache_enabled) {
        _memory.startStore(start, number_of_elements, dataPtr, isWorkPending);
    } else {
        startPos = start;
        fetchCount = number_of_elements;
        answerPtr = dataPtr;
        workResponse = isWorkPending;
        if (isBlockValid(start)) {
            if (DEBUG > 0) {
                // DEBUG: This line can be removed after testing
                printf("Cache::startStore: Storing %d @ C[%d]\n", *answerPtr, startPos);
            }
            cacheData();
            *workResponse = false;
            // _registry[startPos] = *answerPtr;
        } else {
            if (DEBUG > 0) {
                // DEBUG: This line can be removed after testing
                printf("Cache::startStore: Storing %d @ M[%d]\n", *answerPtr, startPos);
            }
            memoryStore();
        }
    }
}
