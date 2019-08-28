//
// Created by William Campbell on 2019-08-01.
//

#include "CanDevice.h"

// canFeastSend sends a
//std::string CanDevice::canFeastGet(std::string commandMessage, std::string(* canDevUpdate)(std::string)){
//    // set up some dummy variables
//    std::string success = "yea thats a rodger ";
//    // Do canFeast of ressource: poll (in loop) or single request for object dictionary value
//    std::cout<<"Canfeast Request to network"<<"\n";
//    // raw message parsing with canDev object dictionary
//    //Implement after raw messaging works, should receive
//    // q, qd or info requested
//    // access internal hash table and use that value to send over canFeast or to perform getBeagle (XADRESS)
//
//    // Call the callBack provided i.e. function pointer to jointUpdate
//    success = canDevUpdate(commandMessage);
//    return success;
//}
//
//// Implementation of canDevUpdate for individual devices
//std::string CanDevice::jointUpdate(std::string data)
//{
//    std::string success = data;
//    //Test of function
//    std::cout<<"jointUpdate functioning with input from callBack: ";
//    std::cout<<data << "\n";
//    return success;
//}
//// set and get OD commands should take in the NAME (hardcoded) of the obj dictionary specific function
//// USE the function createCanMessage(std::string specific_command) to take that command and turn it into a true blue string with all requirments
//// IT also adds the node ID, since this function is local to each canDev and its own nodeID
//// createCanMessage(std::string specific_command) uses the candevices object dictionary map and other params to construct the correct message given a obj dic functional name
//// This message is then sent to canFeast over the can line to the correct node to either request an OD entry or change it.
//void CanDevice::setOD(std::string objectAddress){
//    std::string msg = canFeastGet(objectAddress, &jointUpdate);
//    std::cout << msg<<std::endl;
//}
//void CanDevice::getOD(std::string objectAddress){
//    std::string msg = CanDevice::canFeastGet(objectAddress, &jointUpdate);
//    std::cout << msg<<std::endl;
//}
//// Testing OG Callback code with canDev
std::string canFeastGet(std::string commandMessage, std::string(* canDevUpdate)(std::string) )
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

