/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: sllist.h
 * Date Created: 9/21/2021
 * File Contents: This file contains the function declarations for Programming Challenge 03
 **********************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node{
	int data;
	struct sll_node* next_node;
}sll_node;

typedef struct sllist{
	struct sll_node* head_node;
}sllist;

void insert( sllist* the_list, int the_value );
void print_list( sll_node* head_node );
void destructor( sll_node* curr_ptr );
void reverse_func(sll_node** head_node);
void reverse_recurs(sll_node** head_node, sll_node* prev_node, sll_node* curr_node);
void delete_nth(sll_node** head_node, long unsigned int del_loc);
