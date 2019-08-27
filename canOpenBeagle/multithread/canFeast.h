//
// Created by William Campbell on 2019-08-27.
//

#ifndef EMBEDED_CANFEAST_H
#define EMBEDED_CANFEAST_H

#define BUF_SIZE 100000
//String Length for defining fixed sized char array
#define STRING_LENGTH 50
#define MAX_RECONNECTS 10
//Base for int to str conversion
#define DECIMAL 10

//// testing cpp linking
int addnumbers(int a, int b);
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







#endif //EMBEDED_CANFEAST_H
