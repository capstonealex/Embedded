#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct timeval tv_read;
    FILE* fp = fopen(argv[1], "rb");

    char newFileName[50];
    strcpy(newFileName,"/media/sdcard1/X2logs/");
    char* oldName=argv[1];
    strcat(newFileName,oldName);
    strcat(newFileName,".txt");

  FILE* fp_write = fopen(newFileName, "w");

    if(fp==NULL)
        printf("File read error\n");
    if(fp_write==NULL)
        printf("File write error\n");

    uint32_t sizeInt=1;
    uint32_t motor1pos=1;
    uint32_t motor2pos=1;
    uint32_t motor3pos=1;
    uint32_t motor4pos=1;
    uint16_t motor1Tor=1;
    uint16_t motor2Tor=1;
    uint16_t motor3Tor=1;
    uint16_t motor4Tor=1;
    long long timesec=1;
    long timeusec=1;

    fprintf(fp_write,"Lhip pos,Lhip torque,Lknee pos,Lknee torque,Rhip pos,Rhip torque,Rknee pos,Rknee torque,\n");
    while(1){
        fread(&timesec, sizeof(timesec), 1, fp);
        fread(&timeusec, sizeof(timeusec), 1, fp);
        fread(&motor1pos, sizeof(sizeInt), 1, fp);
        fread(&motor1Tor, sizeof(sizeInt), 1, fp);
        fread(&motor2pos, sizeof(sizeInt), 1, fp);
        fread(&motor2Tor, sizeof(sizeInt), 1, fp);
        fread(&motor3pos, sizeof(sizeInt), 1, fp);
        fread(&motor3Tor, sizeof(sizeInt), 1, fp);
        fread(&motor4pos, sizeof(sizeInt), 1, fp);
        fread(&motor4Tor, sizeof(sizeInt), 1, fp);

        if(!feof(fp)){
            fprintf(fp_write,"%lld,%ld,%d,%d,%d,%d,%d,%d,%d,%d\n",
                   timesec,timeusec,
                   motor1pos,motor1Tor,
                   motor2pos,motor2Tor,
                   motor3pos,motor3Tor,
                   motor4pos,motor4Tor
            );
        }
        else{
            break;
        }
    }

    fclose(fp);
    fclose(fp_write);

    return 0;
}