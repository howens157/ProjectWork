/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: BDC.cpp
 * Date Created: 10/20/2021
 * File Contents: This file contains the struct and class method
                  definitions for BDC in PC06
 **********************************/
#include "../include/BDC.h"

//AND struct
AND::AND() : A(false), B(false) {}

bool AND::calc_and(bool A_in, bool B_in){
    A = A_in;
    B = B_in;
    if(A && B)
        return true;
    else
        return false;
}

bool AND::get_and() const{
    if(A && B)
        return true;
    else
        return false;
}

//OR struct
OR::OR() : A(false), B(false) {}

bool OR::calc_or(bool A_in, bool B_in){
    A = A_in;
    B = B_in;
    if(A || B)
        return true;
    else
        return false;
}

bool OR::get_or() const{
    if(A || B)
        return true;
    else
        return false;
}

//NOT struct
NOT::NOT() : A(false) {}

bool NOT::calc_not(bool A_in){
    A = A_in;
    return !A;
}

bool NOT::get_not() const{
    return !A;
}

//BDC class
BDC::BDC() : ff1(JKFF()), ff2(JKFF()), ff3(JKFF()), ff4(JKFF()) {}

void BDC::count(bool clk, bool up_down){
    ff1.updateVals(clk, 1, 1);

    NOT not_0;
    not_0.calc_not(up_down);

    AND and_0;
    and_0.calc_and(not_0.get_not(), ff1.getQbar());

    AND and_1;
    and_1.calc_and(up_down, ff1.getQ());

    OR or_0;
    or_0.calc_or(and_0.get_and(), and_1.get_and());

    ff2.updateVals(clk, or_0.get_or(), or_0.get_or());

    AND and_2;
    and_2.calc_and(and_0.get_and(), ff2.getQbar());

    AND and_3;
    and_3.calc_and(and_1.get_and(), ff2.getQ());

    OR or_1;
    or_1.calc_or(and_2.get_and(), and_3.get_and());

    ff3.updateVals(clk, or_1.get_or(), or_1.get_or());

    AND and_4;
    and_4.calc_and(and_2.get_and(), ff3.getQbar());

    AND and_5;
    and_5.calc_and(and_3.get_and(), ff3.getQ());

    OR or_2;
    or_2.calc_or(and_4.get_and(), and_5.get_and());

    ff4.updateVals(clk, or_2.get_or(), or_2.get_or());
}

int BDC::get_value() const{
    return 8*ff4.getQ() + 4*ff3.getQ() + 2*ff2.getQ() + ff1.getQ();
}

std::ostream& operator<<(std::ostream& output, const BDC& B){
    output << B.ff4.getQ() << ' ';
    output << B.ff3.getQ() << ' ';
    output << B.ff2.getQ() << ' ';
    output << B.ff1.getQ() << ' ';
    output << B.get_value();
    return output;
}
