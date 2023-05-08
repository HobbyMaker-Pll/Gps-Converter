#ifndef NMEA_0183_H
#define NMEA_0183_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void convertStringToUTC(char* s, Nmea0183utc* time);
char handleIncomingNmea0183(char* c, int size);
int validateMessage(LinkedFields* msg);
char* deQueue(FieldsQueue* queue);
void inQueue(FieldsQueue* queue, char* field);
void freeQueue(FieldsQueue* queue);

#endif