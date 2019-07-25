//
// Created by William Campbell on 2019-07-25.
// Testing function pointer call backs
//

/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>


void sendCommand( int* canOutput);
void canFeast ( int* canOutput);


int main (/*int argc, char *argv[]*/){
    printf("Welcome to canFeast!\n");
    int canOutput = 0;
    printf("%d\n",canOutput);
    canFeast(&canOutput);
    printf("%d\n",canOutput);


    return 0;
}



void sendCommand( int* canOutput){
    *canOutput = *canOutput + 1;

}
void canFeast ( int* canOutput){
    sendCommand( canOutput);
}