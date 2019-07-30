//
// Created by William Campbell on 2019-07-23.
//

#include "Robot.h"

Robot::Robot(){
    cout<<"Setting Robot joint initial conditions...\n";
    // Set joint Intial positions.
    joints[0].setPos(30);
    joints[1].setPos(60);
    joints[2].setPos(30);
    joints[3].setPos(60);
    // Set joint IDs
    joints[0].setId(1);
    joints[1].setId(2);
    joints[2].setId(3);
    joints[3].setId(4);
};
void Robot::printInfo() {
    cout<<"This is an X2 robot with: \n";
    for ( auto x:joints) {
        x.printInfo();
    }
}

