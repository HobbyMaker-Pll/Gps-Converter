#include "include\nmea0183.h"

nmea0183UTC stringToUTC(char* info)
{

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

nmea0183Type* initNmea0183Type(char* identifier, int fieldsSize)
{
    // Allocates memory for the msg type and its fields
    nmea0183Type* msg = malloc(sizeof(nmea0183Type));
    msg->fields = malloc( (sizeof(char*) * fieldsSize) );

    //defines the packge size
    msg->fieldsSize = fieldsSize;

    // defines the packge indentifier
    msg->indentifier = identifier;

    return msg;
}