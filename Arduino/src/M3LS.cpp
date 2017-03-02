/*
M3LS.cpp - An Arduino library for translating high level commands to M3-LS API
           calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#include "M3LS.h"

#define DEBUG   //If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.
#ifdef DEBUG    //Macros are usually in all capital letters.
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)     //now defines a blank line
  #define DPRINTLN(...)   //now defines a blank line
#endif

// Constructors
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
    setupSPI();
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
    setupSPI();
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
    setupSPI();
}

// Public functions
// Sets the current control mode to the new mode
void M3LS::setControlMode(ControlMode newMode){
    currentControlMode = newMode;
}

// Default method for updating the needle's position
void M3LS::updatePosition(long xPos, long yPos, long zPos){
    updatePosition(xPos, yPos, zPos, XYZ);
}

void M3LS::updatePosition(long xPos){
    moveToTargetPosition(xPos, X);
}

// Update the needle's position based upon current mode and joystick inputs
void M3LS::updatePosition(long xPos, long yPos, long zPos, Axes axis){
    switch(currentControlMode)
    {
        case position : moveToTargetPosition(xPos, yPos, zPos, axis);
                        break;
        case velocity : break;
    }
}

// Set the controller's sensitivity to a new value
void M3LS::setSensitivity(int speed){
    /*
    Send to controller:
        <40 SSSSSS CCCCCC AAAAAA IIII>
    Receive from controller:
        <40>
    */

    // Build command ~and send it to SPI
    memcpy(sendChars, "<40 ", 4);
    sprintf(sendChars + 4, "%06x", speed);
    memcpy(sendChars + 10, "000033 0000CD 0001>\r", 20);
}

// Store the current position as the home position
void M3LS::setHome(){
    getCurrentPosition();
    memcpy(homePosition, currentPosition, numAxes * sizeof(long));
}

// Return to the stored home position
void M3LS::returnHome(){
    // Store current mode
    // ControlMode previousMode = currentControlMode;
    // Switch to closed loop mode
    // Raise Z axis
    // Move X and Y to target
    moveToTargetPosition(homePosition[0], homePosition[1], XY);
    // Restored previous mode
    // setControlMode(previousMode);
}

// Private Functions
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
    memcpy(sendChars, "<10>\r", 5);
    sendSPICommand(pin, 5);

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
    sendSPICommand(pins[axis], 14);
}

// Default two axis move command
void M3LS::moveToTargetPosition(long target0, long target1){
    moveToTargetPosition(target0, target1, XY);
}

// Move the specified axes to the target positions
void M3LS::moveToTargetPosition(long target0, long target1, Axes axis){
    switch(axis)
    {
        case XY  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    break;
        case XZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[2], 14);
                    break;
        case YZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[1], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[2], 14);
                    break;
    }
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
                    sendSPICommand(pins[0], 14);
                    break;
        case Y   :  setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    break;
        case Z   :  setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
        case XY  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    break;
        case XZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
        case YZ  :  setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
        case XYZ :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
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

int M3LS::sendSPICommand(int pin, int length){
    memset(recvChars, 0, 100);
    digitalWrite(pin, LOW);
    for(int i=0; i<length; i++){
        SPI.transfer(sendChars[i]);
        // Minimum delay time: 60 microseconds between SPI transfers.
        delayMicroseconds(60);
    }

    int j = 0;
    while('<' != (recvChars[j] = SPI.transfer(IN_PROGRESS))){
        delayMicroseconds(60);
    }
    while(DONE != (recvChars[++j] = SPI.transfer(IN_PROGRESS))){
        delayMicroseconds(60);
        if(j >= 99) return -1;
    }
    DPRINT("Received from M3-LS:");
    DPRINTLN(recvChars);
    DPRINT("Took ");
    DPRINT(j-1);
    DPRINTLN(" iterations.\n");
    digitalWrite(pin, HIGH);
    SPI.endTransaction();
    return 0;
}

void M3LS::setupSPI(){
    // #ifdef DEBUG
    //     Serial.begin(9600);
    // #endif
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
}