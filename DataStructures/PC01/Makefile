# Name: Hayden Owens
# E-mail: howens@nd.edu
# Date Created: 9/2/2021
# File Contents: This is the Makefile for compilation of Programming Challenge 01

# gcc is for the GCC compiler for C
PP:= gcc

# CFLAGS are the compiler flags for when we compile C code in this course
CFLAGS:= -O2 -g -Wall -Wextra -Wconversion -Wshadow -std=c11 -Werror -lm

# Command: make PC01
# This will create PC01
sudoku.o: sudoku.c
	$(PP) $(CFLAGS) -c sudoku.c
PC01.o: PC01.c
	$(PP) $(CFLAGS) -c PC01.c
# PC01 Objects
PC01_objs:= PC01.o sudoku.o
# PC01 Executable
PC01: $(PC01_objs)
	$(PP) $(CFLAGS) -o PC01 $(PC01_objs)

# Clean Command
clean:
	rm -rf *.o PC01
