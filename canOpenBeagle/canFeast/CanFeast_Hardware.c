/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 100000
#endif
#define MAX_STRINGS 40
#define BUTTON_ONE 1
#define BUTTON_TWO 2
#define BUTTON_THREE 3
#define BUTTON_FOUR 4


/* Helper functions */
static void sendCommand(int fd, char *command, size_t commandLength, int* canOutput);
void canFeast (char *buf, int* canOutput);
void getButton(int button);
// MAKE ME ACCEPT drivePOS we want
void setAbsPos();
// MAKE ME ACCEPT nodeID
void getPos();


int main (/*int argc, char *argv[]*/){
	printf("Welcome to canFeast!\n");
	int canOutput = 0;
    while(canOutput == 0){
        getButton(BUTTON_ONE);
    }

	
    return 0;
}

void getButton(int button){
    char buttons[][MAX_STRINGS]=
            {
                    "[1] 9 read 0x0101 1 u32", //button 1
                    "[1] 9 read 0x0102 1 u32",//button 2
                    "[1] 9 read 0x0103 1 u32", //button 1
                    "[1] 9 read 0x0104 1 u32"//button 2
            };
    canFeast(buttons[button-1]);
}
//GET THIS TO WORK WITH SPECIFC NODE ID
void getPos()
{
    char *buf="[1] 2 read 0x6063 0 i32"; //display current knee position
    //char *input = NULL;
    int count = 0;

    while(count<100){
        count ++;
        canFeast(buf);
    }
}
void setAbsPos()
{
    char commList[][MAX_STRINGS]=
            {
                    "[1] 2 start", //go to start mode
                    "[1] 2 read 0x1008 0 vs", //read hardware name
                    "[1] 2 read 0x1017 0 i16", //read heartbeat timing
                    "[1] 2 write 0x1017 0 i16 10000", //set heartbeat to 10s
                    "[1] 2 write 0x6060 0 i8 1", //Drive to position mode
                    "[1] 2 read 0x6061 0 i8", //display current drive mode
                    "[1] 2 read 0x6063 0 i32", //display current knee position
                    "[1] 2 write 0x607A 0 i32 200000", //move to this position (absolute)
                    "[1] 2 read 0x607A 0 i32", //display target position
                    "[1] 2 read 0x6041 0 i16", //display status word
                    "[1] 2 write 0x6040 0 i16 47", //control word low
                    "[1] 2 write 0x6040 0 i16 63" //control word high

            };

    int Num_of_Strings = sizeof(commList)/MAX_STRINGS;

    //printf("%d", Num_of_Strings);
    for(int i=0; i<Num_of_Strings; ++i)
        canFeast(commList[i]);

}

void canFeast (char *buf,int* canOutput) {
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
	 return return_command;

}

static void sendCommand(int fd, char *command, size_t commandLength, int* c)
{
    //will: change this hackey BUTTON_PRESS logic
    char button_press[] = "[1] 0x3F800000";
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
    if(strcmp(buff,button_press)==0)
    {
        *canOutput = 1;
    }
    else
    {
        *canOutput = 0;
    }
}

