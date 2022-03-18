/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: BDC_Test.cpp
 * Date Created: 10/20/2021
 * File Contents: This program will test that BDC works for PC06
 **********************************/
#include "../include/BDC.h"
#include <fstream>

void read_and_count(std::ifstream& inputs, BDC& my_bdc){
    bool CLK, up_down;
    while(!inputs.eof()){
        inputs >> CLK >> up_down;
        my_bdc.count(CLK, up_down);
        std::cout << my_bdc << std::endl;
    }
}

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

    BDC my_bdc;
    std::cout << "Initial value in main: " << my_bdc << std::endl;
    read_and_count(inputs, my_bdc);
    std::cout << "Final value in main: " << my_bdc << std::endl;

    inputs.close();
}
