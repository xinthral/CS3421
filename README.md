# Computer Organization
> CS3421 { Aug - Dec 2021 } The purpose of this was to emulate a system
utilizing concepts of System Clocks, CPU Registries, and Memory Banks

## Cache
* 

## Clock
* doWork
* dump
* parseInstructions
* reset
* tick

## CPU
* decodeInstruction
* doCycleWork
* dump
* executeInstruction
* fetch_memory
* find_register
* get_register
* incrementPC
* isClockEnabled
* isMoreCycleWorkNeeded
* instruction_add
* instruction_addi
* instruction_beq
* instruction_blt
* instruction_bneq
* instruction_inv
* instruction_halt
* instruction_lw
* instruction_mul
* instruction_sw
* instructionBitSelector
* nextState
* parseInstructions
* reset
* set_reg
* startTick

## IMemory
* create
* dump
* get_memory
* nextState
* parseInstructions
* printBankHeaders
* reset
* set
* set_memory

## Memory
* create
* doCycleWork
* dump
* get_memory
* isMoreCycleWorkNeeded
* nextState
* parseInstructions
* printBankHeaders
* reset
* set
* set_memory(int,int);
* startFetch
* startStore
* startTick
