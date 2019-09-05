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
#include <stdio.h>
#include <time.h>

/******************************************************************************/
void itoa(int value, char *str, int base);
//Reverses a string. Used by itoa()
void strreverse(char *begin, char *end);

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
void app_programStart(void){

}


/******************************************************************************/
void app_communicationReset(void){

}


/******************************************************************************/
void app_programEnd(void){

}


/******************************************************************************/
void app_programAsync(uint16_t timer1msDiff){

}


/******************************************************************************/
void app_program1ms(void){
    // printf("RT THREAD PROGRAM\n");
    // int n = 0;
    /// Timer code
    // struct timeval start;
    // struct timeval stop;
    // gettimeofday(&start, NULL);
    // while(n<1000){
    //     printf("%d\n", CO_OD_ROM.producerHeartbeatTime);
    //     n++;
    // }
    // gettimeofday(&stop, NULL);
    // double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    // elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
    // printf("TASK 1:  %.2f milliseconds\n", elapsed_ms);
    /* Logger code block*/
    FILE* fp;
    fp = fopen("log.txt", "a");

    // Generate whatever you want logged here, "data" is just an example
    char data [50];
    itoa(CO_OD_ROM.producerHeartbeatTime, data, 10);
    // This lines writes the info in "data" to the file pointer specified
    fputs(data, fp);
    fputs("\n", fp);

    // Always remember to close your files
    fclose(fp);

}

