#include "include\main.h"

int main(char *arg, char **argv)
{
    FILE *fp;
    char c;
    char ret;

    // Opens file descriptor for nmea file
    fp = fopen("../resources/output.nmea", "r");

    // checks if file descriptor has opened correctly
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (1)
    {
        c = fgetc(fp);
        if (c == EOF) break;

        //parse each character to nmea handle method
        ret = handleIncomingNmea0183(c); 

        if(ret != 1) continue;
    }
    
    // closes file descriptor
    fclose(fp);
    return 0;
}

