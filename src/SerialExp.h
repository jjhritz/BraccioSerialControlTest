//
// Created by User on 10/11/2018.
//

#ifndef SERIALEXP_H
#define SERIALEXP_H

#define DEBUG 1

char* receivedChars;
char* tempChars;        // temporary array for use when parsing
boolean newData = false;

char* messageFromPC;
int integerFromPC = 0;

// Constructs the string arrays
void allocateStrings(int txLength, char* externalArray);

// reads from the serial buffer and writes the contents to processing arrays
void recvWithStartEndMarkers(byte txLength = 32, char startMarker = '<', char endMarker = '>');

void emptyReceiveBuffer();



#endif //SERIALEXP_H


