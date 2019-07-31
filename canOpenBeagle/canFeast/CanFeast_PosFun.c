#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <math.h>


#ifndef BUF_SIZE
#define BUF_SIZE 100000
#endif
#define STRING_LENGTH 50
#define NUM_POS_POLLS 10
#define DECIMAL 10
#define BUTTON_ONE 1
#define BUTTON_TWO 2
#define BUTTON_THREE 3
#define BUTTON_FOUR 4


/* Helper functions */
static void sendCommand(int fd, char *command, size_t commandLength, int* canOutput);
void canFeast (char *buf, int* canOutput);
void getButton(int button, int* canOutput);
// MAKE ME ACCEPT nodeID
void getPos(int nodeid, int* canOutput);
void setAbsPosSmart(int position, int* canOutput);
/* Helpers for int to string conversion */
void itoa(int value, char* str, int base);
void strreverse(char* begin, char* end);
void stringExtract(char *origStr, char **extractStr, int pos);
int strToInt(char str[]);

int main (){
    int canOutput=0;
    printf("Welcome to CANfeast!\n");


    return 0;
}

void getButton(int button, int* canOutput){
    char buttons[][STRING_LENGTH]=
            {
                    "[1] 9 read 0x0101 1 u32", //button 1
                    "[1] 9 read 0x0102 1 u32",//button 2
                    "[1] 9 read 0x0103 1 u32", //button 3
                    "[1] 9 read 0x0104 1 u32"//button 4
            };
    canFeast(buttons[button-1], canOutput);
}

void getPos(int nodeid, int* canOutput){
    char node[STRING_LENGTH], getpos[STRING_LENGTH], dataType[STRING_LENGTH], buffer[STRING_LENGTH];
    itoa(nodeid,buffer,DECIMAL);
    strcpy(getpos, "[1] ");
    strcpy(node, buffer);
    strcpy(dataType," read 0x6063 0 i32");
    //concatenate message
    strcat(getpos, node);
    strcat(getpos, dataType);
    int count=0;
    while(count< NUM_POS_POLLS){
        count ++;
        canFeast(getpos, canOutput);
    }
}

void setAbsPosSmart(int position, int* canOutput){
    char pos[STRING_LENGTH], movePos[STRING_LENGTH];
    char buffer[STRING_LENGTH];
    itoa(position,buffer,DECIMAL);
    printf("Decimal value = %s\n", buffer);
    strcpy(movePos, "[1] 2 write 0x607A 0 i32 ");
    strcpy(pos, buffer);
    strcat(movePos, pos);
    printf("%s\n",movePos);

    char* commList[]= {
            "[1] 2 start", //go to start mode
            "[1] 2 write 0x6060 0 i8 1", //Drive to position mode
            "[1] 2 read 0x6063 0 i32", //display current knee position
            movePos, //move to this position (absolute)
            "[1] 2 write 0x6040 0 i16 47", //control word low
            "[1] 2 write 0x6040 0 i16 63" //control word high
    };

    int Num_of_Strings = sizeof(commList)/ sizeof(commList[0]);
    for(int i=0; i<Num_of_Strings; ++i)
        canFeast(commList[i],canOutput);
}

void canFeast(char *buf,int* canOutput) {
    char *socketPath = "/tmp/CO_command_socket";  /* Name of the local domain socket, configurable by arguments. */
    int fd;
    struct sockaddr_un addr;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path) - 1);
    // Try to make a connection to the local UNIT AF_UNIX SOCKET, quit if unavailable
    if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1){
        perror("Socket connection failed");
        exit(EXIT_FAILURE);
    }
    sendCommand(fd, buf, strlen(buf),canOutput);
    //close socket
    close(fd);
}

static void sendCommand(int fd, char *command, size_t commandLength, int* canOutput)
{
    //will: change this hackey BUTTON_PRESS logic
    char button_press= '3';
    size_t n;
    char buf[BUF_SIZE];

    if (write(fd, command, commandLength) != commandLength){
        perror("Socket write failed");
        exit(EXIT_FAILURE);
    }

    n = read(fd, buf, sizeof(buf));
    if (n == -1){
        perror("Socket read failed");
        exit(EXIT_FAILURE);
    }
    printf("%s", buf);
    if(buf[6] == button_press){
        *canOutput = 1;
    }
    else{
        *canOutput = 0;
    }
}

////Definitionof itoa(int to string conversion) and helper Kernighan & Ritchie's Ansi C.
////Converts an integer value to a null-terminated string using the specified base and stores the result in the array given by str parameter.
////If base is 10 and value is negative, the resulting string is preceded with a minus sign (-). With any other base, value is always considered unsigned.
////char *  itoa ( int value, char * str, int base );
////value - Value to be converted to a string.
////str - Array in memory where to store the resulting null-terminated string.
////base - Numerical base used to represent the value as a string, between 2 and 36, where 10 means decimal base, 16 hexadecimal, 8 octal, and 2 binary.
void itoa(int value, char* str, int base) {
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    int sign;

    // Validate base
    if (base<2 || base>35){
        *wstr='\0';
        return;
    }

    // Take care of sign
    if ((sign=value) < 0)
        value = -value;

    // Conversion. Number is reversed.
    do
        *wstr++ = num[value%base];
    while(value/=base);

    if(sign<0)
        *wstr++='-';

    *wstr='\0';

    // Reverse string
    strreverse(str,wstr-1);
}

void strreverse(char* begin, char* end) {
    char aux;
    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}

//Extracts a string at position pos of origStr and stores it in extractStr.
//Index 0 is position 1
// IMPORTANT: The origStr passed into the function gets modified. So pass a copy if needed.
void stringExtract(char *origStr, char **extractStr, int pos){
    char delim[] = " ";
    char *ptr = strtok(origStr, delim);

    for(int i=0; ptr != NULL && i<pos; i++){
        *extractStr=ptr;
        ptr = strtok(NULL, delim);
    }
}

int strToInt(char str[]){
    int len = strlen(str);
    int i, num = 0;

    if(str[0]=='-'){
        for (i = 0; i < len-1; i++){
            num += (str[len - (i + 1)] - '0') * pow(10, i);
        }
        return -num;
    }

    for (i = 0; i < len; i++) {
        num += ((str[len - (i + 1)] - '0') * pow(10, i));
    }

    return num;
}