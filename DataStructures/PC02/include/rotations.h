/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: rotations.h
 * Date Created: 9/14/2021
 * File Contents: Contains the function declarations
 *                for Programming Challenge 02
 **********************************/
 #include <stdbool.h>
 #include <stdio.h>
 #include <stdlib.h>

 void read_user_opt(long unsigned int* size_arr, long unsigned int* num_rot, bool* rot_dir);
 void read_user_val(long unsigned int size_arr, int arr[], long unsigned int arr_order[]);
 void print_arr(long unsigned int size_arr, int arr[], long unsigned int arr_order[]);
 void rotate_order(long unsigned int size_arr, long unsigned int* arr_order, long unsigned int num_rot, bool rot_dir);
