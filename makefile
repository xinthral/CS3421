#/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
#**************************************/

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  	-g			- this flag adds debugging information to the executable file
#  	-Wall		- this flag is used to turn on most compiler warnings
#  	-std		- compile with version compatibility
#  	-no-pie 	- do not produce a position-independent executable
#	-fPIC		- Format position-independent code
CFLAGS  = -g -Wall -fPIC

# The build target
EXECUTABLE = emul
TESTFILES = emul_t
CLK = clock
CPU = cpu
MEM = memory
PRS = parser
TST = test

build: $(EXECUTABLE)

test: $(TESTFILES)
# This is how the instructions say to do it
# $(CLK).o: $(CLK).h
# $(CPU).o: $(CPU).h
# $(MEM).o: $(MEM).h
# $(PRS).o: $(CLK).h $(CPU).h $(MEM).h
# $(TST).o: $(CLK).h $(CPU).h $(MEM).h $(TST).h

# Dynamically assign *.o to be compiled from its .cpp counterpart
# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $<

# Compile Clock component
$(CLK).o: $(CLK).cpp $(CLK).h
	$(CC) $(CFLAGS) -c $(CLK).cpp

# Compile CPU component
$(CPU).o: $(CPU).cpp $(CPU).h
	$(CC) $(CFLAGS) -c $(CPU).cpp

# Compile Memory component
$(MEM).o: $(MEM).cpp $(MEM).h
	$(CC) $(CFLAGS) -c $(MEM).cpp

# Compile Parser component
$(PRS).o: $(PRS).cpp $(PRS).h $(CLK).h $(CPU).h $(MEM).h
	$(CC) $(CFLAGS) -c $(PRS).cpp

# Compile Testing component
$(TST).o: $(TST).cpp $(TST).h $(CLK).h $(CPU).h $(MEM).h
	$(CC) $(CFLAGS) -c $(TST).cpp

# Compile Full porgram
$(EXECUTABLE): $(CLK).o $(CPU).o $(MEM).o $(PRS).o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $^

# Compile Full program plus tests
$(TESTFILES): $(CLK).o $(CPU).o $(MEM).o $(TST).o
	$(CC) $(CFLAGS) -o $(TESTFILES) $^

clean:
	$(RM) *.o $(EXECUTABLE) $(TESTFILES) $(TST)
