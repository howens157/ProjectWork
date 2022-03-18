/**********************************
 * Authors: Payton Lewandowski - plewando@nd.edu
            Hayden Owens - howens@nd.edu
            Thomas Knipe - tknipe@nd.edu
            Eduardo Yepiz - eyepiz@nd.edu
 * File Name: PrefixTreeNode.h
 * File Contents: This file contains a rough draft of our initial ideas for a
                  PrefixTree (Trie) class
 **********************************/
#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#include <vector>

struct prefixtree_node{
    char data;
    bool valid;
    std::vector<prefixtree_node*> children;

    prefixtree_node() : data('\0'), valid(false), children() {}
    prefixtree_node(char data_in, bool valid_in) : data(data_in), valid(valid_in), children() {}

};

class prefixtree{

    private:
        prefixtree_node* root;

        void delete_nodes(prefixtree_node* curr_node){
            if(curr_node->children.empty()){
                return;
            }

            for(long unsigned int i = 0; i < curr_node->children.size(); i++){
                delete_nodes(curr_node->children[i]);
            }

            delete curr_node->children;
            delete curr_node;
        }


    public:
        //default constructor
        prefixtree() : root(NULL) {}

        //destructor
        ~prefixtree(){
            delete_nodes(root);
        }

        //copy constructor
        prefixtree(const prefixtree& copy) : root(NULL)) {
            //to finish
        }

        prefixtree& operator=(const prefixtree& assign){
            //to finish
        }

        void insert(std::string new_data){
            for(long unsigned int iter = 0; iter < new_data.length(); iter++)
            {
                new_data[iter] = (char)std::tolower(new_data[iter]);
            }

            prefixtree_node* curr_node = root;
            for(int i = 0; i < new_data.size(); i++)
            {
                insert_letter(new_data[i], curr_node);
            }

            curr_node->valid = true;
        }

        void insert_letter(char new_letter, prefixtree_node*& curr_node){
            for(int i = 0; i < curr_node->children.size(); i++)
            {
                if(new_letter = curr_node->children[i])
                {
                    curr_node = curr_node->children[i];
                    return;
                }
            }

            prefixtree_node* new_child = new prefixtree_node(new_letter, false);
            curr_node->children.push_back(new_child);
            curr_node = new_child;
            return;
        }

        vector<std::string> suggestnext(prefixtree_node* curr_node){
            int numsuggestions = 3;
            prefixtree_node* next_node;
            vector<std::string> suggestions;

            for(int i = 0; i < numsuggestions; i++){
                suggestions.push_back("");

                //need to implement algorithm for searching for words

            }
            return suggestions;
        }

        bool contains(std::string target){
            prefixtree_node* curr_node = root;
            bool target_found = true;
            for(int i = 0; i < target.size(); i++)
            {
                for(int j = 0; j < curr_node->children.size(); j++)
                {
                    if(target[i] = curr_node->children[j])
                    {
                        curr_node = curr_node->children[j];
                        break;
                    }
                    elseif(j == curr_node->children.size() - 1)
                        target_found = false;
                }
            }
            return target_found;
        }

};

#endif
