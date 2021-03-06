/*
 * Application interface for CANopenSocket.
 *
 * @file        application.c
 * @author      Janez Paternoster
 * @copyright   2016 Janez Paternoster
 *
 * This file is part of CANopenSocket, a Linux implementation of CANopen
 * stack with master functionality. Project home page is
 * <https://github.com/CANopenNode/CANopenSocket>. CANopenSocket is based
 * on CANopenNode: <https://github.com/CANopenNode/CANopenNode>.
 *
 * CANopenSocket is free and open source software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "CANopen.h"
#include "stdio.h"
#include <stdint.h>
#include <sys/time.h>

//// Data logger helper functions
void fileLoggerBinary();
void fileLogHeader();
void fileLogger();
void strreverse(char *begin, char *end);
void itoa(int value, char *str, int base);
/******************************************************************************/
void app_programStart(void){
    //void fileLogHeader();
}
/******************************************************************************/
void app_communicationReset(void){
}
/******************************************************************************/
void app_programEnd(void){
}
/******************************************************************************/
void app_programAsync(uint16_t timer1msDiff){
//Timing speed of reading from memory and file writing
//struct timeval start;
//struct timeval stop;
//gettimeofday(&start, NULL);
/*
struct timeval tv;
gettimeofday(&tv,NULL);
printf("time before(s): %lu, (us): %lu\n",tv.tv_sec, tv.tv_usec);
fileLogger(timer1msDiff);
gettimeofday(&tv,NULL);
printf("time after(s): %lu, (us): %lu\n",tv.tv_sec, tv.tv_usec);
*/
//gettimeofday(&stop, NULL);
//double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
//elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
//printf("TASK 1:  %.2f milliseconds\n", elapsed_ms);
}

/******************************************************************************/
void app_program1ms(void){
	fileLoggerBinary();
}
/******************************************************************************/
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
/******************************************************************************/
void strreverse(char *begin, char *end)
{
    char aux;
    while (end > begin)
        aux = *end, *end-- = *begin, *begin++ = aux;
}
/******************************************************************************/
void fileLogger(){
    //printf("fileLogger beggining\n");
    FILE* fp;
    fp = fopen("X2_log.txt", "a");
    // Generate whatever you want logged here, "data" is just an example
    char position [50];
	char timestamp [50];
    char torque[50];
    char comma[] = ", ";
	
	//Getting timestamp
	//printf("time(s): %lu, (us): %lu\n",tv.tv_sec, tv.tv_usec);
    //itoa(timer1msDiff, position, 10);
	struct timeval tv;
	gettimeofday(&tv,NULL);
	itoa(tv.tv_sec, timestamp, 10);
    fputs(timestamp, fp);
    fputs(comma, fp);
	itoa(tv.tv_usec, timestamp, 10);
	fputs(timestamp, fp);
    fputs(comma, fp);
	
    // Motor 1: Left Hip position and Torque
    itoa(CO_OD_RAM.actualMotorPositions.motor1, position, 10);
    itoa(((int16_t)CO_OD_RAM.statusWords.motor1), torque, 10);
    fputs(position, fp);
    fputs(comma, fp);
    fputs(torque, fp);
    fputs(comma, fp);
    // Motor 2: Left Knee position and Torque
    itoa(CO_OD_RAM.actualMotorPositions.motor2, position, 10);
    itoa(((int16_t)CO_OD_RAM.statusWords.motor2), torque, 10);
    fputs(position, fp);
    fputs(comma, fp);
    fputs(torque, fp);
    fputs(comma, fp);
    // Motor 3: Right Hip position and Torque
    itoa(CO_OD_RAM.actualMotorPositions.motor3, position, 10);
    itoa(((int16_t)CO_OD_RAM.statusWords.motor3), torque, 10);
    fputs(position, fp);
    fputs(comma, fp);
    fputs(torque, fp);
    fputs(comma, fp);
    // Motor 4: Right Knee position and Torque
    itoa(CO_OD_RAM.actualMotorPositions.motor4, position, 10);
    itoa(((int16_t)CO_OD_RAM.statusWords.motor4), torque, 10);
    fputs(position, fp);
    fputs(comma, fp);
    fputs(torque, fp);
    fputs("\n", fp);
	
    fclose(fp);
	
}
void fileLogHeader(){
    FILE *fp;
    fp = fopen("X2_log.txt", "a");
    char header1[] = "======================================\n";
    char header2[] = "X2 exoskeleton torque and position log\n";
    char header3[] = "======================================\n";
    char header4[]= "Time(s), time(ms) LHPos, LHT, LKPos, LKT, RHPos, RHT,RKPos, RKT\n";
    fputs(header1, fp);
    fputs(header2, fp);
    fputs(header3, fp);
    fputs(header4, fp);
    fclose(fp);
}

void fileLoggerBinary(){
    FILE* fp;
    uint32_t sizeInt = 0;
    fp = fopen("/media/sdcard1/X2logs/X2_log.bin", "ab");
	if(fp==NULL)
		printf("\nFILE CREATION ERROR\n");

    struct timeval tv;
    gettimeofday(&tv,NULL);

    uint32_t motor1pos=CO_OD_RAM.actualMotorPositions.motor1;
    uint32_t motor2pos=CO_OD_RAM.actualMotorPositions.motor2;
    uint32_t motor3pos=CO_OD_RAM.actualMotorPositions.motor3;
    uint32_t motor4pos=CO_OD_RAM.actualMotorPositions.motor4;
    uint16_t motor1Tor=CO_OD_RAM.statusWords.motor1;
    uint16_t motor2Tor=CO_OD_RAM.statusWords.motor2;
    uint16_t motor3Tor=CO_OD_RAM.statusWords.motor3;
    uint16_t motor4Tor=CO_OD_RAM.statusWords.motor4;
    long long timesec=tv.tv_sec;
    long timeusec=tv.tv_usec;


    fwrite(&timesec, sizeof(timesec), 1, fp);
    fwrite(&timeusec, sizeof(timeusec), 1, fp);
    fwrite(&motor1pos, sizeof(sizeInt), 1, fp);
    fwrite(&motor1Tor, sizeof(sizeInt), 1, fp);
    fwrite(&motor2pos, sizeof(sizeInt), 1, fp);
    fwrite(&motor2Tor, sizeof(sizeInt), 1, fp);
    fwrite(&motor3pos, sizeof(sizeInt), 1, fp);
    fwrite(&motor3Tor, sizeof(sizeInt), 1, fp);
    fwrite(&motor4pos, sizeof(sizeInt), 1, fp);
    fwrite(&motor4Tor, sizeof(sizeInt), 1, fp);

    fclose(fp);
}