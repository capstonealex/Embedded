
////
//// Created by William Campbell on 2019-07-01.
//// ALEX EXOSKELETON MULTITHREAD ROBOTIC MAIN
////
#include "Robot.h"


int main() {
    // Initialize canOpenBBB node through canOpend, bind socket w/ parser callback.
    const int NUM_JOINTS = 4;
    ////    Initialize robot
    Robot X2;
    X2.printInfo();
    ////    initialize all joints to Current read position (STATE) or homing sequence?
    float position = 90.0;
    cout<<"----------Reading actual joint pos and internalizing----------\n";
    for (auto x=0;x< NUM_JOINTS;x++){
        X2.joints[x].setPos(position);
        position+=15.0;
    }
    X2.printInfo();
}