# Authors: Payton Lewandowski - plewando@nd.edu
#          Hayden Owens - howens@nd.edu
#          Thomas Knipe - tknipe@nd.edu
#          Eduardo Yepiz - eyepiz@nd.edu
# Makefile for Final Project

# G++ is for the GCC compiler for C++
PP := g++

# Compiler flags
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Folder variables
INC := inc
SRC := src
OBJ := objects
EXE := exe

# make initialize

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# make AutoCompleter

$(OBJ)/AutoCompleter.o: $(SRC)/AutoCompleter.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/AutoCompleter.cpp -o $@

AutoCompleter_objs := $(OBJ)/AutoCompleter.o

AutoCompleter: $(AutoCompleter_objs)
	$(PP) $(CXXFLAGS) -o $(EXE)/AutoCompleter $(AutoCompleter_objs)

# make all

all: AutoCompleter

# make clean

clean:
	rm -rf $(OBJ)/* $(EXE)/* *.o
