//
// Created by William Campbell on 2019-07-30.
//

#ifndef CANOPENBEAGLE_JOINT_H
#define CANOPENBEAGLE_JOINT_H

#include<iostream>
#include <mutex>  // For std::unique_lock
#include <shared_mutex>
#include <thread>
using namespace std;

class Joint {
    //Private members
    int id;
    float q, qd;
    float maxq, minq;
    void setPos(float qd);
    mutable std::shared_mutex mutex_;
    //Will: Add other vars after initial test implimentation up and running
    // qd, qdd,T, mode. limts, Transformation, Reduction Ratio(CONST)
    // Candev* copley;// pointer to this joints asssiated candevice (COPLEY DRIVER)
public:
    Joint();
    Joint(float q_init, int ID);
    void setId(int ID);
    int getId();
    void applyPos(float q);
    float getPos();
    void printInfo();
};


#endif //CAPSTONE_JOINT_H
