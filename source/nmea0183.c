#include "nmea0183.h"
#include "gga.h"

FieldsQueue fields = {NULL, NULL, 0};
char curField [MAX_FIELD_SIZE];
char* isFinishing=NULL; 
char* isNewMessage=NULL;

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
}

void inQueue(FieldsQueue* queue, char* field)
{
    LinkedFields* new = (LinkedFields*) malloc(sizeof(LinkedFields));
    new->field = field;
    new->next = NULL;
    
    if(queue->bottom != NULL)
        queue->bottom->next = new;
    
    queue->bottom = new;

    if(queue->top == NULL)
        queue->top=queue->bottom;

    queue->queueLen++;
}

char* deQueue(FieldsQueue* queue)
{
    if(queue->top == NULL) return NULL;

    char* field = queue->top->field;
    LinkedFields* aux = queue->top->next;

    free(queue->top);

    queue->top = aux;

    if (queue->top == NULL) queue->bottom = NULL;

    queue->queueLen--;

    return field;
}

char handleIncomingNmea0183(char* c, int size)
{  
    if ( (strlen(curField)+size+1) > MAX_FIELD_SIZE) // new incoming char buffer exceeded max nmea size
    {
        curField[0]='\0'; 
        return 0;
    }

    strncat(curField, c, size);

    
    isNewMessage = strchr(curField, '$');

    if( isFinishing == NULL)
    {
        isFinishing = strchr(curField, '\n');
        return 0;
    }
    

    
    if (isFinishing != NULL && isNewMessage != NULL)
    {
        char* identificator = deQueue(&fields);

        #ifdef GGA_H
        if(strstr(identificator, GGA_IDENTIFICATOR) != NULL) fillGGA(&fields);
        #endif

        free(identificator);
        freeQueue(&fields);
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