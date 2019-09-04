//
// Created by William Campbell on 2019-07-30.
//

#ifndef CANOPENBEAGLE_JOINT_H
#define CANOPENBEAGLE_JOINT_H

//#include <mutex>  // For std::unique_lock
//#include <shared_mutex>
//#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

using namespace std;

class Joint {
    //Private members
    int id;
    float q, qd;
    float maxq, minq;
    void setPos(float qd);
    void canFeast(int *canSocket, char *command, char *canReturnMessage);
//    mutable std::shared_mutex mutex_;
    //Will: Add other vars after initial test implimentation up and running
    // qd, qdd,T, mode. limts, Transformation, Reduction Ratio(CONST)

public:
//    CanDevice copley;// pointer to this joints candevice, the motor driver (COPLEY DRIVER)
    Joint();
    Joint(float q_init, int ID);
    void setId(int ID);
    int getId();
    void applyPos(float q);
    string getPos(int *canSocket);
    void printInfo();
    //callback functions for this devices canDevice object
    void posCallBack(float qReal); // Mainatain real world position in joint object
};


#endif //CAPSTONE_JOINT_H