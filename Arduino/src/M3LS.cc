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

// Gets and stores the current position of each stage
long* M3LS::getCurrentPosition(){
    for (int axis = 0; axis < numAxes; axis++){
        currentPosition[axis] = getAxisPosition(pins[axis]);
    }
    return currentPosition;
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
    memcpy(sendChars, "<10>\r", 5);
    sendSPICommand(pin);

    // Allocate space for and generate position value
    char position[8];
    memcpy(position, recvChars + 11, 8);
    return atoi(position);
}

// Move the X axis stage to a given position
void M3LS::moveToTargetXPosition(long target){
    /*
    Send to controller:
        <08>\r
    Receive from controller:
        <10 SSSSSS PPPPPPPP EEEEEEEE>\r
        length: 30 bytes
    */

    // Build command and send it to SPI
    memcpy(sendChars, "<08 ", 4);
    sprintf(sendChars + 4, "%08ld", target);
    memcpy(sendChars + 12, ">\r", 2);
    sendSPICommand(pins[0]);
}

// Temporary, for testing only
void M3LS::sendSPICommand(int pin){
    // Get command
    char comm[2];
    memcpy(comm, sendChars + 1, 2);
    int commNum = atoi(comm);

    // Move to Target command
    if (commNum == 8){
        if (pin == pins[0]){
            // Extract target value and set the current position to it
            // TODO
            currentPosition[0] = 34567890L;
        }
    }

    // Get Status and Position command
    else if (commNum == 10){
        if (pin == pins[0]){
            memcpy(recvChars, "<10 123456 ", 11);
            sprintf(recvChars + 11, "%08ld", currentPosition[0]);
            memcpy(recvChars + 19, " 87654321>\r", 11);
        } else if (pin == pins[1]){
            memcpy(recvChars, "<10 123456 ", 11);
            sprintf(recvChars + 11, "%08ld", currentPosition[1]);
            memcpy(recvChars + 19, " 87654321>\r", 11);
        } else if (pin == pins[2]){
            memcpy(recvChars, "<10 123456 ", 11);
            sprintf(recvChars + 11, "%08ld", currentPosition[2]);
            memcpy(recvChars + 19, " 87654321>\r", 11);
        } else {
            memcpy(recvChars, "<10 123456 00000000 87654321>\r", 30);
        }
    }
    //Return an error flag?
}
