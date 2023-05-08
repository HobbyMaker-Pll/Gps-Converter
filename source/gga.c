#include "gga.h"

ggaMessage ggaPackge;

void fillGGA(FieldsQueue* fields)
{
    char* field = deQueue(fields);
    convertStringToUTC(field, &(ggaPackge.time));
    free(field);

    field = deQueue(fields);
    ggaPackge.latitude = strtod(field, NULL);
    free(field);

    field = deQueue(fields);
    ggaPackge.latitudeDir = *field;
    free(field);

    field = deQueue(fields);
    ggaPackge.longitute = strtod(field, NULL);
    free(field);

    field = deQueue(fields);
    ggaPackge.longitudeDir = *field;
    free(field);

    field = deQueue(fields);
    ggaPackge.gpsQuality = atoi(field);
    free(field);

    field = deQueue(fields);
    ggaPackge.satelliteCount = atoi(field);
    free(field);

    field = deQueue(fields);
    ggaPackge.hdop = strtof(field, NULL);
    free(field);

    field = deQueue(fields);
    ggaPackge.orthometricHeight = strtof(field, NULL);
    free(field);

    field = deQueue(fields);
    ggaPackge.orthometricHeightUnit = *field;
    free(field);

    field = deQueue(fields);
    ggaPackge.geoidSeparation = strtof(field, NULL);
    free(field);

    field = deQueue(fields);
    ggaPackge.geoidSeparationUnit = *field;
    free(field);

    field = deQueue(fields);
    ggaPackge.ageOfDGPS = strtof(field, NULL);
    free(field);

    field = deQueue(fields);
    ggaPackge.referenceStation = atoi(field);
    free(field);

}