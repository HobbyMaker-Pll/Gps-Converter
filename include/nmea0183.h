#ifndef NMEA_0183_H
#define NMEA_0183_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GGA_IDENTIFICATOR "GGA"
#define GGA_SIZE 15
#define DELIMITERS ","

#define MAX_FIELD_SIZE 100

typedef struct field
{
    char* field;
    struct field* next;
} LinkedFields;

typedef struct _fieldsQueue
{
    LinkedFields* top;
    LinkedFields* bottom;
    char* curField;
    size_t queueLen;
} FieldsQueue;


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
    int isReady;
} ggaMessage;

void fillGGA();
char handleIncomingNmea0183(char c, int size);
int validateMessage(char* msg);
char* deQueue(FieldsQueue* queue);

#endif