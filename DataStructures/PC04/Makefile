# Author: Hayden Owens
# E-mail: howens@nd.edu
#
# This is the Makefile for Programming Challenge 04 - CSE 20312

# gcc is for the compiler for C
PP := gcc

# CFLAGS are the compiler flages for when we compile C code in this course
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


# Create the Binary Search Tree Object
$(OBJ)/bst.o: $(SRC)/bst.c
	$(PP) $(CFLAGS) -c $(SRC)/bst.c -o $@


# Create the PC04 object
$(OBJ)/PC04.o: $(SRC)/PC04.c
	$(PP) $(CFLAGS) -c $(SRC)/PC04.c -o $@

# Create the rw2bc object
$(OBJ)/rw2bc.o: $(SRC)/rw2bc.c
	$(PP) $(CFLAGS) -c $(SRC)/rw2bc.c -o $@


# PC04 Objects
PC04_objs := $(OBJ)/bst.o $(OBJ)/PC04.o

# rw2bc Objects
rw2bc_objs := $(OBJ)/rw2bc.o

# Singly Linked List Executable and Run
PC04: $(PC04_objs)
	$(PP) $(CFLAGS) -o $(EXE)/PC04 $(PC04_objs)

rw2bc: $(rw2bc_objs)
	$(PP) $(CFLAGS) -o $(EXE)/rw2bc $(rw2bc_objs)


# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
