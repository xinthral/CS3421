/**************************************
# Author: Jesse Hassell
# Date: Nov, 2021
# The cache device sits between the CPU and Data Memory, and can improve memory
# performance. The cache contains 8 bytes of high speed memory, and contains
# logic to handle data passing through it from read/lw instructions and write/sw
# instructions.
**************************************/

#include "cache.h"

Cache::Cache(int debug) {
    DEBUG = debug;
}
void Cache::reset() {
    /* The "reset" command resets the cache to disabled, setting CLO to zero,
    # and data to be invalid. */
}

void Cache::cacheOn() {
    /* The "on" command enables the cache, causing it to keep copies of data
    # transferred between the CPU and Data Memory. The coder may assume cache
    # will only be enabled when the CPU is idle (about to start a new
    # instruction). */
}

void Cache::cacheOff() {
    /* The "off" command disables the cache, causing the system to act as if no
    # cache were present. Any data written to the cache should be written to
    # memory (cache flush). The coder may assume cache will only be disabled
    # when the CPU is idle (about to start a new instruction). */

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
    #       CLO         : 0x01
    #       cache data  : 0x00 0x18 0x22 0xFF 0xEE 0x27 0x1E 0xAE
    #       Flags       :   V    V    W    W    V    V    V    V
    */
}
