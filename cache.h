#ifndef CACHE_H
#define CACHE_H

#include <map>                  // std::map
#include "memory.h"             // Internal Memory Object
#include <stdio.h>              // printf

// Forward Declarations
class Memory;

class Cache {
protected:
    static const int cacheSize = 8;             // Size of cache

private:
    Memory& _memory;
    int DEBUG{};
    bool _cache_enabled;                        // True if cache is enabled
    int _CLO;                                   // Block Identifier
    char _flags[cacheSize] = {'I'};             // Registry Flags
    int _registry[cacheSize] = { 0 };           // Register Bank
    std::map<std::string,int> cshOperations;    // Cache Operations
    bool* workResponse;                         // startFetch response pointer

public:
    Cache(Memory*, int);
    int blockId(int);                           // Return the block identifier
    void cacheOn();                             // Turn on caching
    void cacheOff();                            // Turn off caching
    void dump();                                // Display the cache
    bool isCacheEnabled();                      // True if cache is enabled
    void memoryFetch();                         // Fetch the memory
    void memoryStore();                         // Store the memory
    void reset();                               // Reset the cache
    void startFetch(int,int,int*, bool*);
    void startStore(int,int,int*, bool*);
    void parseInstructions(std::string);
};

#endif
