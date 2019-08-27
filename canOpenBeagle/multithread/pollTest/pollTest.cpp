//
// Created by William Campbell on 2019-08-21.
// Test of multithread SDO polling for position of canFeast for all 4 robot joints
// Callback of response to robot joint objects
//

#include "Robot.h"
#include <thread>         // std::thread
#include <fstream>      // fstream to write read values to
/* Helper functions */
void initexo(Robot& robot);
void criticalThreadTest(Joint& joint);
int dummyApplyPos(int q);
void readThread(Robot& X2, int counts);
const int NUM_JOINTS = 4;
int main() {
    Robot X2;
    initexo(X2);
    int readCounts = 100;
    cout<<"Input the positions to send to joints 1 to 4"<<"\n";
    std::thread readT (readThread,ref(X2), readCounts);
    std::thread criticalT (criticalThreadTest,ref(X2));
    std::cout << "main, critical and read thread now execute concurrently...\n";

    readT.join();                // pauses until first finishes
    criticalT.join();            // pauses until second finishes

    std::cout << "Critical and read threads completed.\n";
    /*
    readThreadTest(X2);
    criticalThreadTest(X2.joints[2]);
     */
    X2.printInfo();
    return 0;
}


void initexo(Robot& X2){
    // Initialize canOpenBBB node through canOpend, bind socket w/ parser callback.
    ////    Initialize robot
    ////    initialize all joints to Current read position (STATE) or homing sequence?
    float position = 90.0;
    cout<<"----------Reading actual joint pos and internalizing----------\n";
    for (auto x=0;x< NUM_JOINTS;x++){
        X2.joints[x].applyPos(position);
        position+=15.0;
    }
    X2.printInfo();
}
void criticalThreadTest(Robot& X2){
    //Algorithm write thread and safety checks,
    float junk,currentpos;
    // continually wait for keyboard input and send as joint commands when typed.
    int n =0;
    while (n<10)
    {
        std::cout<<"Press keyboard for current joint positions."
        //cin is nonblocking and acts as arguments from control algorithm for testing
        std::cin>> junk;
        X2.printInfo();
        n++;
    }
}
void readThread(Robot& X2, int counts){
    std::cout<<"----------READING THREAD BEGIN-------------"<<"\n";
    // file output for read testing
    ofstream myfile;
    myfile.open ("output.txt");
    int n = 0;
    while(n<counts) {
        myfile << "\n" << "Sample "  << n << ": ";
        for (auto i = 0; i < 4; i++) {
//            std::cout << X2.joints[i].getPos() << "\n";
            myfile << X2.joints[i].getPos() << "    " ;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        n++;
    }
    myfile.close();
}



