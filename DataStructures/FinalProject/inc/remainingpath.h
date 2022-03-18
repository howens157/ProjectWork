/**********************************
 * Authors: Payton Lewandowski - plewando@nd.edu
            Hayden Owens - howens@nd.edu
            Thomas Knipe - tknipe@nd.edu
            Eduardo Yepiz - eyepiz@nd.edu
 * File Name: remainingpath.h
 * File Contents: This file contains the declarations for remainingpath
                  which is a collection of functions to calulate the letter
                  weights to be used in our searching algorithm
 **********************************/
 /*
    Functions to use if searching for words is done by checking the smallest (current path length) + (expected remaining path length). You could also check once and then hard-code the results into another text file.

    Variables:
        letter_sums: vector of total distances between each instance of a letter and the end of the word
        letter_counts: vector of total number of instances of each letter

        total_length: total length of all words, to calculate average word length as a backup (if a letter/pair never occurs)
        word_count: total number of words, to calculate average word length

        letter_weights: vector of average distances from each letter to the end of the word
*/

#ifndef REMAININGPATH_H
#define REMAININGPATH_H

#include <string>
#include <vector>
#include <cctype>


// Converts characters to position in the vector (use for quickly finding a letter's position in the vectors)
unsigned int char_to_pos(const char input){
    unsigned int output;
    output = (unsigned int)input - 97;
    return output;
}


// Adds a word's weights to the vector (single letter version) (run once for every word)
void letter_weigh(std::vector<float> &letter_sums, std::vector<float> &letter_counts,
    long unsigned int &total_length, unsigned int &word_count, const std::string &word){

    // Increment total length and count
    total_length += word.length();
    word_count++;

    // Loop through words and increment values in arrays
    unsigned int iter;
    char letter;
    unsigned int letter_pos;
    for(iter = 0 ; iter < word.length() ; iter++){
        letter = word.at(iter);
		if(!std::islower(letter)) return; // End function when word is done
        letter_pos = char_to_pos(letter);
        letter_counts.at(letter_pos) += 1;
        letter_sums.at(letter_pos) += (float)(word.length() - (iter + 1));
    }

    return;
}


// Calculates average weights (single letter version) (run after all words are added)
void letter_weigh_finish(const std::vector<float> &letter_sums, const std::vector<float> &letter_counts,
    const long unsigned int total_length, const unsigned int word_count, std::vector<float> &letter_weights){

    unsigned int iter;
    for(iter = 0 ; iter < letter_weights.size() ; iter++){
        if(letter_counts.at(iter) != 0){
            letter_weights.at(iter) = letter_sums.at(iter)/letter_counts.at(iter);
        }else if(word_count != 0){ // If letter was never found, use average word length
            letter_weights.at(iter) = (float)(total_length)/(float)(word_count);
        }else{ // If no words were ever added, use 0
            letter_weights.at(iter) = 0;
        }
    }

    return;
}


#endif
