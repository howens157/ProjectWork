/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: JK_Test.cpp
 * Date Created: 10/20/2021
 * File Contents: This program will test that JKFF works for PC06
 **********************************/
#include "../include/JKFF.h"
#include <fstream>

void read_and_test(std::ifstream& inputs){
    JKFF my_ff;
    bool CLK, J, K;
    while(!inputs.eof()){
        inputs >> CLK >> J >> K;
        my_ff.updateVals(CLK, J, K);
        std::cout << my_ff.getQ() << " " << my_ff.getQbar() << std::endl;
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

    read_and_test(inputs);

    inputs.close();
}
