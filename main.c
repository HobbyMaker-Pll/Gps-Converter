#include "include\main.h"

#define MAX_LINE_SIZE 100
#define MAX_FIELD_SIZE 20

int main(char *arg, char **argv)
{
    FILE *fp;

    nmea0183Type* zdaPackge;
    zdaPackge = initNmea0183Type("ZDA", ZDA_FIELDS_SIZE);


    char line[MAX_LINE_SIZE];
    char *token;
    char fields[MAX_FIELD_SIZE][MAX_LINE_SIZE];

    fp = fopen("../resources/output.nmea", "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while(fgets(line, sizeof(line), fp) != NULL) {
        token = strtok(line, ",*");
        if(!validateMessage(line)) continue;

        int fieldCount = 0;
        int isIdentifier = 0;

        while(token != NULL) {
            strcpy((fields[fieldCount]), token);
            printf("%s", fields[fieldCount]);
            token = strtok(NULL, ",*");
            fieldCount++;
        }
    }

    fclose(fp);
    return 0;
}

