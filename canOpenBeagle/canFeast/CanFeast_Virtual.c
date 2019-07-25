/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

#ifndef BUF_SIZE
#define BUF_SIZE 100000
#endif
#define MAX_STRINGS 40

/* Helper functions */
static void sendCommand(int fd, char *command, size_t commandLength);

void canFeast (char *buf);

int main (/*int argc, char *argv[]*/){
	printf("Welcome to canFeast!\n");

    char commList[][MAX_STRINGS]=
            {
                    "[1] 4 start", //go to start mode
                    "[1] 4 read 0x1008 0 vs", //read hardware name
                    "[1] 4 read 0x1017 0 i16", //read heartbeat timing
					"[1] 4 write 0x1017 0 i16 10000", //set heartbeat to 10s
            };

    int Num_of_Strings = sizeof(commList)/MAX_STRINGS;

    //printf("%d", Num_of_Strings);
    for(int i=0; i<Num_of_Strings; ++i)
        canFeast(commList[i]);
    return 1;
}

void canFeast (char *buf) {
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
		 sendCommand(fd, buf, strlen(buf));
	 //}

	 //close socket
	 close(fd);

}

static void sendCommand(int fd, char *command, size_t commandLength)
{
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
}

