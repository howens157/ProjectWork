/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: max_prod_sub.cpp
 * Date Created: 10/12/2021
 * File Contents: This file contains the function definitions for Programming Challenge 05
 **********************************/
#include <vector>
#include <iostream>

#define COUT std::cout
#define ENDL std::endl
#define VECTOR std::vector

void printArray( VECTOR<int>& theArray ){

	COUT << "[";

	for(long unsigned int iter = 0; iter < theArray.size(); iter++){

		COUT << theArray.at(iter);

		if( iter < theArray.size() - 1 ){

			COUT << ",";
		}
	}

	COUT << "]";

}

int max_prod_sub( VECTOR<int>& theArray ) {

	// Your work goes here
    int globalMax = theArray.at(0);
    int currMax = theArray.at(0);

    for(unsigned int iter = 0; iter < theArray.size(); iter++){
        currMax = 1;
        for(unsigned int jter = iter; jter < theArray.size(); jter++){
            currMax *= theArray.at(jter);

            if(currMax > globalMax)
                globalMax = currMax;
        }
    }
    return globalMax;
}


int main( const int argc, const char* argv[] ){

	VECTOR<int> the_array;

	for( int iter = 1; iter < argc; ++iter ){

		int temp = atoi( argv[iter] );

		the_array.push_back( temp );

	}

	printArray(the_array);
	COUT << ENDL;
	COUT << "Max Product Subarray Solution = " << max_prod_sub(the_array) << ENDL;

	return EXIT_SUCCESS;
}
