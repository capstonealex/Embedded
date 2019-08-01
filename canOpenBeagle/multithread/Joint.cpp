//
// Created by William Campbell on 2019-07-24.
//

#include "Joint.h"

Joint::Joint(){
    //Default constructor - SHOULD THROW AN ERROR
    q = 0;
    id = 0;
    // THESE MUST BE HARD SET AT OBJECT INITIALIZATION
    maxq = 360;
    minq =0;
}
Joint::Joint(float q_init, int ID){
    cout<<"Initializing joint WITH INPUTS \n";
    q = q_init;
    id = ID;
}
void Joint::applyPos(float q){
    // std::lock_guard <std::mutex> lockGuard(std::mutex);
    std::unique_lock lock(mutex_);
    //Safety checks.
    // Is joint where we think it is? or within safe range of it?
    // are we trying to move to a pos within the joints limits?
    if(q>minq && q<maxq) {
        qd = q;
        Joint::setPos(qd);
    }
    else{
        cout<<"Positions outside of joint limits"<<"\n";
    }
}
void Joint::setPos(float qd){
    q = qd;
    cout<<"Joint id: "<<id<<" Go to position: "<<q<<"\n";
    //Send off to CANDEV or DIRECTLY SEND OVER CANFEAST
}
void Joint::setId(int ID){
    id = ID;
}
int  Joint::getId()
{
    return id;
}
float Joint::getPos(){
    std::shared_lock lock(mutex_);
//    std::lock_guard <std::mutex> lockGuard(std::mutex);
    return q;
}
void Joint::printInfo(){
    cout<<"Joint id number "<<id<<" @ pos "<<q<<"\n";
}