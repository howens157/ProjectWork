/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: rotations.c
 * Date Created: 9/14/2021
 * File Contents: Contains the function definitions
 *                for Programming Challenge 02
 **********************************/
#include "../include/rotations.h"

void read_user_opt(long unsigned int* size_arr, long unsigned int* num_rot, bool* rot_dir) {
    char temp = 'Q';
    fprintf(stdout, "Enter the size, num rotations, and direction: ");
    fscanf(stdin, "%lu %lu %c", size_arr, num_rot, &temp);
    while(getchar() != '\n') {}
    if(temp == 'L')
        *rot_dir = false;
    else if(temp == 'R')
        *rot_dir = true;
    else{
        fprintf(stderr, "Invalid Direction Specifier\n");
        exit(EXIT_FAILURE);
    }
}

void read_user_val(long unsigned int size_arr, int* arr, long unsigned int* arr_order) {
    fprintf(stdout, "Input the %lu values: ", size_arr);
    long unsigned int iter;
    for(iter = 0; iter < size_arr; ++iter){
        fscanf(stdin, " %d", &arr[iter]);
        arr_order[iter] = iter;
    }
    while(getchar() != '\n') {}
}

void print_arr(long unsigned int size_arr, int* arr, long unsigned int* arr_order) {
    long unsigned int iter;
    for(iter = 0; iter < size_arr; ++iter){
        fprintf(stdout, "%d at %p\n", arr[arr_order[iter]], &arr[arr_order[iter]]);
    }
}

void rotate_order(long unsigned int size_arr, long unsigned int* arr_order, long unsigned int num_rot, bool rot_dir) {
    long unsigned int iter, jter;
    long unsigned int temp;
    num_rot = num_rot%size_arr;
    for(iter = 0; iter < num_rot; ++iter) {
        if(rot_dir) {
            temp = arr_order[size_arr-1];
            for(jter = size_arr-1; jter > 0; --jter) {
                arr_order[jter] = arr_order[jter-1];
            }
            arr_order[0] = temp;
        }
        else {
            temp = arr_order[0];
            for(jter = 0; jter < size_arr-1; ++jter) {
                arr_order[jter] = arr_order[jter+1];
            }
            arr_order[size_arr-1] = temp;
        }
    }
}
