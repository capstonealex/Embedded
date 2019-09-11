//
// Created by William Campbell on 2019-09-11.
//
#include <stdio.h>
#include <sys/time.h>

void fileLogger(int n);
void itoa(int value, char *str, int base);
//Reverses a string. Used by itoa()
void strreverse(char *begin, char *end);
void fileLogHeader();

int main (int argc, char *argv[]) {
    int x = 0;
    fileLogHeader();
    while (x < 100) {
        fileLogger(x);
        x++;
    }
}


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
void fileLogHeader(){
    FILE *fp;
    fp = fopen("X2_log.txt", "a");
    char header1[] = "======================================\n";
    char header2[] = "X2 exoskeleton torque and position log\n";
    char header3[] = "======================================\n";
    char header4[]= "LHPos, LHT, LKPos, LKT, RHPos, RHT,RKPos, RKT\n";
    fputs(header1, fp);
    fputs(header2, fp);
    fputs(header3, fp);
    fputs(header4, fp);
    fclose(fp);
}
void fileLogger(int n){
    FILE *fp;
    fp = fopen("X2_log.txt", "a");

// Generate whatever you want logged here, "data" is just an example
    char position [50];
    char torque[50];
    char comma[] = ", ";
    itoa(n, position, 10);
    itoa(n+50, torque, 10);
    n++;
// This lines writes the info in "data" to the file pointer specified
    fputs(position, fp);
    fputs(comma, fp);
    fputs(torque, fp);
    fputs("\n", fp);

// Always remember to close your files
    fclose(fp);
}
