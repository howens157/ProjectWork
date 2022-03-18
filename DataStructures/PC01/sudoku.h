/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: sudoku.h
 * Date Created: 9/2/2021
 * File Contents: This file contains the function declarations
 *                for Programming Challenge 01
 **********************************/

#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 9
#define COLS 9

#endif

void malloc_puzzle(int** sudoku);
void free_puzzle(int** sudoku);
void read_puzzle(int** sudoku, FILE* input_file);
void print_puzzle(int** sudoku);
unsigned int check_puzzle( int** sudoku );
void insert_and_check_puzzle( int** sudoku);
void auto_solve(int** sudoku);
bool solve_recurs(int** sudoku, int** solving, long unsigned int row, long unsigned int col);
void reset_puzzle(int** sudoku, int** solving, long unsigned int row, long unsigned int col);
