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
    int DEBUG{};                                // Debug output control
    bool _cache_enabled;                        // True if cache is enabled
    int _CLO;                                   // Block Identifier
    char _flags[cacheSize] = {'I'};             // Registry Flags
    int _registry[cacheSize] = { 0 };           // Register Bank
    int* answerPtr;                             // startFetch reponse pointer
    std::map<std::string,int> cshOperations;    // Cache Operations
    int fetchCount{};                           // startFetch number of elements
    int startPos{};                             // startFetch starting position
    bool* workResponse;                         // startFetch response pointer

public:
    Cache(Memory*, int);
    int blockId(int);                           // Return the block identifier
    void cacheData();
    void cacheOn();                             // Turn on caching
    void cacheOff();                            // Turn off caching
    void dump();                                // Display the cache
    bool isBlockValid(int);                     // Return true if cached
    bool isCacheEnabled();                      // True if cache is enabled
    void invalidateCache();
    void memoryFetch();                         // Fetch the memory
    void memoryStore();                         // Store the memory
    void parseInstructions(std::string);
    void reset();                               // Reset the cache
    void startFetch(int,int,int*, bool*);       // Search the Cache
    void startStore(int,int,int*, bool*);       // Write to Cache
};

#endif
