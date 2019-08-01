//
// Created by William Campbell on 2019-07-30.
// Derek bananas C++ Multithreading
//

// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <fstream>
using namespace std;


int main()
{
    ofstream myfile;
    myfile.open ("example.txt");
    std::thread first (foo,0);    // spawn new thread that calls foo()
    std::thread second (bar,0);  // spawn new thread that calls bar(0)
    std::cout << "main, foo and bar now execute concurrently...\n";

    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes

    std::cout << "foo and bar completed.\n";
    myfile << "Writing this to a file.\n";
    myfile.close();

    return 0;
}

