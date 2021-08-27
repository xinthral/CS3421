#/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
#  -std	  - compile with c99 compatibility
CFLAGS  = -g -Wall -std=c99

# The build target
EXECUTABLE = emul
CLK = clock
CPU = cpu
MEM = memory
PRS = parser

all: $(EXECUTABLE)

$(EXECUTABLE): $(CLK).o $(CPU).o $(MEM).o $(PRS).o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(CLK).o $(CPU).o $(MEM).o $(PRS).o

# This is how the instructions say to do it
#$(CLK).o: $(CLK).h
#$(CPU).o: $(CPU).h
#$(MEM).o: $(MEM).h
#$(PRS).o: $(CLK).h $(CPU).h $(MEM).h

# This makes more sense to me but is probably wrong
$(CLK).o: $(CLK).cpp $(CLK).h
	$(CC) $(CFLAGS) -c $(CLK).cpp

$(CPU).o: $(CPU).cpp $(CPU).h
	$(CC) $(CFLAGS) -c $(CPU).cpp

$(MEM).o: $(MEM).cpp $(MEM).h
	$(CC) $(CFLAGS) -c $(MEM).cpp

$(PRS).o: $(PRS).cpp $(PRS).h
	$(CC) $(CFLAGS) -c $(PRS).cpp

clean:
	$(RM) *.o $(EXECUTABLE)
