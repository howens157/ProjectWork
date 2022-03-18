/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: bst.c
 * Date Created: 9/29/2021
 * File Contents: This file contains the function definitions for Programming Challenge 04
 **********************************/
 #include "../include/bst.h"

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


void in_order_traversal( bst_node* curr_node ){

	if( curr_node == NULL )
		return;

	in_order_traversal( curr_node->left );

	fprintf( stdout, "%d ", curr_node->value );

	in_order_traversal( curr_node->right );

}


void pre_order_traversal( bst_node* curr_node ){

	if( curr_node == NULL )
		return;

	fprintf( stdout, "%d ", curr_node->value );

	pre_order_traversal( curr_node->left );

	pre_order_traversal( curr_node->right );

}


void post_order_traversal( bst_node* curr_node ){

	if( curr_node == NULL )
		return;

	post_order_traversal( curr_node->left );

	post_order_traversal( curr_node->right );

	fprintf( stdout, "%d ", curr_node->value );

}

void destructor( bst_node* curr_node ){

	if( curr_node == NULL )
		return;

	destructor( curr_node->left );

	destructor( curr_node->right );

	free( curr_node );

}

void find_kth_element( bst_node* curr_node, int kth, int* curr_val, int* solution ){

	if( curr_node == NULL )
		return;

	// Traverse Right
	find_kth_element( curr_node->right, kth, curr_val, solution );

	// At this current node, increment curr_val
	++(*curr_val);

	// If kth equals curr_val, then set the solution to the node's value
	if( kth == *curr_val )
		*solution = curr_node->value;

	// Traverse Left
	find_kth_element( curr_node->left, kth, curr_val, solution  );

}

long unsigned int maximum_depth( bst_node* curr_node, long unsigned int currdepth, long unsigned int* maxdepth ){

	if( curr_node == NULL )
		return 0;
	// Rest of logic goes here
	if(currdepth > *maxdepth)
		*maxdepth = currdepth;
	maximum_depth(curr_node->left, currdepth+1, maxdepth);
	maximum_depth(curr_node->right, currdepth+1, maxdepth);


	return *maxdepth;

}


void reverse_tree( bst_node** curr_node ){

	if( *curr_node == NULL )
		return;

	// Rest of logic goes here
	reverse_tree(&((*curr_node)->left));
	bst_node* temp = (*curr_node)->right;
	(*curr_node)->right = (*curr_node)->left;
	(*curr_node)->left = temp;
	reverse_tree(&((*curr_node)->left));
}
