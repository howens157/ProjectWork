/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: rw2bc.c
 * Date Created: 9/21/2021
 * File Contents: This file contains the main driver function for the rw2bc
 * for Programming Challenge 03
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

  fprintf(stdout, "\nProvide the nth-element from the end to delete: ");
  long unsigned int del_loc;
  fscanf(stdin, "%lu", &del_loc);
  while(getchar() != '\n'){}

  delete_nth(&the_list->head_node, del_loc);

  fprintf(stdout, "\nNew List:\n");
  print_list(the_list->head_node);
  fprintf(stdout, "\n");

 	destructor( the_list->head_node );
 	free( the_list );

 	return EXIT_SUCCESS;
 }
