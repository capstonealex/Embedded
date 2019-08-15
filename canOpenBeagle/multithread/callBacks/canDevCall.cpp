// Created by William Campbell on 2019-08-01.
//

#include<iostream>

std::string canFeastGet(std::string commandMessage, std::string(* canDevUpdate)(std::string))
{
    // set up some dummy variables
    std::string success = "yea";

    // Do canFeast of ressource: poll (in loop) or single request for object dictionary value
    std::cout<<"Canfeast Request to network"<<"\n";
    // raw message parsing with canDev object dictionary
    //Implement after raw messaging works, should receive
        // q, qd or info requested
        // access internal hash table and use that value to send over canFeast or to perform getBeagle (XADRESS)

    // Call the callBack provided i.e. function pointer to jointUpdate
    success = canDevUpdate(commandMessage);
    return success;
}
//Implementation of canDevUpdate for individual devices
std::string jointUpdate(std::string data)
{
    std::string success = data;
    //Test of function
    std::cout<<"jointUpdate functioning with input from callBack: ";
    std::cout<<data << "\n";
    return success;
}


int main(){
    std::string msg = canFeastGet("WILL", &jointUpdate);
    std::cout << msg<<std::endl;
    return 0;
}