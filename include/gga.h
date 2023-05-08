#ifndef GGA_H
#define GGA_H

#include "nmea0183.h"

#define GGA_IDENTIFICATOR "GGA"
#define GGA_SIZE 15

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
    int isReady;
} ggaMessage;

void fillGGA(FieldsQueue* fields);

#endif