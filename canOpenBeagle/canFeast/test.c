////
//// Created by William Campbell on 2019-07-25.
//// Testing function pointer call backs
////
//
///******************************************************************************/
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//int main (/*int argc, char *argv[]*/){
//    char position[]= "200000";
//    char movePos[] = "[1] 2 write 0x607A 0 i32 ";
//    strcat(movePos, position);
////    printf("%s",movePos);
////    setAbsPosSmart(position);
//    return 0;
//}
//
////void setAbsPosSmart(char *position) {
////    char movePos[] = "[1] 2 write 0x607A 0 i32 ";
////    strcat(movePos, position);
////    printf("%s",movePos);
////}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setAbsPosSmart(int position);
void itoa(int value, char* str, int base);
void strreverse(char* begin, char* end);

        int main () {
    int position = 200000;
    setAbsPosSmart(position);

    return(0);
}
void setAbsPosSmart(int position) {
    char pos[50], movePos[50];
    char buffer[50];
    itoa(position,buffer,10);
    printf("Decimal value = %s\n", buffer);
    strcpy(movePos, "[1] 2 write 0x607A 0 i32 ");
    strcpy(pos, buffer);
    strcat(movePos, pos);
//    strcat(movePos, position);
    printf("%s\n",movePos);
}
/**

 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":

 */

void strreverse(char* begin, char* end) {

    char aux;

    while(end>begin)

        aux=*end, *end--=*begin, *begin++=aux;

}

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
