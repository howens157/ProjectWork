# Name: Hayden Owens
# E-mail: howens@nd.edu
# Date Created: 9/21/2021
# File Contents: This is the Makefile for compilation of Programming Challenge 03

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

# PC03
$(OBJ)/sllist.o: $(SRC)/sllist.c
	$(PP) $(CFLAGS) -c $(SRC)/sllist.c -o $@

$(OBJ)/PC03.o: $(SRC)/PC03.c
	$(PP) $(CFLAGS) -c $(SRC)/PC03.c -o $@

$(OBJ)/rw2bc.o: $(SRC)/rw2bc.c
	$(PP) $(CFLAGS) -c $(SRC)/rw2bc.c -o $@

PC03_objs := $(OBJ)/sllist.o $(OBJ)/PC03.o

rw2bc_objs := $(OBJ)/sllist.o $(OBJ)/rw2bc.o

PC03: $(PC03_objs)
	$(PP) $(CFLAGS) -o $(EXE)/PC03 $(PC03_objs)

rw2bc: $(rw2bc_objs)
	$(PP) $(CFLAGS) -o $(EXE)/rw2bc $(rw2bc_objs)

# Make clean
clean:
	rm -rf $(OBJ)/* $(EXE)/*
