/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: PC03.c
 * Date Created: 9/21/2021
 * File Contents: This file contains the main driver function for Programming Challenge 03
 * Program based on sllist_part13_sol.c by Dr. Matthew Morrison
 **********************************/
#include "../include/sllist.h"

 int main( const int argc, const char* argv[] ){

	sllist* the_list = (sllist *)malloc( sizeof( sllist ) );

	the_list->head_node = NULL;

	int iter;
	for( iter = 1; iter < argc; ++iter ){
		int the_value = atoi( argv[iter] );
		insert( the_list, the_value );
	}

  fprintf(stdout, "Initial List:\n");
	print_list( the_list->head_node );

  reverse_func(&the_list->head_node);

  fprintf(stdout, "\nReversed List:\n");
  print_list(the_list->head_node);
  fprintf(stdout, "\n");
	destructor( the_list->head_node );
	free( the_list );

	return EXIT_SUCCESS;
}
