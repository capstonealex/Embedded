//
// Created by William Campbell on 2019-07-31.
//

#include "JointRecord.h"
#include <chrono>
#include <thread>


void read_task(JointRecord& o, int counts) {
    std::cout<<"----------READING THREAD BEGIN-------------"<<"\n";
    int x = 0;
    while(x< counts) {
        float x = o.getPos();
        std::cout << "CURRNET POS: " << x << "\n";
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }

}
void write_task(JointRecord& o, int counts) {
    std::cout<<"----------Writing THREAD BEGIN-------------"<<"\n";
    int x = 0;
    while(x< counts) {
        float x = o.getPos();
        o.setPos(x+50);
        std::this_thread::sleep_for (std::chrono::milliseconds(50));
    }
}


int main()
{
    // ----------  shared object thread access -----------
    JointRecord b;
    std::cout <<"Initial joint positions: " << b.getPos() <<"\n";
    int counts = 100;
    std::thread t1(read_task, std::ref(b), counts);
    std::thread t2(write_task, std::ref(b), counts);
    t1.join();
    t2.join();

    return 0;



}