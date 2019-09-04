//
// Created by William Campbell on 2019-09-04.
//

#include "MoveLeg.h"
#include "State.h"
#include<iostream>
using namespace std;

void MoveLeg::entry(void){
    cout << "entry() called";
}
void MoveLeg::during(void){
    cout << "durring() called";
}
/// HOW TO MAKE THIS FUNCTION RETURN THE NEXT STATES NAME...
/// enum of state names maybe??
void MoveLeg::exit(void) {
    cout << "exit() called";
//    int nextState = 2;
//    return nextState;

}