#ifndef NMEA_0183_H
#define NMEA_0183_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GGA_IDENTIFICATOR "GGA"
#define DELIMITERS ","

#define MAX_INCOMINING_MESSAGE_SIZE 300

typedef struct _nmea0183utc
{
    int hour;
    int minute;
    int seconds;
    int miliseconds;
} Nmea0183utc;

typedef struct _nmea0183date
{
    int day;
    int month;
    int year;
} Nmea0183date;

typedef struct _gga
{
    Nmea0183utc time;
    double latitude;
    char latitudeDir;
    double longitute;
    char longitudeDir;
    int gpsQuality;
    int satelliteCount;
    float hdop;
    float orthometricHeight;
    char orthometricHeightUnit;
    float geoidSeparation;
    char geoidSeparationUnit;
    float ageOfDGPS;
    int referenceStation;
    char isReady;
} ggaMessage;

void fillGGA(char* message, char* inParse);
char handleIncomingNmea0183(char c);
int validateMessage(char* msg);

#endif