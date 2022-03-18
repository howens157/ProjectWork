/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: sudoku.c
 * Date Created: 9/2/2021
 * File Contents: This file contains the function definitions
 *                for Programming Challenge 01
 **********************************/

#include "sudoku.h"

void malloc_puzzle(int** sudoku)
{
    long unsigned iterator;
    for(iterator = 0; iterator < COLS; ++iterator)
    {
        sudoku[iterator] = (int*)malloc(COLS*sizeof(int));
    }
}

void free_puzzle(int** sudoku)
{
    long unsigned iterator;
    for(iterator = 0; iterator < COLS; ++iterator)
    {
        free(sudoku[iterator]);
    }
    free(sudoku);
}

void read_puzzle(int** sudoku, FILE* input_file)
{
    long unsigned int row_input = 0;
    long unsigned int col_input = 0;
    int temp;
    while(input_file != NULL)
    {
        /* Read in an integer from the input file */
        fscanf(input_file, "%d", &temp);
        /* Place the int at the appropriate row and column */
        sudoku[row_input][col_input] = temp;
        /* If col_input is less than COLS - 1, increment col_input */
        if(col_input < COLS - 1)
            col_input++;
        /* Otherwise, increment row_input and set col_input = 0 */
        else
        {
            row_input++;
            col_input = 0;
        }
        /* Break the while loop if we've reached the end of the file */
        if(input_file->_IO_read_ptr == input_file->_IO_read_end)
            break;
    }
}

void print_puzzle(int** sudoku)
{
    long unsigned int rter;
    long unsigned int cter;

    for(rter = 0; rter < ROWS; ++rter)
    {
        for(cter = 0; cter < COLS; ++cter)
        {
            fprintf(stdout, "%d ", sudoku[rter][cter]);
        }
        fprintf(stdout, "\n");
    }
}

unsigned int check_puzzle( int** sudoku )
{
    long unsigned int rter;
    long unsigned int cter;

    for(rter = 0; rter < ROWS; ++rter)
        for(cter = 0; cter < COLS; ++cter)
            if(sudoku[rter][cter] == 0)
                return 0;

    return 1;
}

void insert_and_check_puzzle( int** sudoku)
{
    int user_val;
    long unsigned int user_row, user_col;
    fprintf(stdout, "Insert the value, row, and column here: ");
    fscanf(stdin, "%d %lu %lu", &user_val, &user_row, &user_col);
    if(user_val < 1 || user_val > 9) {
        fprintf(stderr, "The value must be between 1 and 9. You entered %d\n", user_val);
        return;
    }
    if(user_row > 8) {
        fprintf(stderr, "The row must be between 1 and 9. You entered %lu\n", user_row);
        return;
    }
    if(user_col > 8) {
        fprintf(stderr, "The column must be between 1 and 9. You entered %lu\n", user_col);
        return;
    }
    long unsigned int rter, cter;
    //Check the row
    for(cter = 0; cter < COLS; ++cter)
        if(sudoku[user_row][cter] == user_val) {
            fprintf(stderr, "There is already a %d in that row at (%lu, %lu).\n", user_val, user_row, cter);
            return;
        }
    //Check the col
    for(rter = 0; rter < ROWS; ++rter)
        if(sudoku[rter][user_col] == user_val) {
            fprintf(stderr, "There is already a %d in that column at (%lu, %lu).\n", user_val, rter, user_col);
            return;
        }
    //Check the 3x3 box
    for(rter = user_row-(user_row%3); rter < user_row-(user_row%3)+2; ++rter)
        for(cter = user_col-(user_col%3); cter < user_col-(user_col%3)+2; ++cter)
            if(sudoku[rter][cter] == user_val) {
                fprintf(stderr, "There is already a %d in that box at (%lu, %lu).\n", user_val, rter, cter);
                return;
            }

    sudoku[user_row][user_col] = user_val;
    return;
}

void auto_solve(int** sudoku)
{
    int** solving = (int**)malloc(ROWS*sizeof(int*));
    malloc_puzzle(solving);

    long unsigned int iter, jter;
    for(iter = 0; iter < ROWS; ++iter) {
        for(jter = 0; jter < COLS; ++jter) {
            solving[iter][jter] = sudoku[iter][jter];
        }
    }

    solve_recurs(sudoku, solving, 0, 0);

    for(iter = 0; iter < ROWS; ++iter) {
        for(jter = 0; jter < COLS; ++jter) {
            sudoku[iter][jter] = solving[iter][jter];
        }
    }
    print_puzzle(solving);
    free_puzzle(solving);
}

//I tried to just use a brute force method to find a solution. It works for puzzle
//1 when there are not many empty cells, but puzzle 2 runs for too long and puzzle
//3 runs into other errors I have not been able to solve.
//I consulted https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#Constraint_programming
//as the basis of my brute force attempt
bool solve_recurs(int** sudoku, int** solving, long unsigned int row, long unsigned int col)
{
    if(sudoku[row][col] != 0) {
        if(col == 8) {
            if(row == 8)
                return true;
            else if(solve_recurs(sudoku, solving, row+1, 0))
                return true;
        }
        else {
            if(solve_recurs(sudoku, solving, row, col+1))
                return true;
        }
    }
    else {
        long unsigned int iter, rter, cter;
        bool valid = true;
        int curr_testval;
        for(iter = 1; iter < 10; ++iter) {
            valid = true;
            reset_puzzle(sudoku, solving, row, col);
            curr_testval = (int)iter;
            //Check the row
            for(cter = 0; cter < COLS; ++cter)
                if(solving[row][cter] == curr_testval) {
                    valid = false;
                }
            //Check the col
            for(rter = 0; rter < ROWS; ++rter)
                if(solving[rter][col] == curr_testval) {
                    valid = false;
                }
            //Check the 3x3 box
            for(rter = row-(row%3); rter < row-(row%3)+2; ++rter)
                for(cter = col-(col%3); cter < col-(col%3)+2; ++cter)
                        if(solving[rter][cter] == curr_testval) {
                        valid = false;
                    }
            if(valid) {
                solving[row][col] = curr_testval;
                if(col == 8) {
                    if(solve_recurs(sudoku, solving, row+1, 0))
                        return true;
                }
                else {
                    if(solve_recurs(sudoku, solving, row, col+1))
                        return true;
                }
            }
        }
    }
    return false;
}

void reset_puzzle(int** sudoku, int** solving, long unsigned int row, long unsigned int col)
{
    long unsigned int iter, jter;
    for(iter = col; iter < COLS; ++iter) {
        solving[row][iter] = sudoku[row][iter];
    }
    for(iter = row + 1; iter < ROWS; ++iter) {
        for(jter = 0; jter < COLS; ++jter) {
            solving[row][iter] = sudoku[row][iter];
        }
    }
}
