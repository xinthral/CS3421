#/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
# This is how the instructions say to do it

#**************************************/

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# compiler flags:
#  	-g			- adds debugging information to the executable file
#  	-Wall		- is used to turn on most compiler warnings
#  	-Wextra		- turns on extra compiler checks unchecked by -Wall
# 	-O			- optimization level (ie -O3)
#  	-std		- compile with version compatibility
#  	-no-pie 	- do not produce a position-independent executable
#	-fPIC		- Format position-independent code
CFLAGS   = -g
CXFLAGS  = -O3 -fPIC
CXXFLAGS = -Wall -Wextra -fPIC

# The build target
EXECUTABLE = cs3421_emul
CLK = clock
CPU = cpu
MEM = memory
PRS = parser
TST = test

# Compile Full porgram
all: $(CLK).o $(CPU).o $(MEM).o $(PRS).o
	$(CC) $(CFLAGS) $(CXFLAGS) -o $(EXECUTABLE) $^

# Compile Full program plus tests
test: $(CLK).o $(CPU).o $(MEM).o $(TST).o
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $(TST) $^

# Define Object Files
$(CLK).o: $(CLK).h
$(CPU).o: $(CPU).h
$(MEM).o: $(MEM).h
$(PRS).o: $(CLK).h $(CPU).h $(MEM).h
$(TST).o: $(CLK).h $(CPU).h $(MEM).h $(TST).h

# Template function to compile defined objects files
# Dynamically assign *.o to be compiled from its .cpp counterpart
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXFLAGS) -c $<

clean:
	$(RM) *.o $(EXECUTABLE) $(TST)
