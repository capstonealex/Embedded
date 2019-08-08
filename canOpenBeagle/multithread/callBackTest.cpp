//
// Created by William Campbell on 2019-08-08.
//

#include "CanDevice.h"


int main(){
    CanDevice testDev;
    std::string test = testDev.position;
    std::cout<< test;
//    std::string msg = canFeastGet("WILL", &jointUpdate);
//    std::cout << msg<<std::endl;
    return 0;
}