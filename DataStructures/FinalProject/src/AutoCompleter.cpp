/**********************************
 * Authors: Payton Lewandowski - plewando@nd.edu
            Hayden Owens - howens@nd.edu
            Thomas Knipe - tknipe@nd.edu
            Eduardo Yepiz - eyepiz@nd.edu
 * File Name: AutoCompleter.c
 * File Contents: This file contains the main driver function for our
 				  AutoCompleter program. It reads in a dictionary and caluclates
				  the letter weights. It then output a few example prefix
				  suggestions and then allows the user to enter their
				  own prefixes in order to get suggestions.
 **********************************/
#include <cstdlib>
#include "../inc/Trie.h" // also contains <fstream>, <iostream>, and <vector>
#include "../inc/remainingpath.h" // also contains <cctype>, <string>, and <vector>

void suggest_word(std::string prefix, std::vector<float> letter_weights, Trie dictionary)
{
	std::string suggestion = dictionary.suggest(prefix, letter_weights);
	if(suggestion == "ERROR")
	{
		std::cout << "No word found with " << prefix << std::endl;
	}
	else
	{
		std::cout << "Your suggestion for " << prefix << " is: " << suggestion << std::endl;
	}
}

int main(int argc, char* argv[]){ // argv[1] == 1000words.txt or Dictionary.txt

	// Check if number of inputs is valid, NOTE: change condition if using more command line args
	if(argc != 2){
		std::cout << "Incorrect number of inputs: please provide the text file you would like to use as a dictionary\n";
		exit(-1);
	}

	// Read input file name and create input stream
	std::ifstream dictIn(argv[1]);
	if(!dictIn.is_open()){
		std::cout << argv[1] << " does not exist\n";
		exit(-1);
	}

    // Create and fill weights info and trie
	std::string new_word;
	Trie dictionary;
	std::vector<float> letter_sums(26, 0);
	std::vector<float> letter_counts(26, 0);
	long unsigned int total_length;
	unsigned int word_count;

	while(!dictIn.eof()){
		dictIn >> new_word;
		for(unsigned int i = 0; i < new_word.length(); i++)
		{
			new_word[i] = (char)tolower(new_word[i]);
		}
        letter_weigh(letter_sums, letter_counts, total_length, word_count, new_word);
		dictionary.addString(new_word);
	}

	std::vector<float> letter_weights(26, 0);
	letter_weigh_finish(letter_sums, letter_counts, total_length, word_count, letter_weights);

	// Close input stream
	dictIn.close();

	// Do whatever else here
	std::cout << "LETTER WEIGHTS" << std::endl;
	for(unsigned int lter = (unsigned int) 'a' ; lter <= (unsigned int) 'z' ; lter++){
		std::cout << (char)toupper((char)lter) << ": " << letter_weights[lter - 97] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "TEST CASES" << std::endl;
	suggest_word("wha", letter_weights, dictionary);
	suggest_word("aard", letter_weights, dictionary);
	suggest_word("omni", letter_weights, dictionary);
	suggest_word("z", letter_weights, dictionary);
	suggest_word("range", letter_weights, dictionary);
	suggest_word("prob", letter_weights, dictionary);
	std::cout << std::endl;

	std::string userprefix;
	bool alphabetic = true;
	while(1)
	{
        alphabetic = true;
		std::cout << "Please enter a prefix or '*' to quit: ";
		std::cin >> userprefix;
		if(userprefix == "*")
			return 0;
		for(unsigned int i = 0; i < userprefix.length(); i++)
		{
			if(userprefix[i] < 'a' || userprefix[i] > 'z')
			{
				std::cout << "Please enter a lowercase alphabetic prefix." << std::endl;
				alphabetic = false;
				break;
			}
		}
		if(!alphabetic)
        {
            continue;
        }
		suggest_word(userprefix, letter_weights, dictionary);
	}

	return 0;
}
