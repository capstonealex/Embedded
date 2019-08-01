//
// Created by William Campbell on 2019-07-31.
//

#include "JointRecord.h"


JointRecord::JointRecord(){
    //Default constructor - SHOULD THROW AN ERROR
    q = 10;
    id = 0;
}

float JointRecord::getPos(){
    std::lock_guard <std::mutex> lockGuard(std::mutex);
    return q;
}

void JointRecord::setPos(float qd) {
    std::lock_guard <std::mutex> lockGuard(std::mutex);
// Constructor locks the mutex
    q =qd;
// If some exception occurs at this
// point then destructor of lockGuard
// will be called due to stack unwinding.
//

}