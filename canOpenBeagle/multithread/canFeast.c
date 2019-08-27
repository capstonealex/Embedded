//
// Created by William Campbell on 2019-08-27.
//
// C libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include "canFeast.h"

///// test of cpp library linking
int addnumbers(int a, int b){
    printf("Adding two numbers...\n");
    return a+b;
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
    // cast string constant to char * for C++ compatibility
    char *socketPath = ((char *)"/tmp/CO_command_socket"); /* Name of the local domain socket, configurable by arguments. */
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

