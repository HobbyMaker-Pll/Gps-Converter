#include "include\nmea0183.h"


char incomingMessage[MAX_INCOMINING_MESSAGE_SIZE];

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
    char* field = strsep(&message, DELIMITERS);
    convertStringToUTC(field, &(ggaPackge.time));

    field = strsep(&message, DELIMITERS, &inParse);
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
    if( c != '\n')
    {
        strncat(incomingMessage, &c, 1);
        return 0;
    }
    
    else
    {
        char* data = strdup(incomingMessage);
        char* inParse = data;
        char* identificator = strtok_r(inParse, DELIMITERS, &inParse);

        if(strstr(identificator, GGA_IDENTIFICATOR) != NULL) fillGGA(data, inParse);
        incomingMessage[0] = '\0';
        return 1;
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