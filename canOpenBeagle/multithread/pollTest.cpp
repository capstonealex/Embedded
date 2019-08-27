//
// Created by William Campbell on 2019-08-21.
// Test of multithread SDO polling of canopend node reppresentation of beagle bone black on PDO enabled network
// for position of canFeast for all 4 robot joints
// Callback of response to robot joint objects
//

#include "Robot.h"
#include <thread>         // std::thread
#include <fstream>      // fstream to write read values to

// C libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>

//Node ID for the 4 joints
#define LHIP 1
#define LKNEE 2
#define RHIP 3
#define RKNEE 4
#define BUF_SIZE 100000
//String Length for defining fixed sized char array
#define STRING_LENGTH 50
#define MAX_RECONNECTS 10
//Base for int to str conversion
#define DECIMAL 10
// move all these functions out and only call the one you need.
/* canFeast and socket functions */
// Sending SDO messages over sockets to canopend
void canFeastUp(int *canSocket);
void canFeast(int *canSocket, char *command, char *canReturnMessage);
void canFeastDown(int *canSocket);
//Reads position of specified node
long getPos(int *canSocket, int nodeid, char *canReturnMessage);
/* Message parsing functions */
//Converts integer to string
void itoa(int value, char *str, int base);
//Reverses a string. Used by itoa()
void strreverse(char *begin, char *end);
//Extracts string a specified pos and stores it in extractStr
void stringExtract(char *origStr, char **extractStr, int pos);
//Converts strings to integer and returns it.
long strToInt(char str[]);
/* Robot object functions */
void initexo(Robot& robot);
/* Thread functions */
void criticalThreadTest(Joint& joint);
int dummyApplyPos(int q);
void testReadThread(Robot& X2, int counts);
void readThread(Robot& X2, int counts);
const int NUM_JOINTS = 4;
int main() {
    Robot X2;
    initexo(X2);
    int readCounts = 1000;
    cout<<"Input the positions to send to joints 1 to 4"<<"\n";
    std::thread readT (readThread,ref(X2), readCounts);
    std::thread criticalT (criticalThreadTest,ref(X2));
    std::cout << "main, critical and read thread now execute concurrently...\n";

    readT.join();                // pauses until first finishes
    criticalT.join();            // pauses until second finishes

    std::cout << "Critical and read threads completed.\n";
    X2.printInfo();
    return 0;
}


void initexo(Robot& X2){
    // Initialize canOpenBBB node through canOpend, bind socket w/ parser callback.
    ////    Initialize robot
    ////    initialize all joints to Current read position (STATE) or homing sequence?
    float position = 90.0;
    cout<<"----------Reading actual joint pos and internalizing----------\n";
    for (auto x=0;x< NUM_JOINTS;x++){
        X2.joints[x].applyPos(position);
        position+=15.0;
    }
    X2.printInfo();
}
void criticalThreadTest(Robot& X2){
    //Algorithm write thread and safety checks,
    float junk,currentpos;
    // continually wait for keyboard input and send as joint commands when typed.
    int n =0;
    while (n<10)
    {
        std::cout<<"Press keyboard for current joint positions.";
        //cin is nonblocking and acts as arguments from control algorithm for testing
        std::cin>> junk;
        X2.printInfo();
        n++;
    }
}
/// Polling thread -> this thread polls the network for each joints position via SDO messaging.
//// V1. SDO direct messaging to each node (each joint) and manually change each joints position
//// status: development
//// V2. SDO direct meassging with call backs from within a candevice (GENERAL FORM) callback to joint which created it.
//// status: on hold
//// V3. SDO messaging to access BBB object dictionary
//// status: on hold
//// V4. If V3 is too slow, direct access BBB object dictionary
//// status: on hold
void readThread(Robot& X2, int counts){
    std::cout<<"----------READING THREAD BEGIN-------------"<<"\n";
    ofstream myfile;
    myfile.open ("output.txt");
    int n = 0;
    float qRead;
    //// Open canFeast Socket to canopend
    // Set up socket to canOpend
    int socket;
    canFeastUp(&socket);
    //Used to store the canReturnMessage. Not used currently, hence called junk.
    //Should pass this to calling function for possible error handling.
    char junk[STRING_LENGTH];

    while(n<counts) {
        myfile << "\n" << "Sample "  << n << ": ";
        for (auto i = 0; i < 4; i++) {
            //// Canfeast each joints position and put into X2 objects joints using posCallBack(qRead)
            // joint addresses
            // LHIP 1
            // LKNEE 2
            // RHIP 3
            // RKNEE 4
            //// i+1 is joint address
            qRead = getPos(&socket, i+1 , junk);
            X2.joints[i].posCallBack(qRead); /// update that joint with its read position
//            std::cout << X2.joints[i].getPos() << "\n";
//            myfile << X2.joints[i].getPos() << "    " ;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        n++;
    }
    canFeastDown(&socket);
//    myfile.close();
    //// Close canFeast socket to canopend
}

/// Test thread for reading virtual X2 positions for testing multithreading
//// Status: functioning
void testReadThread(Robot& X2, int counts){
    std::cout<<"----------READING THREAD BEGIN-------------"<<"\n";
    // file output of read in values
    ofstream myfile;
    myfile.open ("output.txt");
    int n = 0;
    while(n<counts) {
        myfile << "\n" << "Sample "  << n << ": ";
        for (auto i = 0; i < 4; i++) {
//            std::cout << X2.joints[i].getPos() << "\n";
            myfile << X2.joints[i].getPos() << "    " ;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        n++;
    }
    myfile.close();
}

//// canFeast functionality
//Reads position of specified node using canFeast
long getPos(int *canSocket, int nodeid, char *canReturnMessage)
{
    char node[STRING_LENGTH], getpos[STRING_LENGTH], dataType[STRING_LENGTH], buffer[STRING_LENGTH];
    char positionMessage[STRING_LENGTH];
    char *positionStr;
    long position;

    //Create a message to be sent using canFeast. "[1] <nodeid> read 0x6063 0 i32"
    //Return should be "[1] <position value>\r"
    itoa(nodeid, buffer, DECIMAL);
    strcpy(getpos, "[1] ");
    strcpy(node, buffer);
    strcpy(dataType, " read 0x6063 0 i32");
    //concatenate message
    strcat(getpos, node);
    strcat(getpos, dataType);
    //Send message
    canFeast(canSocket, getpos, positionMessage);

    //printf("Position Message for node %d: %s",nodeid, positionMessage);

    //Extracting 2 position of return string. This should contain position value (if no errors).
    stringExtract(positionMessage, &positionStr, 2);
    // printf("Extracted Message for node %d: %s\n",nodeid, positionStr);

    //Converting string to int
    position = strToInt(positionStr);
    // printf("Position of node %d: %ld\n", nodeid, position);

    return position;
}
//// Creates a socket connection to canopend using a pointer to int socket
void canFeastUp(int *canSocket)
{
    char *socketPath = "/tmp/CO_command_socket"; /* Name of the local domain socket, configurable by arguments. */
    struct sockaddr_un addr;

    *canSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (*canSocket == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path) - 1);
    // Try to make a connection to the local UNIT AF_UNIX SOCKET, quit if unavailable
    if (connect(*canSocket, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("Socket connection failed");
        exit(EXIT_FAILURE);
    }
}
//// Shuts down canFeast socket
void canFeastDown(int *canSocket)
{
    printf("closing socket...\n");
    //close socket
    close(*canSocket);
    printf("socket close\n");
}
//// Sends message over a canSocket established connection
void canFeast(int *canSocket, char *command, char *canReturnMessage)
{
    int commandLength = strlen(command);
    size_t n;
    char buf[BUF_SIZE];

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
//// Canfeast message parsing functions

//Definitionof itoa(int to string conversion) and helper Kernighan & Ritchie's Ansi C.
//char *  itoa ( int value, char * str, int base );
//value - Value to be converted to a string.
//str - Array in memory where to store the resulting null-terminated string.
//base - Numerical base used to represent the value as a string, between 2 and 36, where 10 means decimal base, 16 hexadecimal, 8 octal, and 2 binary.
void itoa(int value, char *str, int base)
{
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *wstr = str;
    int sign;

    // Validate base
    if (base < 2 || base > 35)
    {
        *wstr = '\0';
        return;
    }

    // Take care of sign
    if ((sign = value) < 0)
        value = -value;

    // Conversion. Number is reversed.
    do
        *wstr++ = num[value % base];
    while (value /= base);

    if (sign < 0)
        *wstr++ = '-';

    *wstr = '\0';

    // Reverse string
    strreverse(str, wstr - 1);
}

//Reverses a string. Used by itoa()
void strreverse(char *begin, char *end)
{
    char aux;
    while (end > begin)
        aux = *end, *end-- = *begin, *begin++ = aux;
}

//Extracts a string at position pos of origStr and stores it in extractStr.
//Index 0 is position 1.
// IMPORTANT: The origStr passed into the function gets modified. So pass a copy if needed.
void stringExtract(char *origStr, char **extractStr, int pos)
{
    //using both space, nextline and carriage return as delimiter
    char delim[] = " \n\r";
    char *ptr = strtok(origStr, delim);

    //strtok extracts each string using delimiter specified earlier.
    for (int i = 0; ptr != NULL && i < pos; i++)
    {
        *extractStr = ptr;
        ptr = strtok(NULL, delim);
    }
}

//Converts strings to integer and returns it.
long strToInt(char str[])
{
    int len = strlen(str);
    long num = 0;

    //If there is - in the beginning, then just convert the remaining chars and return -ve of value.
    if (str[0] == '-')
    {
        for (int i = 0, j = 1; i < (len - 1); i++, j *= 10)
            num += ((str[len - (i + 1)] - '0') * j); //ASCII subtraction followed by multiplying factor of 10
        return -num;
    }

    //if no -ve, then just convert convert char to int.
    for (int i = 0, j = 1; i < len; i++, j *= 10)
        num += ((str[len - (i + 1)] - '0') * j); //ASCII subtraction followed by multiplying factor of 10
    return num;
}

