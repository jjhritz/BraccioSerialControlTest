/*
 * Module: Serial Expansion
 * Function: Provides more functions for dealing with the serial communication interface on the Arduino
 *
 * Based on code by Robin2: https://forum.arduino.cc/index.php?topic=396450.0
 */

#include "SerialExp.h"
#include <Arduino.h>

void recvWithStartEndMarkers(byte txLength, char startMarker, char endMarker)
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char rc;

    while (Serial.available() > 0 && newData == false)
    {
        delay(2);
        rc = Serial.read();

        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= txLength)
                {
                    ndx = txLength - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
}


void allocateStrings(int txLength, char* externalArray)
{
    // allocate space for the characters we receive between the start and end markers
    if (receivedChars == NULL)
    {
        receivedChars = (char*) malloc(txLength * sizeof(char));
    }

    // allocate space for the parsing workspace array
    if (tempChars == NULL)
    {
        tempChars = (char*) malloc(txLength * sizeof(char));
    }

    // allocate space for the message
    // if the external array isn't defined, point it at this internal array
    if (messageFromPC == NULL && externalArray == NULL)
    {
        messageFromPC = (char*) malloc(txLength * sizeof(char));
        externalArray = messageFromPC;
    }

    // otherwise, point this internal array at the external one
    else if(messageFromPC == NULL && externalArray != NULL)
    {
        messageFromPC = externalArray;
    }
}


void emptyReceiveBuffer()
{
    while (Serial.available() > 0)
    {
        Serial.read();
    }
}
