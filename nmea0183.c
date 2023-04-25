#include "include\nmea0183.h"

char** fields = NULL;
int fieldsCount;

ggaMessage ggaPackge;

void convertStringToUTC(char* s, Nmea0183utc* time)
{
    sscanf(
        s, 
        "%2d%2d%2d.%d", 
        &(time->hour), 
        &(time->minute), 
        &(time->seconds), 
        &(time->miliseconds)
    );
}

void fillGGA(char* message, char* inParse)
{
    char* field = NULL;
    convertStringToUTC(field, &(ggaPackge.time));

    //field = strsep(&message, DELIMITERS, &inParse);
    ggaPackge.latitude = strtod(field, NULL);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.latitudeDir = *field;

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.longitute = strtod(field, NULL);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.longitudeDir = *field;

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.gpsQuality = atoi(field);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.satelliteCount = atoi(field);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.hdop = strtof(field, NULL);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.orthometricHeight = strtof(field, NULL);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.orthometricHeightUnit = *field;

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.geoidSeparation = strtof(field, NULL);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.geoidSeparationUnit = *field;

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.ageOfDGPS = strtof(field, NULL);

    field = strtok_r(inParse, DELIMITERS, &inParse);
    ggaPackge.referenceStation = atoi(field);
}

char handleIncomingNmea0183(char c)
{
    if (fieldsCount == 0)
    {
        fields = (char**) realloc(fields,sizeof(char*));
        fields[0] = (char*) realloc(&(fields[0]), sizeof(char)); 
        fields[0][0] = '\0';
        fieldsCount++;
    }
    
    if( c != '\n')
    {
        
        if (c == ',' || c == '*')
        {
            
            fields = (char**) realloc(fields, sizeof(char*)*(fieldsCount+1));

            if(fields == NULL) {perror("fields not allocated"); exit(1);}

            char* tmp = (char*) realloc(&(fields[fieldsCount]), sizeof(char));
            fields[fieldsCount] = tmp; 
            fields[fieldsCount][0] = '\0';

            printf("%s\n", fields[fieldsCount]);
            fieldsCount++;

        } else {
            fields[fieldsCount] = (char*) realloc(&(fields[fieldsCount]), sizeof(char)*(strlen(fields[fieldsCount])+2));
            strncat(fields[fieldsCount], &c, 1);
            printf("%s\n", fields[fieldsCount]);
        }
        return 0;
    }
    
    else
    {
        // char* data = strdup(incomingMessage);
        // char* inParse = data;
        // char* identificator = strtok_r(inParse, DELIMITERS, &inParse);

        // if(strstr(identificator, GGA_IDENTIFICATOR) != NULL) fillGGA(data, inParse);
        // incomingMessage[0] = '\0';
        // return 1;
    }
}

int validateMessage(char* msg)
{
    int i, checksum = 0;

    // Calculate checksum
    for (i = 1; i < strlen(msg) - 3; i++) {
        checksum ^= msg[i];
    }

    // Convert checksum to hexadecimal
    int checksum_hex;
    sscanf(&msg[strlen(msg) - 2], "%x", &checksum_hex);

    // Compare calculated checksum with the one in the sentence
    if (checksum == checksum_hex) {
        return 1; // Checksum OK
    } else {
        return 0; // Checksum error
    }
}