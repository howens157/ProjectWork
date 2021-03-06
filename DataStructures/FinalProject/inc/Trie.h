/**********************************
 * Authors: Payton Lewandowski - plewando@nd.edu
            Hayden Owens - howens@nd.edu
            Thomas Knipe - tknipe@nd.edu
            Eduardo Yepiz - eyepiz@nd.edu
			(Modified Version of Dr. Morrison's Trie.h)
 * File Name: Trie.h
 * File Contents: This file contains the class declaration and definition
 				  for the Trie class
 **********************************/

#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"

#define COUT std::cout
#define ENDL std::endl
#define STRING std::string
#define NUM_ASCII 128

class Trie{

	private:

		void addString( TrieNode* theNode, const std::string& word, unsigned int value ){

			// We haven't reach the end of the word
			if( value < word.size() ){

				// Add each character to the word
				// addChild will not permit duplicates
				theNode->addChild( word[value] );

				// Get the TrieNode correlating to the char
				TrieNode* nextLevel = theNode->getChildPtr( word[value] );

				// Recursively call the next level
				addString( nextLevel, word, value + 1);
			}

			// If we have reached the end of the word
			else if( value == word.size() ){

				// Add a star indicating this is a valid word
				theNode->addChild( '*' );
				return;
			}

		}


		void printTriePreOrder( TrieNode* theNode, unsigned int level ){

			// If we've reached the end, return
			if( theNode == NULL ){
				return;
			}

			// If we are at the root, just print the level
			if( theNode->getLetter() == 0 ){
				COUT << "root: " << level << ENDL;
			}

			else{
				// Print the letter and the level
				COUT << theNode->getLetter() << " " << level << "\t"; //ENDL;
			}

			// If we are at a star, we can return
			if( theNode->getLetter() == '*' ){
				return;
			}

			// Otherwise, recursively call
			for(unsigned int iter = 0; iter < NUM_ASCII; iter++){

				printTriePreOrder(theNode->getChildPtrOrder(iter), level + 1);

			}

		}

		bool contains( TrieNode* theNode, const std::string& word, unsigned int value ) const {

			// We haven't reach the end of the word
			if( value < word.size() ){

				if( theNode->getChildPtr( word.at(value) ) == NULL )
					return false;

				else
					// Recursively call using the child pointer
					return contains( theNode->getChildPtr( word.at(value) ), word, value+1 );
			}

			// If we have reached the end of the word
			else{ // if( value == word.size() ){

				// Add a star indicating this is a valid word
				if( theNode->getChildPtr( '*' ) == NULL )
					return false;

				return true;
			}

			return false;
		}

		// Private Member
		TrieNode* root;

	public:

		Trie() : root( new TrieNode() ) {}

		void addString( const std::string& word ){

			addString( root, word, 0 );

		}


		void printTriePreOrder( ){

			printTriePreOrder(root, 1);

		}


		bool contains( const std::string& word ) const{

			return contains( root, word, 0 );

		}

		std::string suggest(const std::string& prefix, const std::vector<float> letter_weights) {
			TrieNode* curr = root;
			std::string suggestion = "";
			for(unsigned int i = 0; i < prefix.length(); i++)
			{
				curr = curr->getChildPtr(prefix[i]);
				if(curr == NULL)
				{
					return("ERROR");
				}
				suggestion = suggestion + curr->getLetter();
			}

			float lowest_weight;
			char nextchild = 'a';
			while(1)
			{
				lowest_weight = 1000.0;
				if(curr->getChildPtr('*') != NULL)
				{
					break;
				}
				for(unsigned int childindex = (unsigned int)'a'; childindex <= (unsigned int)'z'; childindex++)
				{
					if(curr->getChildPtr((char)childindex) != NULL)
					{
						if(letter_weights[childindex - 97] < lowest_weight)
						{
							lowest_weight = letter_weights[childindex-97];
							nextchild = (char)childindex;
						}
					}
				}
				curr = curr->getChildPtr(nextchild);
				suggestion = suggestion + curr->getLetter();
			}

			return suggestion;
		}

};

#endif
