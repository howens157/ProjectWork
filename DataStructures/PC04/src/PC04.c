/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: PC04.c
 * Date Created: 9/29/2021
 * File Contents: This file contains the main driver function for Programming Challenge 04
 **********************************/
#include "../include/bst.h"

int main( const int argc, const char* argv[] ){

	if( argc < 2 ){

		fprintf( stderr, "Needs more than one input.\n" );

		return EXIT_FAILURE;
	}

	// Create the Binary Search Tree
	bst* int_bst = (bst*)malloc( sizeof(bst) );

	constructor( int_bst );

	int iter;
	for( iter = 1; iter < argc; ++iter ){

		int input_value = atoi( argv[iter] );

		insert( &(int_bst->root), input_value );

	}

	// Print initial tree
	fprintf( stdout, "---------------------------------\n");
	fprintf( stdout, "Initial Tree\n");
	fprintf( stdout, "In-order traversal  : " );
	in_order_traversal( int_bst->root );
	fprintf( stdout, "\n" );

	fprintf( stdout, "Pre-order traversal : " );
	pre_order_traversal( int_bst->root );
	fprintf( stdout, "\n" );

	fprintf( stdout, "Post-order traversal: " );
	post_order_traversal( int_bst->root );
	fprintf( stdout, "\n" );

	// Print outputs
	fprintf( stdout, "---------------------------------\n");
	int curr_value = 0;
	int solution = 0;
	find_kth_element( int_bst->root, 4, &curr_value, &solution );
	fprintf( stdout, "The 4th largest element is %d\n", solution );

	// Print the Maximum Depth
	fprintf( stdout, "---------------------------------\n");
	long unsigned int* maxdepth = (long unsigned int*)malloc(sizeof(long unsigned int));
	*maxdepth = 0;
	fprintf( stdout, "The maximum depth is %lu\n", maximum_depth( int_bst->root, 1 , maxdepth) );
	free(maxdepth);
	// Print the Reverse and Print the Tree
	fprintf( stdout, "---------------------------------\n");

	// Reverse the tree
	reverse_tree( &(int_bst->root) );

	fprintf( stdout, "Final Tree\n");
	fprintf( stdout, "In-order traversal  : " );
	in_order_traversal( int_bst->root );
	fprintf( stdout, "\n" );

	fprintf( stdout, "Pre-order traversal : " );
	pre_order_traversal( int_bst->root );
	fprintf( stdout, "\n" );

	fprintf( stdout, "Post-order traversal: " );
	post_order_traversal( int_bst->root );
	fprintf( stdout, "\n" );

	// Call the destructor on the root
	destructor( int_bst->root );

	// Free the Binary Search Tree pointer
	free( int_bst );

	return 0;

}
