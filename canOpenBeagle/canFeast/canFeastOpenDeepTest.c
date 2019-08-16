//
// Created by William Campbell on 2019-08-16.
// Testing canFeast passing a socket into a function which uses that socket under canFeastOpen
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>

//Buffer for socket
#ifndef BUF_SIZE
#define BUF_SIZE 100000
#endif

#define STRING_LENGTH 50
#define MAX_STRINGS 40
#define MAX_RECONNECTS 10


void canFeastUp(int *canSocket);
void canFeast(int *canSocket, char *command, char *canReturnMessage);
void canFeastDown(int *canSocket);
void canFeastErrorHandler(int *canSocket, char *command, char *canReturnMessage);
int getTestDeep (int *canSocket, char *canReturnMessage);
// Test code
int main (/*int argc, char *argv[]*/){
    //Used to store the canReturnMessage. Not used currently, hence called junk.
    //Should pass this to calling function for possible error handling.
    char junk[STRING_LENGTH];
    printf("Welcome to canFeastOpen test!\n");
    int socket;
    //set up canFeasts socket
    canFeastUp(&socket);
    getTestDeep(&socket, junk);
    canFeastDown(&socket);
    return 1;

}

int getTestDeep (int *canSocket, char *canReturnMessage){
    char commList[][MAX_STRINGS]=
            {
                    "[1] 4 start", //go to start mode
                    "[1] 4 read 0x1008 0 vs", //read hardware name
                    "[1] 4 read 0x1017 0 i16", //read heartbeat timing
                    "[1] 4 write 0x1017 0 i16 10000", //set heartbeat to 10s
            };
    int Num_of_Strings = sizeof(commList)/MAX_STRINGS;

    for(int i=0; i<Num_of_Strings; ++i) {
        canFeast(canSocket, commList[i], canReturnMessage);
    }
    return 1;
}
void canFeastUp(int *canSocket) {
    char *socketPath = "/tmp/CO_command_socket";  /* Name of the local domain socket, configurable by arguments. */
    struct sockaddr_un addr;

    *canSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (*canSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path) - 1);
// Try to make a connection to the local UNIT AF_UNIX SOCKET, quit if unavailable
    if (connect(*canSocket, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        perror("Socket connection failed");
        exit(EXIT_FAILURE);
    }
}
void canFeast(int *canSocket, char *command, char *canReturnMessage) {
    int commandLength = strlen(command);
    size_t n;
    char buf[BUF_SIZE];

    if (write(*canSocket, command, commandLength) != commandLength){
        perror("Socket write failed");
        exit(EXIT_FAILURE);
    }

    n = read(*canSocket, buf, sizeof(buf));
    if (n == -1){
        perror("Socket read failed");
        close(*canSocket);
        exit(EXIT_FAILURE);
    }
    printf("%s", buf);
    strcpy(canReturnMessage,buf);

}
// Error handling -> reset socket and try again when sockets fail.
void canFeastErrorHandler(int *canSocket, char *command, char *canReturnMessage) {
    int commandLength = strlen(command);
    int recconects;
    size_t n;
    char buf[BUF_SIZE];

    if (write(*canSocket, command, commandLength) != commandLength){
        perror("Socket write failed, attempting again");
        canFeast( canSocket, command, canReturnMessage);
    }
    while((write(*canSocket, command, commandLength) != commandLength) && recconects!= MAX_RECONNECTS){
        perror("Socket write failed, attempting again");
        //shut down socket
        canFeastDown(canSocket);
        //recreate socket
        canFeastUp(canSocket);
        recconects ++;
        // try to send again
    }


    n = read(*canSocket, buf, sizeof(buf));
    if (n == -1){
        perror("Socket read failed, attempting to send command again");
        //shut down socket
        canFeastDown(canSocket);
        //recreate socket
        canFeastUp(canSocket);
        // try to send again
        canFeast( canSocket, command, canReturnMessage);
        exit(EXIT_FAILURE);
    }
    printf("%s", buf);
    strcpy(canReturnMessage,buf);

}

void canFeastDown(int *canSocket) {
    printf("closing socket...\n");
    //close socket
    close(*canSocket);
    printf("socket close\n");
}