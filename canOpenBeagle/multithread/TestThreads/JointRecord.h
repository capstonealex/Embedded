//
// Created by William Campbell on 2019-07-31.
//

#ifndef CANOPENBEAGLE_JOINTRECORD_H
#define CANOPENBEAGLE_JOINTRECORD_H
#include<iostream>
#include<thread>
#include<vector>
#include <mutex>

class JointRecord {
    int id;
    float q;
    std::mutex jm;// joint records mutex, must be acquired to access its shared data e.g. q
public:
    JointRecord();
    float getPos();
    void setPos(float qd);
};


#endif //CANOPENBEAGLE_JOINTRECORD_H
