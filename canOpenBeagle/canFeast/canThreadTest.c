//
// Created by William Campbell on 2019-07-26.
//

/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#ifndef BUF_SIZE
#define BUF_SIZE 100000
#endif
#define MAX_STRINGS 40
#define NUM_POS_POLLS 100
#define DECIMAL 10
#define BUTTON_ONE 1
#define BUTTON_TWO 2
#define BUTTON_THREE 3
#define BUTTON_FOUR 4


/* Helper functions */
static void sendCommand(int fd, char *command, size_t commandLength, int* canOutput);
void canFeast (char *buf, int* canOutput);
void getButton(int button, int* canOutput);
// MAKE ME ACCEPT drivePOS we want
void setAbsPos();
// MAKE ME ACCEPT nodeID
void getPos();
void remove_spaces(char* s);

void setAbsPosSmart(int position);
/* Helpers for int to string conversion */
void itoa(int value, char* str, int base);
void strreverse(char* begin, char* end);



int main (/*int argc, char *argv[]*/){
    printf("Welcome to canFeast!\n");
    pthread_t thread_id1, thread_id2;
    pthread_create(&thread_id1, NULL, do_process1, (void*) j);
    pthread_create(&thread_id2, NULL, do_process2, (void*) k);
    setAbsPosSmart(200000);
    return 0;
}

void getButton(int button, int* canOutput){
    char buttons[][MAX_STRINGS]=
            {
                    "[1] 9 read 0x0101 1 u32", //button 1
                    "[1] 9 read 0x0102 1 u32",//button 2
                    "[1] 9 read 0x0103 1 u32", //button 1
                    "[1] 9 read 0x0104 1 u32"//button 2
            };
    canFeast(buttons[button-1], canOutput);
}
//GET THIS TO WORK WITH SPECIFC NODE ID
void getPos(int nodeid)
{
    char node[MAX_STRINGS], getpos[MAX_STRINGS], dataType[MAX_STRINGS],char buffer[MAX_STRINGS];
    itoa(nodeid,buffer,10);
    strcpy(getpos, "[1] 2 read 0x6063 ");
    strcpy(node, buffer);
    strcpy(dataType," i32");
    //concatenate message
    strcat(getpos, node);
    strcat(getpos, dataType);
    int canOutput = 0;
    int count;
    while(count< NUM_POS_POLLS){
        count ++;
        canFeast(getpos, &canOutput);
    }
}
void setAbsPos(int position)
{
    char pos[MAX_STRINGS], movePos[MAX_STRINGS];
    char buffer[MAX_STRINGS];
    itoa(position,buffer,10);
    printf("Decimal value = %s\n", buffer);
    strcpy(movePos, "[1] 2 write 0x607A 0 i32 ");
    strcpy(pos, buffer);
    strcat(movePos, pos);
    printf("%s\n",movePos);

    char* commList[MAX_STRINGS];
    commList[0]= "[1] 2 start"; //go to start mode
    commList[1]= "[1] 2 read 0x1008 0 vs"; //read hardware name
    commList[2]= "[1] 2 read 0x1017 0 i16"; //read heartbeat timing
    commList[3]= "[1] 2 write 0x1017 0 i16 10000"; //set heartbeat to 10s
    commList[4]= "[1] 2 write 0x6060 0 i8 1"; //Drive to position mode
    commList[5]= "[1] 2 read 0x6061 0 i8"; //display current drive mode
    commList[6]= "[1] 2 read 0x6063 0 i32"; //display current knee position
    commList[7]= movePos; //move to this position (absolute)
    commList[8]= "[1] 2 read 0x607A 0 i32"; //display target position
    commList[9]= "[1] 2 read 0x6041 0 i16"; //display status word
    commList[10]= "[1] 2 write 0x6040 0 i16 47"; //control word low
    commList[11]= "[1] 2 write 0x6040 0 i16 63"; //control word high

    int Num_of_Strings = sizeof(commList)/MAX_STRINGS;

    //printf("%d", Num_of_Strings);
    for(int i=0; i<Num_of_Strings; ++i)
        canFeast(commList[i],&canOutput);

}

void canFeast(char *buf,int* canOutput) {
    char *socketPath = "/tmp/CO_command_socket";  /* Name of the local domain socket, configurable by arguments. */
    //char buf[BUF_SIZE];
    int fd;
    struct sockaddr_un addr;
    //int opt;
    //int i;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path) - 1);
    // Try to make a connection to the local UNIT AF_UNIX SOCKET, quit if unavailable
    if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("Socket connection failed");
        exit(EXIT_FAILURE);
    }
    /*get command and send down socket, print response to screen*/
    // get commands from stdin until end.
    //while (fgets(buf, BUF_SIZE, stdin) != NULL)
    //{
    sendCommand(fd, buf, strlen(buf),canOutput);
    //}

    //close socket
    close(fd);
}

static void sendCommand(int fd, char *command, size_t commandLength, int* canOutput)
{
    //will: change this hackey BUTTON_PRESS logic
    char button_press= '3';
    size_t n;
    char buf[BUF_SIZE];

    if (write(fd, command, commandLength) != commandLength)
    {
        perror("Socket write failed");
        exit(EXIT_FAILURE);
    }

    n = read(fd, buf, sizeof(buf));
    if (n == -1)
    {
        perror("Socket read failed");
        exit(EXIT_FAILURE);
    }
    printf("%s", buf);
    if(buf[6] == button_press)
    {
        *canOutput = 1;
    }
    else
    {
        *canOutput = 0;
    }
}

////Definitionof itoa(int to string conversion) and helper Kernighan & Ritchie's Ansi C.

void itoa(int value, char* str, int base) {

    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    char* wstr=str;

    int sign;




    // Validate base

    if (base<2 || base>35){ *wstr='\0'; return; }



    // Take care of sign

    if ((sign=value) < 0) value = -value;




    // Conversion. Number is reversed.

    do *wstr++ = num[value%base]; while(value/=base);

    if(sign<0) *wstr++='-';

    *wstr='\0';



    // Reverse string


    strreverse(str,wstr-1);

}
void strreverse(char* begin, char* end) {

    char aux;

    while(end>begin)

        aux=*end, *end--=*begin, *begin++=aux;

}
