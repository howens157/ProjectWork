/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: PC01.c
 * Date Created: 9/2/2021
 * File Contents: Contains the main driver function
 *                for Programming Challenge 01
 **********************************/

#include "sudoku.h"

int main( const int argc, const char* argv[] ){

    if(argc != 2)
    {
        fprintf(stderr, "Error: argc = %d. Should = 2\n", argc);
        exit(EXIT_FAILURE);
    }

    FILE* puzzle_file = fopen(argv[1], "r");

    int** sudoku = (int**)malloc(ROWS*sizeof(int*));
    malloc_puzzle(sudoku);
    read_puzzle(sudoku, puzzle_file);

    int user_input = 0;
    while(user_input != 4)
    {
        fprintf(stdout, "Please select from the following choices:\n"
                        "1: Print the current puzzle\n"
                        "2: Insert value into puzzle\n"
                        "3: Automatically solve the puzzle (in progress)\n"
                        "4: Exit the game\n"
                        "Insert your choice here: ");
        fscanf(stdin, "%d", &user_input);
        switch (user_input) {
            case 1:
                print_puzzle(sudoku);
                break;
            case 2:
                insert_and_check_puzzle(sudoku);
                break;
            case 3:
                auto_solve(sudoku);
                break;
            case 4:
                fprintf(stdout, "Thank you for playing!\n");
                break;
            default:
                fprintf(stderr, "Invalid Choice\n");
        }
        if(check_puzzle(sudoku))
        {
            fprintf(stdout, "Congratulations! You have solved the puzzle!\n");
            print_puzzle(sudoku);
            break;
        }
    }

    fclose(puzzle_file);
    free_puzzle(sudoku);
    return 0;
  }
