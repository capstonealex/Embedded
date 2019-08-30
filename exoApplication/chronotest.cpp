//
// Created by William Campbell on 2019-08-30.
//

// C++ program to find out execution time of
// of functions
#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

// For demonstration purpose, we will fill up
// a vector with random integers and then sort
// them using sort function. We fill record
// and print the time required by sort function
void add(int x, int y);
int main()
{

    // Generate Random values




    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    // Call the function, here sort()
    add(9,4);

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}

void add(int x, int y){
    cout << x+y;
}