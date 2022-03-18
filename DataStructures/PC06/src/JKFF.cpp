/**********************************
 * Name: Hayden Owens
 * Email: howens@nd.edu
 * File Name: JKFF.cpp
 * Date Created: 10/20/2021
 * File Contents: This file contains the class method definitions for JKFF in PC06
 **********************************/
 #include "../include/JKFF.h"

 JKFF::JKFF() : Q(false), Qbar(true) {}

 void JKFF::updateVals(bool CLK, bool J_in, bool K_in){
     if(CLK){
         if(!J_in && K_in){
             Q = 0;
             Qbar = 1;
         }
         else if(J_in && !K_in){
             Q = 1;
             Qbar = 0;
         }
         else if(J_in && K_in){
             bool temp = Q;
             Q = Qbar;
             Qbar = temp;
         }
     }
 }

 bool JKFF::getQ() const{
     return Q;
 }

 bool JKFF::getQbar() const{
     return Qbar;
 }
