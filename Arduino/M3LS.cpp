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
    pins = new int[numAxes]{X_SS};
    currentPosition = new long[numAxes];

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
    pins = new int[numAxes]{X_SS, Y_SS};
    currentPosition = new long[numAxes];

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
    pins = new int[numAxes]{X_SS, Y_SS, Z_SS};
    currentPosition = new long[numAxes];

    // Initialize all pins as unselected outputs
    for (int pin = 0; pin < numAxes; pin++){
        pinMode(pins[pin], OUTPUT);
        digitalWrite(pins[pin], HIGH);
    }
}

// Gets and stores the current position of each stage
void M3LS::getCurrentPosition(){
    for (int axis = 0; axis < numAxes; axis++){
        currentPosition[axis] = getAxisPosition(pins[axis]);
    }
}

// Get the current position of a single stage
long M3LS::getAxisPosition(int pin){
    String response = spi.sendSPICommand("<10>", pin);
    return response.substring(11, 19).toInt();
}

void M3LS::moveToTargetPosition(){
    // TODO
    return;
}
