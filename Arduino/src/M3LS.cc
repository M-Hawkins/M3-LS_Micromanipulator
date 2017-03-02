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
    setupSPI();
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
    setupSPI();
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
    setupSPI();
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

// Default three axis move command
void M3LS::moveToTargetPosition(long target){
    moveToTargetPositionX(target);
}

// Move the X axis stage to a given position
void M3LS::moveToTargetPositionX(long target){
    setTargetPosition(target);
    sendSPICommand(pins[0]);
}

// Move the Y axis stage to a given position
void M3LS::moveToTargetPositionY(long target){
    setTargetPosition(target);
    sendSPICommand(pins[1]);
}

// Move the Z axis stage to a given position
void M3LS::moveToTargetPositionZ(long target){
    setTargetPosition(target);
    sendSPICommand(pins[2]);
}

// Default two axes move command
void M3LS::moveToTargetPosition(long targetX, long targetY){
    moveToTargetPositionXY(targetX, targetY);
}

// Move the X and Y stages to a given position
void M3LS::moveToTargetPositionXY(long targetX, long targetY){
    setTargetPosition(targetX);
    sendSPICommand(pins[0]);
    setTargetPosition(targetY);
    sendSPICommand(pins[1]);
}

// Move the X and Z stages to a given position
void M3LS::moveToTargetPositionXZ(long targetX, long targetZ){
    setTargetPosition(targetX);
    sendSPICommand(pins[0]);
    setTargetPosition(targetZ);
    sendSPICommand(pins[2]);
}

// Move the Y and Z stages to a given position
void M3LS::moveToTargetPositionYZ(long targetY, long targetZ){
    setTargetPosition(targetY);
    sendSPICommand(pins[1]);
    setTargetPosition(targetZ);
    sendSPICommand(pins[2]);
}

// Default three axes move command
void M3LS::moveToTargetPosition(long targetX, long targetY, long targetZ){
    moveToTargetPositionXYZ(targetX, targetY, targetZ);
}

// Move the X, Y, and Z stages to a given position
void M3LS::moveToTargetPositionXYZ(long targetX, long targetY, long targetZ){
    setTargetPosition(targetX);
    sendSPICommand(pins[0]);
    setTargetPosition(targetY);
    sendSPICommand(pins[1]);
    setTargetPosition(targetZ);
    sendSPICommand(pins[2]);
}

// Set the target position to move to
void M3LS::setTargetPosition(long target){
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
}

int M3LS::sendSPICommand(int pin, char *command, int length){
    memset(recvchars, 0, 100);
    digitalWrite(pin, LOW);
    for(int i=0; i<length; i++){
        SPI.transfer(command[i]);
        // Minimum delay time: 60 microseconds between SPI transfers.
        delayMicroseconds(60);
    }

    int j = 0;
    while('<' != (buf[j] = SPI.transfer(IN_PROGRESS))){
        delayMicroseconds(60);
    }
    while(DONE != (buf[++j] = SPI.transfer(IN_PROGRESS))){
        delayMicroseconds(60);
        if(j > 99) return -1;
    }
    digitalWrite(pin, HIGH);
    SPI.endTransaction();
    return 0;
}

void M3LS::setupSPI(){
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
}
