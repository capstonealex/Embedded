//
// Created by William Campbell on 2019-08-01.
//

#include<iostream>

std::string buildCompleteMessage(std::string rawData, std::string (* encrypterFunPtr)(std::string) )
{
    // Add some header and footer to data to make it complete message
    std::cout<<rawData<<"\n";
    rawData = "[HEADER]" + rawData + "[FooTER]";

    // Call the callBack provided i.e. function pointer to encrypt the
    rawData = encrypterFunPtr(rawData);
    return rawData;
}

//This encrypt function increment all letters in string by 1.
std::string encryptDataByLetterInc(std::string data)
{
    for(int i = 0; i < data.size(); i++)
    {
        if( (data[i] >= 'a' && data[i] <= 'z' ) || (data[i] >= 'A' && data[i] <= 'Z' ) )
            data[i]++;
    }
    return data;
}

//This encrypt function decrement all letters in string by 1.
std::string encryptDataByLetterDec(std::string data)
{
    for(int i = 0; i < data.size(); i++)
    {
        if( (data[i] >= 'a' && data[i] <= 'z' ) || (data[i] >= 'A' && data[i] <= 'Z' ) )
            data[i]--;
    }
    return data;
}

int main(){
    std::string msg = buildCompleteMessage("WILL", &encryptDataByLetterInc);
    std::cout << msg<<std::endl;
    std::string msg2 = buildCompleteMessage("SampleString", &encryptDataByLetterDec);
    std::cout<<msg2<<std::endl;
    return 0;
}