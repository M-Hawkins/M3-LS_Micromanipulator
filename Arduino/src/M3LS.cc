/*
M3LS.cpp - An Arduino library for translating high level commands to M3-LS API
           calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#include "M3LS.h"

// Class constructor for a one axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS){
    // Initialize variables
    numAxes = 1;
    pins[0] = X_SS;

    // Initialize all pins as unselected outputs
    for (int pin = 0; pin < numAxes; pin++){
        pinMode(pins[pin], OUTPUT);
        digitalWrite(pins[pin], HIGH);
    }
}

// Class constructor for a two axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS, int Y_SS){
    // Initialize variables
    numAxes = 2;
    pins[0] = X_SS;
    pins[1] = Y_SS;

    // Initialize all pins as unselected outputs
    for (int pin = 0; pin < numAxes; pin++){
        pinMode(pins[pin], OUTPUT);
        digitalWrite(pins[pin], HIGH);
    }
}

// Class constructor for a three axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS, int Y_SS, int Z_SS){
    // Initialize variables
    numAxes = 3;
    pins[0] = X_SS;
    pins[1] = Y_SS;
    pins[2] = Z_SS;

    // Initialize all pins as unselected outputs
    for (int pin = 0; pin < numAxes; pin++){
        pinMode(pins[pin], OUTPUT);
        digitalWrite(pins[pin], HIGH);
    }
}
// 
// Gets and stores the current position of each stage
void M3LS::getCurrentPosition(){
    for (int axis = 0; axis < numAxes; axis++){
        currentPosition[axis] = getAxisPosition(pins[axis]);
    }
}

// Get the current position of a single stage
long M3LS::getAxisPosition(int pin){
    /*
    Send to controller:
        <10>\r
    Receive from controller:
        <10 SSSSSS PPPPPPPP EEEEEEEE>\r
        length: 30 bytes
    */
    // Build command and send it to SPI
    static char sendMessage[] = "<10>\r";
    memcpy(sendChars, sendMessage, 5);
    sendSPICommand(pin);

    // Allocate space for return message
    char position[8];
    memcpy(position, recvChars + 11, 8);
    return atoi(position);
}

void M3LS::moveToTargetPosition(){
    // TODO
    return;
}

// Temporary, for testing only
void M3LS::sendSPICommand(int pin){
    if (pin == pins[0]){
        memcpy(recvChars, "<10 123456 11111234 87654321>\r", 30);
    } else if (pin == pins[1]){
        memcpy(recvChars, "<10 123456 22221234 87654321>\r", 30);
    } else if (pin == pins[2]){
        memcpy(recvChars, "<10 123456 33331234 87654321>\r", 30);
    } else {
        memcpy(recvChars, "<10 123456 00000000 87654321>\r", 30);
    }
}
