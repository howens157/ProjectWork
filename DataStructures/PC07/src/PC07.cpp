/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: PC07.cpp
 * Date Created: 11/9/2021
 * File Contents: This program contains the main driver function for PC07
 **********************************/
#include "../inc/palindrome.h"

int main(const int argc, const char* argv[])
{
    if(argc != 2){
        std::cout << "Incorrect number of inputs" << std::endl;
        exit(-1);
    }
    std::string filename = argv[1];

    std::ifstream inputs;
    inputs.open(filename);

    if(!inputs.good()){
        std::cout << filename << " does not exist" << std::endl;
        exit(-1);
    }

    read_and_test(inputs);

    inputs.close();
}
