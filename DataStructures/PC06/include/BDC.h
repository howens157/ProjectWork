/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: BDC.h
 * Date Created: 10/20/2021
 * File Contents: This file contains the class and struct declaration
                  for BDC in PC06
 **********************************/
#include "../include/JKFF.h"

#ifndef BDC_H
#define BDC_H

struct AND{
    bool A;
    bool B;

    AND();

    bool calc_and(bool A_in, bool B_in);
    bool get_and() const;
};

struct OR{
    bool A;
    bool B;

    OR();

    bool calc_or(bool A_in, bool B_in);
    bool get_or() const;
};

struct NOT{
    bool A;

    NOT();

    bool calc_not(bool A_in);
    bool get_not() const;
};

class BDC{
private:
    JKFF ff1;
    JKFF ff2;
    JKFF ff3;
    JKFF ff4;

    int get_value() const;

public:
    BDC();
    void count(bool clk, bool up_down);
    friend std::ostream& operator<<(std::ostream& output, const BDC& B);
};

#endif
