#/**************************************
# Author: Jesse Hassell
# Date: Aug, 2021
# Purpose: Make file to manage the different components of this
# build and be able to compile them individually.
# This is how the instructions say to do it

#**************************************/

# the compiler: gcc for C program, define as g++ for C++
CC = g++

# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# compiler flags:
#  	-g			- adds debugging information to the executable file
#  	-Wall		- is used to turn on most compiler warnings
#  	-Wextra		- turns on extra compiler checks unchecked by -Wall
# 	-O			- optimization level (ie -O3)
#  	-std		- compile with version compatibility
#  	-no-pie 	- do not produce a position-independent executable
#	-fPIC		- Format position-independent code
CFLAGS   = -g -fPIC -std=c++11
CXFLAGS  = -Wall -Wextra -Werror -Wfatal-errors -pedantic -fno-stack-protector
CXXFLAGS = -Wno-unused-result -Wno-format-extra-args -Wno-unused-variable -Wno-unused-parameter -Wno-write-strings

# The build target
EXECUTABLE = cs3421_emul
TESTOUTPUT = xtester.exe
CLK = clock
CPU = cpu
CSH = cache
IOD = iodevice
MEM = memory
MIM = imemory
PRS = parser
TST = xtest
UTL = utilities

# # Compile Full porgram
all: $(CLK).o $(CPU).o $(CSH).o $(IOD).o $(MEM).o $(MIM).o $(PRS).o $(UTL).o
	$(CC) $(CFLAGS) $(CXFLAGS) -o $(EXECUTABLE) $^

# Compile Full program plus tests
test: $(CLK).o $(CPU).o $(CSH).o $(IOD).o $(MEM).o $(MIM).o $(TST).o $(UTL).o
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $(TESTOUTPUT) $^

# Define Object Files
$(CLK).o: $(CLK).h
$(CPU).o: $(CPU).h
$(CSH).o: $(CSH).h
$(IOD).o: $(IOD).h
$(MEM).o: $(MEM).h
$(MIM).o: $(MIM).h
$(UTL).o: $(UTL).h
$(PRS).o: $(CLK).h $(CPU).h $(CSH).h $(IOD).h $(MEM).h $(MIM).h $(PRS).h $(UTL).h
$(TST).o: $(CLK).h $(CPU).h $(CSH).h $(IOD).h $(MEM).h $(MIM).h $(TST).h $(UTL).h

# Template function to compile defined objects files
# Dynamically assign *.o to be compiled from its .cpp counterpart
%.o: %.cpp
ifeq ($(DEBUG), 1)
	$(CC) $(CFLAGS) $(CXFLAGS) -c $<
else
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<
endif

clean:
	$(RM) *.o $(EXECUTABLE) $(TESTOUTPUT)
