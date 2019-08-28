///
//// Created by William Campbell on 2019-07-01.
//// ALEX EXOSKELETON MULTITHREAD ROBOTIC MAIN
////
//// For mutex locking functions we have in place use C++17 standard.
#include "Robot.h"
#include "Joint.h"
/* Helper functions */
void initexo(Robot& robot);
const int NUM_JOINTS = 4;
int main() {
    Robot X2;
    initexo(X2);
    X2.printInfo();
    //Start sockets with canopend
    int socket;
    //Used to store the canReturnMessage. Not used currently, hence called junk.
    //Should pass this to calling function for possible error handling.
    std::string messageSent = "[1] 4 read 0x1017 0 i16";
    std::string messageRecieved;
    X2.canFeastUp(&socket);
    int n = 0;
    while(n<100) {
        X2.canFeast(&socket, messageSent, messageRecieved);
        n++;
    }
    cout<< messageRecieved;
    X2.canFeastDown(&socket);

    return 0;
}


void initexo(Robot& X2){
    // Initialize canOpenBBB node through canOpend, bind socket w/ parser callback.
//    const int NUM_JOINTS = 4;
    ////    Initialize robot
/*   X2.printInfo();*/
    ////    initialize all joints to Current read position (STATE) or homing sequence?
    float position = 90.0;
    cout<<"----------Reading actual joint pos and internalizing----------\n";
    for (auto x=0;x< NUM_JOINTS;x++){
        X2.joints[x].applyPos(position);
        position+=15.0;
    }
}
