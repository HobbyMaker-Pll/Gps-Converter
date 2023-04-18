#ifndef NMEA_0183_H
#define NMEA_0183_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_SIZE 10
#define MAX_FIELDS_SIZE 20

#define ZDA_FIELDS_SIZE 8

typedef struct _nmea0183Type
{ 
    char* indentifier;
    char** fields;
    int fieldsSize;
} nmea0183Type;

typedef struct _nmea0183UTC
{
    int hour;
    int minute;
    int seconds;
} nmea0183UTC;

enum {
    NEMA0183_STRING,
    NMEA0183_INT,
    NMEA0183_FLOAT,
    NMEA0183_UTC
};

enum {
    ZDA_ID,
    ZDA_UTC,
    ZDA_DAY,
    ZDA_MONTH,
    ZDA_YEAR,
    ZDA_HOUR_OFFSET,
    ZDA_MINUTE_OFFSET,
    ZDA_CHECKSUM
};

nmea0183UTC stringToUTC(char*);
nmea0183Type* initNmea0183Type(char* identifier, int fieldsSize);
int validateMessage(char* msg);

#endif