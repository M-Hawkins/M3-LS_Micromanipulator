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
    currentControlMode = position;

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
    currentControlMode = position;

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
    currentControlMode = position;

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

// Default single axis move command
void M3LS::moveToTargetPosition(long target0){
    moveToTargetPosition(target0, X);
}

// Move the specified axis to the target position
void M3LS::moveToTargetPosition(long target0, Axes axis){
    setTargetPosition(target0);
    sendSPICommand(pins[axis]);
}

// Default two axis move command
void M3LS::moveToTargetPosition(long target0, long target1){
    moveToTargetPosition(target0, target1, XY);
}

// Move the specified axes to the target positions
void M3LS::moveToTargetPosition(long target0, long target1, Axes axis){
    moveToTargetPosition(target0, target1, 0L, axis);
}

// Default three axis move command
void M3LS::moveToTargetPosition(long target0, long target1, long target2){
    moveToTargetPosition(target0, target1, target2, XYZ);   
}

// Move the specified axes to the target positions
void M3LS::moveToTargetPosition(long target0, long target1, long target2, Axes axis){
    switch(axis)
    {
        case X   :  setTargetPosition(target0);
                    sendSPICommand(pins[0]);
                    break;
        case Y   :  setTargetPosition(target1);
                    sendSPICommand(pins[1]);
                    break;
        case Z   :  setTargetPosition(target2);
                    sendSPICommand(pins[2]);
                    break;
        case XY  :  setTargetPosition(target0);
                    sendSPICommand(pins[0]);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1]);
                    break;
        case XZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[0]);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2]);
                    break;
        case YZ  :  setTargetPosition(target1);
                    sendSPICommand(pins[1]);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2]);
                    break;
        case XYZ :  setTargetPosition(target0);
                    sendSPICommand(pins[0]);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1]);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2]);
                    break;
    }
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

// Store the current position as the home position
void M3LS::setHome(){
    getCurrentPosition();
    memcpy(homePosition, currentPosition, numAxes);
}

// Temporary, for testing only
void M3LS::sendSPICommand(int pin){
    // Get command
    char comm[2];
    memcpy(comm, sendChars + 1, 2);
    int commNum = atoi(comm);

    // Move to Target command
    if (commNum == 8){
        // Extract the target position
        char target[8];
        memcpy(target, sendChars + 4, 8);
        long targetNum = atoi(target);

        // Set appropriate axis position to the target value
        if (pin == pins[0]){
            currentPosition[0] = targetNum;
        } else if (pin == pins[1]){
            currentPosition[1] = targetNum;
        } else if (pin == pins[2]){
            currentPosition[2] = targetNum;
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
            memcpy(recvChars, "<10 123456 88888888 87654321>\r", 30);
        }
    }
    //Return an error flag?
}
