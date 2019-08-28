
////
//// Created by William Campbell on 2019-07-01.
//// ALEX EXOSKELETON MULTITHREAD ROBOTIC MAIN
////
//// For mutex locking functions we have in place use C++17 standard.
#include "../../exoApplication/Robot.h"
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
    std::thread criticalT (criticalThreadTest,ref(X2.joints[2]));
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
    X2.printInfo();
}
void criticalThreadTest(Joint& j){
    //Algorithm write thread and safety checks,
    float pos,currentpos;
    // continually wait for keyboard input and send as joint commands when typed.
    int n =0;
    while (n<10)
    {
        //cin is nonblocking and acts as arguments from control algorithm for testing
        std::cin>> pos;
        j.applyPos(pos);
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



