//
// Created by William Campbell on 2019-07-24.
//

# include "Joint.h"
# include <stdlib.h>
# include <string>
const int STRING_LENGTH =50;
Joint::Joint(){
    //Default constructor - SHOULD THROW AN ERROR
    q = 0;
    id = 0;
    // THESE MUST BE HARD SET AT OBJECT INITIALIZATION
    maxq = 360;
    minq =0;
}
Joint::Joint(float q_init, int ID){
    cout<<"Initializing joint WITH INPUTS \n";
    q = q_init;
    id = ID;
}
void Joint::applyPos(float qd){
    //Safety checks.
    // Is joint where we think it is? or within safe range of it?
    // are we trying to move to a pos within the joints limits?
    ///// Testing for PDOs

    if(q>minq && q<maxq) {
        qd = q;
        Joint::setPos(qd);
    }
    else{
        cout<<"Positions outside of joint limits"<<"\n";
    }
}
void Joint::setPos(float qd){
    q = qd;
    cout<<"Joint id: "<<id<<" Go to position: "<<q<<"\n";
    //Send off to CANDEV or DIRECTLY SEND OVER CANFEAST
}
void Joint::setId(int ID){
    id = ID;
}
int  Joint::getId()
{
    return id;
}
string Joint::getPos(int *canSocket){
    char getpos[STRING_LENGTH];
    char messageSent[]= "[1] 100 read 0x1017 0 i16";
    canFeast(canSocket, messageSent, getpos);
    std::string pos(getpos);
    return pos;

}
string Joint::posTest(int *canSocket){
    char getpos[STRING_LENGTH];
    char messageSent[]= "[1] 100 read 0x6063 1 i32";

    canFeast(canSocket, messageSent, getpos);
    std::string pos(getpos);
    return pos;

}
string Joint::multiPosTestT(int *canSocket){
    char getpos[STRING_LENGTH];
    std::string message = "[1] 100 read 0x6064 " + std::to_string(this->id) + " i32";
    //// Convert all to char arrays and send off as char messageSent
    char messageSent[message.size() + 1];
    strcpy(messageSent, message.c_str());
    canFeast(canSocket, messageSent, getpos);
    std::string pos(getpos);
    return pos;

}
void Joint::printInfo(){
    cout<<"Joint id number "<<id<<" @ pos "<<q<<"\n";
}
void Joint::posCallBack(float qReal){
    q = qReal;
}
void Joint::canFeast(int *canSocket, char *command, char *canReturnMessage)
{
    int commandLength = strlen(command);
    int n;
    char buf[100000];

    if (write(*canSocket, command, commandLength) != commandLength)
    {
        perror("Socket write failed");
        exit(EXIT_FAILURE);
    }

    n = read(*canSocket, buf, sizeof(buf));
    if (n == -1)
    {
        perror("Socket read failed");
        close(*canSocket);
        exit(EXIT_FAILURE);
    }
    //printf("%s", buf);
    strcpy(canReturnMessage, buf);
}
