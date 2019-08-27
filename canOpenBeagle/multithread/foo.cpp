//
// Created by William Campbell on 2019-08-27.
//

#include<iostream>
extern "C" {
#include "canFeast.c"
}
using namespace std;
class MYCLASS{
public:
    void callfunct(int x, int y){
        cout << "sum = "<< addnumbers(x,y) <<endl;
    }
};


int main(int argc, char *argv[]){
    MYCLASS mc;
    mc.callfunct(99,1);
    return 0;
}