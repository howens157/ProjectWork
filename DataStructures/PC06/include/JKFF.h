/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: JKFF.h
 * Date Created: 10/20/2021
 * File Contents: This file contains the class declaration for JKFF in PC06
 **********************************/
#ifndef JKFF_H
#define JKFF_H

#include <iostream>

class JKFF{
private:
    bool Q;
    bool Qbar;

public:
    JKFF();

    void updateVals(bool CLK, bool J_in, bool K_in);

    bool getQ() const;
    bool getQbar() const;

};

#endif
