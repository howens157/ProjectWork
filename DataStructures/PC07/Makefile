# Author: Hayden Owens
# Email: howens@nd.edu
# Created On: 11/9/2021
# This is the Makefile for Programming Challenge 07

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

# make PC07
$(OBJ)/PC07.o: $(SRC)/PC07.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/PC07.cpp -o $@

$(OBJ)/palindrome.o: $(SRC)/palindrome.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/palindrome.cpp -o $@

PC07_objs := $(OBJ)/PC07.o $(OBJ)/palindrome.o

PC07: $(PC07_objs)
	$(PP) $(CFLAGS) -o $(EXE)/PC07 $(PC07_objs)

# make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
