///
//// Created by William Campbell on 2019-07-01.
//// ALEX EXOSKELETON Button polling test
////
#include "Robot.h"
#include "Joint.h"

/* Helper functions */
void initexo(Robot& robot);
const int NUM_JOINTS = 4;
const int STRING_LENGTH =50;

const int BUTTON_ONE = 1;
const int BUTTON_TWO = 2;
const int BUTTON_THREE = 3;
const int BUTTON_FOUR = 4;
int main() {
    Robot X2;
    initexo(X2);
    X2.printInfo();
    //Start sockets with canopend
    int socket;
    //Used to store the canReturnMessage. Not used currently, hence called junk.
    //Should pass this to calling function for possible error handling.
    char messageRecieved[STRING_LENGTH];
    char messageSent[STRING_LENGTH]= "[1] 100 read 0x1017 0 i16";
    X2.canFeastUp(&socket);
    while(true) {
        // check the bbb heartbeat.
        X2.canFeast(&socket, messageSent, messageRecieved);
        cout<< (char *)messageRecieved;
        std::cin.ignore();
    }
    X2.canFeastDown(&socket);

    return 0;
}


void initexo(Robot& X2){
    // Initialize canOpenBBB node through canOpend, bind socket w/ parser callback.
//    const int NUM_JOINTS = 4;
    ////    Initialize robot
/*   X2.printInfo();*/
    ////    initialize all joints to Current read position (STATE) or homing sequence?
    float position = 90.0;
    cout<<"----------Reading actual joint pos and internalizing----------\n";
    for (auto x=0;x< NUM_JOINTS;x++){
        X2.joints[x].applyPos(position);
        position+=15.0;
    }
}

//Used to read button status. Returns 1 if button is pressed
int getButton(int *canSocket, int button, char *canReturnMessage)
{
    //char canReturnMessage[STRING_LENGTH];
    char *buttonMessage;
    char *buttonPressed = "0x3F800000";

    char buttons[][STRING_LENGTH] =
            {
                    "[1] 9 read 0x0101 1 u32", //button 1
                    "[1] 9 read 0x0102 1 u32", //button 2
                    "[1] 9 read 0x0103 1 u32", //button 3
                    "[1] 9 read 0x0104 1 u32"  //button 4
            };
    canFeast(canSocket, buttons[button - 1], canReturnMessage);

    //printf("CAN return on button press is: %s", canReturnMessage);
    //Button pressed returns "[1] 0x3F800000\n". Extracting 2nd string to compare.
    stringExtract(canReturnMessage, &buttonMessage, 2);

    //printf("strcmp result is: %d\n", strcmp(canReturnMessage, "[1] 0x3F800000\r"));

    if (strcmp(buttonMessage, buttonPressed) == 0)
        return 1;
    else
        return 0;
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
