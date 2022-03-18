/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: palindrome.cpp
 * Date Created: 11/9/2021
 * File Contents: This file contains the function definitions for PC07
 **********************************/
#include "../inc/palindrome.h"

void read_and_test(std::ifstream& inputs){
    std::string currphrase;
    while(1){
        inputs >> currphrase;
        if(!inputs.eof())
            if(is_palindrome(currphrase))
                std::cout << "\"" << currphrase << "\"" << " is a palindrome permutation" << std::endl;
            else
                std::cout << "\"" << currphrase << "\"" << " is not a palindrome permutation" << std::endl;
        else
            break;
    }
}

bool is_palindrome(std::string currphrase){
    std::unordered_map<char, int> occurrences;
    int numodds = 0;
    for(long unsigned int iter = 0; iter < currphrase.length(); iter++)
    {
        currphrase[iter] = (char)std::tolower(currphrase[iter]);
        if(occurrences.find(currphrase[iter]) == occurrences.end())
            occurrences[currphrase[iter]] = 1;
        else
            occurrences[currphrase[iter]] += 1;
        if(occurrences[currphrase[iter]]%2 == 1)
            numodds++;
        else
            numodds--;
    }
    if(numodds == 1 || numodds == 0)
        return true;
    else
        return false;
}
