//
// Created by William Campbell on 2019-07-30.
//

#ifndef CANOPENBEAGLE_ROBOT_H
#define CANOPENBEAGLE_ROBOT_H
#include "Joint.h"


class Robot {
private:
    enum{ NUM_JOINTS = 4};

public:
    Robot();
    Joint joints[NUM_JOINTS];
    void printInfo();
    //For sending socket commands
    void canFeastUp(int *canSocket);
    void canFeast(int *canSocket, char *command, char *canReturnMessage);
    void canFeastDown(int *canSocket);
//    void canFeastErrorHandler(int *canSocket, char *command, char *canReturnMessage);

    // CanDevice** canDev[]l;
    //canFeasat constants
    const int BUF_SIZE =100000;
    const int STRING_LENGTH =50;
    const int MAX_RECONNECTS =10;
    const int DECIMAL =10;
    // Exo user buttons
    const int BUTTON_ONE =1;
    const int BUTTON_TWO =2;
    const int BUTTON_THREE= 3;
    const int BUTTON_FOUR =4;
    //Node ID for the 4 joints
    const int LHIP =1;
    const int LKNEE=2;
    const int RHIP =3;
    const int RKNEE= 4;


};


#endif //CAPSTONE_ROBOT_H
