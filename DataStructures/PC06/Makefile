# Author: Hayden Owens
# Email: howens@nd.edu
# Created On: 10/20/2021
# This is the Makefile for Programming Challenge 06

# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flags
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# make initialize
initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# make JK_Test
JK_TestObjs := $(OBJ)/JK_Test.o $(OBJ)/JKFF.o

JK_Test: $(JK_TestObjs)
		$(PP) $(CXXFLAGS) -o $(EXE)/JK_Test $(JK_TestObjs)

$(OBJ)/JK_Test.o: $(SRC)/JK_Test.cpp
		$(PP) $(CXXFLAGS) -c $(SRC)/JK_Test.cpp -o $@

$(OBJ)/JKFF.o: $(SRC)/JKFF.cpp
		$(PP) $(CXXFLAGS) -c $(SRC)/JKFF.cpp -o $@

# make BDC_Test
BDC_TestObjs := $(OBJ)/BDC_Test.o $(OBJ)/BDC.o $(OBJ)/JKFF.o

BDC_Test: $(BDC_TestObjs)
		$(PP) $(CXXFLAGS) -o $(EXE)/BDC_Test $(BDC_TestObjs)

$(OBJ)/BDC_Test.o: $(SRC)/BDC_Test.cpp
		$(PP) $(CXXFLAGS) -c $(SRC)/BDC_Test.cpp -o $@

$(OBJ)/BDC.o: $(SRC)/BDC.cpp
		$(PP) $(CXXFLAGS) -c $(SRC)/BDC.cpp -o $@


# make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
