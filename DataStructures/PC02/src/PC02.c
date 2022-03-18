/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: PC02.c
 * Date Created: 9/14/2021
 * File Contents: Contains the main driver function
 *                for Programming Challenge 02
 **********************************/
 #include "../include/rotations.h"

 int main() {
     long unsigned int size_arr;
     long unsigned int num_rot;
     bool rot_dir; //0 = left, 1 = right
     bool cont = true;
     while(cont){
         read_user_opt(&size_arr, &num_rot, &rot_dir);
         long unsigned int* arr_order = (long unsigned int*)malloc(size_arr*sizeof(long unsigned int));
         int* arr = (int*)malloc(size_arr*sizeof(int));
         read_user_val(size_arr, arr, arr_order);
         fprintf(stdout, "Before Rotation:\n");
         print_arr(size_arr, arr, arr_order);
         rotate_order(size_arr, arr_order, num_rot, rot_dir);
         fprintf(stdout, "After Rotation:\n");
         print_arr(size_arr, arr, arr_order);
         free(arr_order);
         free(arr);

         fprintf(stdout, "Do you wish to continue? (y/n): ");
         char user_cont;
         fscanf(stdin, "%c", &user_cont);
         while(getchar() != '\n') {}
         if(user_cont == 'n')
            cont = false;
     }
 }
