/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: sllist.c
 * Date Created: 9/21/2021
 * File Contents: This file contains the function definitions for Programming Challenge 03
 **********************************/
#include "../include/sllist.h"

void insert( sllist* the_list, int the_value ){
	sll_node* insert_node = (sll_node*)malloc( sizeof(sll_node) );

	insert_node->data = the_value;
	insert_node->next_node = NULL;

	if( the_list->head_node == NULL ){
		the_list->head_node = insert_node;
		return;
	}

	sll_node* curr_ptr = the_list->head_node;

	while( curr_ptr->next_node != NULL ){

		curr_ptr = curr_ptr->next_node;
	}

	curr_ptr->next_node = insert_node;
}

void print_list( sll_node* head_node ){
	sll_node* curr_ptr = head_node;
	while( curr_ptr != NULL ){
		fprintf( stdout, "%d %p\n", curr_ptr->data, curr_ptr);
		curr_ptr = curr_ptr->next_node;
	}
}

void destructor( sll_node* curr_ptr ){
	if( curr_ptr == NULL )
		return;

    destructor( curr_ptr->next_node );

	free( curr_ptr );
}

void reverse_func(sll_node** head_node){
	if((*head_node) == NULL)
    return;
  if((*head_node)->next_node == NULL)
    return;
  sll_node* prev_node = (*head_node);
  sll_node* curr_node = (*head_node)->next_node;
  reverse_recurs(head_node, prev_node, curr_node);
  prev_node->next_node = NULL;
  return;
}

void reverse_recurs(sll_node** head_node, sll_node*prev_node, sll_node* curr_node){
  if(curr_node->next_node == NULL){
    (*head_node) = curr_node;
    curr_node->next_node = prev_node;
    return;
  }
  reverse_recurs(head_node, curr_node, curr_node->next_node);
  curr_node->next_node = prev_node;
  return;
}

void delete_nth(sll_node** head_node, long unsigned int del_loc){
	if(*head_node == NULL || del_loc < 1)
		return;

	sll_node* curr = *head_node;
	long unsigned int iter, length;
	length = 1;
	while(curr->next_node != NULL){
		curr = curr->next_node;
		length++;
	}
	curr = *head_node;

	//case where del_loc is greater than length
	if(length < del_loc)
		return;

	//case where del_loc is equal to length
	if(length == del_loc){
		*head_node = (*head_node)->next_node;
		free(curr);
		return;
	}

	//case where del_loc is less than length
	sll_node* prev = NULL;
	for(iter = 0; iter < length-del_loc; ++iter){
		prev = curr;
		curr = curr->next_node;
	}
	prev->next_node = curr->next_node;
	free(curr);
	return;


}
