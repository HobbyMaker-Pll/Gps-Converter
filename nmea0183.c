#include "include\nmea0183.h"

FieldsQueue* fields = NULL;
int isCheckSum=0;
int newMessage=0;
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

void fillGGA()
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

FieldsQueue* initFieldsQueue()
{
    FieldsQueue* tmp = (FieldsQueue*) malloc(sizeof(FieldsQueue));
    tmp->top = NULL;
    tmp->bottom = NULL;
    tmp->curField = NULL;
    tmp->queueLen = 0;
    return tmp;
}

void inQueue(FieldsQueue* queue, char* field)
{
    LinkedFields* new = (LinkedFields*) malloc(sizeof(LinkedFields));
    new->field = field;
    new->next = NULL;
    
    if(fields->bottom != NULL)
        fields->bottom->next = new;
    
    fields->bottom = new;

    if(fields->top == NULL)
        fields->top=fields->bottom;

    queue->queueLen++;
}

char* deQueue(FieldsQueue* queue)
{
    if(queue->top == NULL) return NULL;

    char* field = malloc(sizeof(queue->top->field));
    *field = '\0';
    strcpy(field, queue->top->field);

    LinkedFields* aux = queue->top->next;

    free(queue->top->field);
    free(queue->top);

    queue->top = aux;

    if (queue->top == NULL) queue->bottom = NULL;

    queue->queueLen--;

    return field;
}

void freeQueue(FieldsQueue* queue)
{
    LinkedFields* aux = queue->top;
    LinkedFields* aux2 = NULL;
    while (aux != NULL)
    {
        aux2 = aux;
        aux = aux->next;
        free(aux2->field);
        free(aux2);
    }
    free(queue->curField);
    free(queue);
}

char handleIncomingNmea0183(char c, int size)
{
    if(fields == NULL) fields = initFieldsQueue();

    if(fields->curField == NULL) 
    {
        fields->curField = (char*) malloc(sizeof(char));
        *(fields->curField) = '\0';
    }
    
    if( c != '\n')
    {

        if (c == ',' || c == '*') // Closing Field
        {
            printf("%s\n", fields->curField);
            inQueue(fields, fields->curField);
            fields->curField = NULL;
            if (c == '*') isCheckSum = 1;

        } else { // Normal Character
            
            fields->curField = (char*) realloc(fields->curField, (sizeof(char) * (strlen(fields->curField)+2) ));
            strncat(fields->curField, &c, size);
        }
        return 0;
    }
    else
    {
        if(strstr(deQueue(fields), GGA_IDENTIFICATOR) != NULL) fillGGA();

        freeQueue(fields);
        fields = NULL;
        return 1;
    }

    return 0;
}

int validateMessage(LinkedFields* field)
{
    // int i, checksum = 0;

    // // Calculate checksum
    // for (i = 1; i < strlen(msg) - 3; i++) {
    //     checksum ^= msg[i];
    // }

    // // Convert checksum to hexadecimal
    // int checksum_hex;
    // sscanf(&msg[strlen(msg) - 2], "%x", &checksum_hex);

    // // Compare calculated checksum with the one in the sentence
    // if (checksum == checksum_hex) {
    //     return 1; // Checksum OK
    // } else {
    //     return 0; // Checksum error
    // }
}