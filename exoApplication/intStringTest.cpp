//
// Created by William Campbell on 2019-09-04.
//

#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <cstring>

int main ()
{
    int node = 10;
    std::string stringMessage = "[1] 100 read 0x6064 " + std::to_string(node) + " i32";
    //// Convert all to char arrays and send off as char messageSent
    std::cout << stringMessage <<"\n";
    char cstr[stringMessage.size() + 1];
    strcpy(cstr, stringMessage.c_str());
    std::cout << cstr <<"\n";
}