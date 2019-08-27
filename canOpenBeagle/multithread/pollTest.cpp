//
// Created by William Campbell on 2019-08-21.
// Test of multithread SDO polling of canopend node reppresentation of beagle bone black on PDO enabled network
// for position of canFeast for all 4 robot joints
// Callback of response to robot joint objects
//

#include "Robot.h"
#include <thread>         // std::thread
#include <fstream>      // fstream to write read values to

#include<iostream>
extern "C" {
#include "canFeast.c"
}

/* Robot object functions */
void initexo(Robot& robot);
/* Thread functions */
void criticalThreadTest(Joint& joint);
int dummyApplyPos(int q);
void testReadThread(Robot& X2, int counts);
void readThread(Robot& X2, int counts);
const int NUM_JOINTS = 4;
int main() {
    Robot X2;
    initexo(X2);
    int readCounts = 1000;
    cout<<"Input the positions to send to joints 1 to 4"<<"\n";
    std::thread readT (readThread,std::ref(X2), readCounts);
    std::thread criticalT (criticalThreadTest,std::ref(X2));
    std::cout << "main, critical and read thread now execute concurrently...\n";

    readT.join();                // pauses until first finishes
    criticalT.join();            // pauses until second finishes

    std::cout << "Critical and read threads completed.\n";
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
        std::cout<<"Press keyboard for current joint positions.";
        //cin is nonblocking and acts as arguments from control algorithm for testing
        std::cin>> junk;
        X2.printInfo();
        n++;
    }
}
/// Polling thread -> this thread polls the network for each joints position via SDO messaging.
//// V1. SDO direct messaging to each node (each joint) and manually change each joints position
//// status: development
//// V2. SDO direct meassging with call backs from within a candevice (GENERAL FORM) callback to joint which created it.
//// status: on hold
//// V3. SDO messaging to access BBB object dictionary
//// status: on hold
//// V4. If V3 is too slow, direct access BBB object dictionary
//// status: on hold
void readThread(Robot& X2, int counts){
    std::cout<<"----------READING THREAD BEGIN-------------"<<"\n";
    ofstream myfile;
    myfile.open ("output.txt");
    int n = 0;
    float qRead;
    //// Open canFeast Socket to canopend
    // Set up socket to canOpend
    int socket;
    canFeastUp(&socket);
    //Used to store the canReturnMessage. Not used currently, hence called junk.
    //Should pass this to calling function for possible error handling.
    char junk[STRING_LENGTH];

    while(n<counts) {
        myfile << "\n" << "Sample "  << n << ": ";
        for (auto i = 0; i < 4; i++) {
            //// Canfeast each joints position and put into X2 objects joints using posCallBack(qRead)
            // joint addresses
            // LHIP 1
            // LKNEE 2
            // RHIP 3
            // RKNEE 4
            //// i+1 is joint address
            qRead = getPos(&socket, i+1 , junk);
            X2.joints[i].posCallBack(qRead); /// update that joint with its read position
//            std::cout << X2.joints[i].getPos() << "\n";
//            myfile << X2.joints[i].getPos() << "    " ;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        n++;
    }
    canFeastDown(&socket);
//    myfile.close();
    //// Close canFeast socket to canopend
}

/// Test thread for reading virtual X2 positions for testing multithreading
//// Status: functioning
void testReadThread(Robot& X2, int counts){
    std::cout<<"----------READING THREAD BEGIN-------------"<<"\n";
    // file output of read in values
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

