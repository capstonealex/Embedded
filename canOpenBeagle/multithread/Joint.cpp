//
// Created by William Campbell on 2019-07-24.
//

#include "Joint.h"


Joint::Joint(){
    //Default constructor - SHOULD THROW AN ERROR
    q = 0;
    id = 0;
}
Joint::Joint(float q_init, int ID){
    cout<<"Initializing joint WITH INPUTS \n";
    q = q_init;
    id = ID;
}
void Joint::setPos(float qd){
    q = qd;
    //Send off to CANDEV
}
void Joint::setId(int ID){
    id = ID;
}
int  Joint::getId()
{
    return id;
}
float Joint::getPos(){
    return q;
}
void Joint::printInfo(){
    cout<<"Joint id number "<<id<<" @ pos "<<q<<"\n";
}