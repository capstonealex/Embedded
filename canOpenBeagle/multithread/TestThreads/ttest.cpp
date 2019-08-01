//
// Created by William Campbell on 2019-07-31.
//
//-------------- C++ Multithreading tutorial --------------

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>


//Return a random value no greater then the argument max
int GetRandom(int max){
    srand(time(NULL));
    return rand() % max;
}

void ExecuteThread(int id){
    // Print out Current time in ms
    auto nowTime = std::chrono::system_clock::now();
    std::time_t sleepTime =
            std::chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);
    std::cout <<"Thread "<< id <<
        " sleep time: " <<
        std::ctime(&sleepTime) << "\n";
    // Get separate pieces of right now time
    std::cout << "Month : " <<
              myLocalTime.tm_mon << "\n";
    std::cout << "Day : " <<
              myLocalTime.tm_mday << "\n";
    std::cout << "Year : " <<
              myLocalTime.tm_year + 1900 << "\n";
    std::cout << "Hours : " <<
              myLocalTime.tm_hour << "\n";
    std::cout << "Minutes : " <<
              myLocalTime.tm_min << "\n";
    std::cout << "Seconds : " <<
              myLocalTime.tm_sec << "\n\n";

    // Putting a thread to sleep
    // A thread is a block of code which executes.
    // We use multithrading to try and improve performance by running multiple at the same time.
    // Put the thread to sleep for up to 3 seconds
    std::this_thread::sleep_for (std::chrono::seconds(GetRandom(3)));
    // Get the time after the thread sleeps for a randome amount of time
    nowTime = std::chrono::system_clock::now();
    sleepTime =
            std::chrono::system_clock::to_time_t(nowTime);
    std::cout << "Thread " << id <<
              " Awake Time : " <<
              std::ctime(&sleepTime) << "\n";


}

// GetTime returns the time right now.
std::string GetTime(){
    auto nowTime = std::chrono::system_clock::now();
    std::time_t sleepTime =
            std::chrono::system_clock::to_time_t(nowTime);
    return std::ctime(&sleepTime);
}

//fake checking account balance
double acctBalance = 100;

// protect shared data from being accesed at the same time.
std::mutex acctLock;

void GetMoney(int id, double withdrawal){
    // exception safe way to block our balance from being accessed by more then 1 thread at a time.
    // restricts acces to the entire scope of this function once one thread tries to execute it.
    std::lock_guard<std::mutex> lock(acctLock);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << id <<
            " tries to withdrawl $" <<
            withdrawal << " on " <<
            GetTime() << "\n";
    if((acctBalance - withdrawal)>=0) {
        acctBalance -= withdrawal;
        std::cout << "New Account Balance is $" <<
                  acctBalance << "\n";
    }
    else {
        std::cout<< " Not enough cash in account for withdrawl";
        std::cout<< "Current balance is $" <<
                acctBalance << "\n";
    }
}

int main()
{
    /* simple multi thread executing back to back and sleeping
    std::thread th1 (ExecuteThread, 1);
    // join() - joins the thread to the main thread, the main thread waits for this thread to
    // finish executing before continuing executing code in main
    th1.join();
    std::thread th2 (ExecuteThread, 2);
    th2.join();
     */


    std::thread threads[10]; // create a thread pool
    for (int i=0 ; i<10; i++){
        threads[i] = std::thread(GetMoney, i, 15); // initiate each thread in pool, each tries to take out 15    $
    }
    for (int i=0 ; i<10; i++){
        threads[i].join();
    }
    return 0;
}