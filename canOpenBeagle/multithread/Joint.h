//
// Created by William Campbell on 2019-07-30.
//

#ifndef CANOPENBEAGLE_JOINT_H
#define CANOPENBEAGLE_JOINT_H

#include<iostream>
using namespace std;

class Joint {
    //Private members
    int id;
    float q;
    //Will: Add other vars after initial test implimentation up and running
    // qd, qdd,T, mode. limts, Transformation, Reduction Ratio(CONST)
    // Candev* copley;// pointer to this joints asssiated candevice (COPLEY DRIVER)
public:
    Joint();
    Joint(float q_init, int ID);
    void setPos(float q);
    void setId(int ID);
    int getId();
    float getPos();
    void printInfo();
};


#endif //CAPSTONE_JOINT_H
