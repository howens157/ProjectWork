/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: PC04.c
 * Date Created: 9/29/2021
 * File Contents: This file contains the main driver function and function
 * declarations/definitions for the rw2bc for Programming Challenge 04
 * This program use functions from both bst_final.c and sllist_sol.c written by
 * Dr. Matthew Morrison
 **********************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct bst_node{

	int value;

	struct bst_node* left;

	struct bst_node* right;

} bst_node;


typedef struct bst{

	struct bst_node* root;

} bst;

typedef struct sll_node{

	struct bst_node* bst;
	struct sll_node* next_node;

}sll_node;

typedef struct sllist{

	struct sll_node* head_node;

} sllist;

void constructor( bst* int_bst ){

	// Set the root to NULL
	int_bst->root = NULL;

}


void insert( bst_node** curr_node, int value ){

	// Dr. Morrison's Golden rule of pointers
	if( *curr_node == NULL ){

		// We found the place to insert! Now create the node.
		bst_node* insert_node = (bst_node*)malloc( sizeof(bst_node) );
		insert_node->value = value;
		insert_node->left = NULL;
		insert_node->right = NULL;

		// Finally, set the curr_node equal to insert_node
		*curr_node = insert_node;

		return;

	}

	else if( value < (*curr_node)->value )
		insert( &((*curr_node)->left), value );

	else if( (*curr_node)->value < value )
		insert( &((*curr_node)->right), value );

	else
		fprintf( stdout, "%d is already in the tree\n", value );
}

void destructor( bst_node* curr_node ){

	if( curr_node == NULL )
		return;

	destructor( curr_node->left );

	destructor( curr_node->right );

	free( curr_node );

}

void push_back( sllist* the_list, bst_node* new ){

	// De-reference in order to allocate and preserve the memory
	sll_node* new_node = ( sll_node* )malloc( sizeof( struct sll_node ) );

	// De-reference new_node and update data
	new_node->bst = new;

	// De-reference new_node and set the next pointer equal to NULL
	new_node->next_node = NULL;

	// Dr. Morrison's Golden Rule of Pointers
	if( the_list->head_node == NULL ){

		the_list->head_node = new_node;
		return;
	}

	sll_node* curr_node = the_list->head_node;

	while( curr_node->next_node != NULL ){
		curr_node = curr_node->next_node;
	}
	curr_node->next_node = new_node;
}

bst_node* pop_front( sllist* the_list ){

	// Dr. Morrison's Golden Rule of Pointers
	if( the_list->head_node == NULL )
		return 0;
	bst_node* popped = the_list->head_node->bst;
	// Create a temporary pointer pointing to the head node
	sll_node* to_free = the_list->head_node;

	// move the head node pointer to the next node
	the_list->head_node = the_list->head_node->next_node;

	// free the node pointing to the temporary node
	free( to_free );

	return popped;

}

void delete( sll_node** curr_node ){

	if( *curr_node == NULL )
		return;

	// Recursively call the next node
	// Review: (*curr_node) de-references the pointer to pointer
	// (*curr_node)->next_node gets the pointer to next_node
	// &( (*curr_node)->next_node ) passes the address to next_node
	delete( &( (*curr_node)->next_node ) );

	free( *curr_node );

}


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

	fprintf( stdout, "Level Order Traversal  : " );
	sllist* queue = (sllist*)malloc(sizeof(sllist));
	queue->head_node = NULL;
	push_back(queue, int_bst->root);
	bst_node* curr = NULL;
	while(queue->head_node != NULL){
		if(queue->head_node->bst->left != NULL)
			push_back(queue, queue->head_node->bst->left);
		if(queue->head_node->bst->right != NULL)
			push_back(queue, queue->head_node->bst->right);
		curr = pop_front(queue);
		fprintf( stdout, "%d ", curr->value );
	}
	fprintf(stdout, "\n");


	// Call the destructor on the root
	destructor( int_bst->root );
	delete(&(queue->head_node));
	// Free the Binary Search Tree pointer
	free( int_bst );
	free(queue);

	return 0;

}
