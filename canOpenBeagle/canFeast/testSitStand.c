/*
 * C Program which Converts an Integer to String & vice-versa
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

#define STRING_LENGTH 50
#define NUM_POS_POLLS 10
#define DECIMAL 10

void itoa(int value, char* str, int base);
void strreverse(char* begin, char* end);
void preop(int nodeid);
void initMotorPos(int nodeid);

int main()
{
    int node = 10;

    initMotorPos(node);

    return 0;
}

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

//set node to preop mode
void preop(int nodeid){
    char node[STRING_LENGTH], preop[STRING_LENGTH], dataTail[STRING_LENGTH], buffer[STRING_LENGTH];
    itoa(nodeid,buffer,DECIMAL);
    strcpy(preop, "[1] ");
    strcpy(node, buffer);
    strcpy(dataTail," preop");
    //concatenate message
    strcat(preop, node);
    strcat(preop, dataTail);
    printf("%s\n",preop);
}

//start motor and set to position mode.
void initMotorPos(int nodeid){
    char node[STRING_LENGTH], comm[STRING_LENGTH], dataTail[STRING_LENGTH], buffer[STRING_LENGTH];
    itoa(nodeid,buffer,DECIMAL);

    //creating message for start mode
    strcpy(comm, "[1] ");
    strcpy(node, buffer);
    strcpy(dataTail," start");
    //concatenate message
    strcat(comm, node);
    strcat(comm, dataTail);
    printf("%s\n",comm);

    //creating message for position mode
    strcpy(comm, "[1] ");
    strcpy(node, buffer);
    strcpy(dataTail," write 0x6060 0 i8 1");
    //concatenate message
    strcat(comm, node);
    strcat(comm, dataTail);
    printf("%s\n",comm);
}