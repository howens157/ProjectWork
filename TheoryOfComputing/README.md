# Theory of Computing
This folder contains project work for my Theory of Computing course.

Programming Assignment 1 (pa1) is concerned with simulating a Nondeterministic Finite Automata, reading in a the states and transitions from a .nfa file (located in ExampleNFAs), taking a string from the command line, and outputting whether that string is recognized by the NFA.
#
Programming Assignment 2 (pa2) makes use of several executables that allow a regular expression to be parsed, and allow NFAs to be constructed from a string or by the union, concatenation, or Kleene star operation. These functions are then combined to create "agrep", an automoton-based version of grep, that takes a regular expression, parses it and then constructs an NFA to recognize the regular expression by walking up the parse tree. It then takes in lines of text from the input stream and outputs the strings that match the given regular expression.
