#/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
# This is how the instructions say to do it

# Dynamically assign *.o to be compiled from its .cpp counterpart
# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $<
#**************************************/

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  	-g			- this flag adds debugging information to the executable file
#  	-Wall		- this flag is used to turn on most compiler warnings
# 	-O			- optimization level (ie -O3)
#  	-std		- compile with version compatibility
#  	-no-pie 	- do not produce a position-independent executable
#	-fPIC		- Format position-independent code
CFLAGS   = -g -Wall -O3
CXFLAGS  = -fPIC
CXXFLAGS = -fPIC

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
	$(CC) $(CFLAGS) $(CXFLAGS) -o $(TST) $^

# Define Object Files
$(CLK).o: $(CLK).h
$(CPU).o: $(CPU).h
$(MEM).o: $(MEM).h
$(PRS).o: $(CLK).h $(CPU).h $(MEM).h
$(TST).o: $(CLK).h $(CPU).h $(MEM).h $(TST).h

# Template function to compile defined objects files
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXFLAGS) -c $<

clean:
	$(RM) *.o $(EXECUTABLE) $(TST)


# Compiled Clock component
# $(CLK).o: $(CLK).cpp $(CLK).h
# 	$(CC) $(CFLAGS) $(CXFLAGS) -c $(CLK).cpp

# Compile CPU component
# $(CPU).o: $(CPU).cpp $(CPU).h
# 	$(CC) $(CFLAGS) $(CXFLAGS) -c $(CPU).cpp

# Compile Memory component
# $(MEM).o: $(MEM).cpp $(MEM).h
# 	$(CC) $(CFLAGS) $(CXFLAGS) -c $(MEM).cpp

# Compile Parser component
# $(PRS).o: $(PRS).cpp $(PRS).h $(CLK).h $(CPU).h $(MEM).h
# 	$(CC) $(CFLAGS) $(CXFLAGS) -c $(PRS).cpp

# Compile Testing component
# $(TST).o: $(TST).cpp $(TST).h $(CLK).h $(CPU).h $(MEM).h
# 	$(CC) $(CFLAGS) $(CXXFLAGS) -c $(TST).cpp
