///
//// Created by William Campbell on 2019-07-01.
//// ALEX EXOSKELETON MULTITHREAD ROBOTIC MAIN
////
#include "Robot.h"
#include "Joint.h"
#include <chrono>
using namespace std::chrono;
/* Helper functions */
void initexo(Robot& robot);
const int NUM_JOINTS = 4;
const int STRING_LENGTH =50;
int main() {
    Robot X2;
    initexo(X2);
    X2.printInfo();
    //Start sockets with canopend
    int socket;
    //Used to store the canReturnMessage. Not used currently, hence called junk.
    //Should pass this to calling function for possible error handling.
    char messageRecieved[STRING_LENGTH];
    char messageSent[STRING_LENGTH]= "[1] 100 read 0x1017 0 i16";
    char junk[STRING_LENGTH];
    //Used to check if button is pressed.
    int button1Status = 0;
    int button2Status = 0;
    int button3Status = 0;
    X2.canFeastUp(&socket);
    while(true) {
        auto start = high_resolution_clock::now();
        X2.canFeast(&socket, messageSent, messageRecieved);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by LOCAL SDO: "
             << duration.count() << " microseconds" << endl;
//        cout<< (char *)messageRecieved;
        //read all 4 button states
        start = high_resolution_clock::now();
        button1Status = getButton(&socket, BUTTON_ONE, junk);
//        button2Status = getButton(&socket, BUTTON_TWO, junk);
//        button3Status = getButton(&socket, BUTTON_THREE, junk);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by : Button poll"
             << duration.count() << " microseconds" << endl;
        // pause until keyboard is hit
        std::cin.ignore();
    }
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
