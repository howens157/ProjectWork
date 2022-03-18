# Name: Hayden Owens
# E-mail: howens@nd.edu
# Date Created: 9/14/2021
# File Contents: This is the Makefile for compilation of Programming Challenge 01

# gcc is the compiler for C
PP := gcc

# CFLAGS are the compiler flags for when we compile C code in this course
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
CFLAGS := -std=c11 $(FLAGS)

# Folder Variables
SRC := src
INC := include
OBJ := objects
EXE := exe

# Initialize the folders for the objects and executables
initialize:
	mkdir $(OBJ) $(EXE)

# Create the Rotations Object
$(OBJ)/rotations.o: $(SRC)/rotations.c
	$(PP) $(CFLAGS) -c $(SRC)/rotations.c -o $@

# Create the PC02 object
$(OBJ)/PC02.o: $(SRC)/PC02.c
	$(PP) $(CFLAGS) -c $(SRC)/PC02.c -o $@

# Rotations Objects
PC02_objs := $(OBJ)/rotations.o $(OBJ)/PC02.o

# Rotaions Executable and Run
PC02: $(PC02_objs)
	$(PP) $(CFLAGS) -o $(EXE)/PC02 $(PC02_objs)

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
