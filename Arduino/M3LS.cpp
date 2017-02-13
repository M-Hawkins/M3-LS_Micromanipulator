/*
M3LS.cpp - An Arduino library for translating high level commands to M3-LS API
           calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#include "Arduino.h"
#include "M3LS.h"

// Class constructor for a three axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS, int Y_SS, int Z_SS){
    // Store pin assignments
    _xSS = X_SS;
    _ySS = Y_SS;
    _zSS = Z_SS;

    // Configure slave select pins as outputs
    pinMode(_xSS, OUTPUT);
    pinMode(_ySS, OUTPUT);
    pinMode(Z_SS, OUTPUT);

    // Disable all stages
    digitalWrite(_xSS, HIGH);
    digitalWrite(_ySS, HIGH);
    digitalWrite(_zSS, HIGH);
}

// Gets and stores the current X, Y, and Z position of the stages
void M3LS::getCurrentPosition(){
    currentPosition[0] = getAxisPosition(_xSS);
    currentPosition[1] = getAxisPosition(_ySS);
    currentPosition[2] = getAxisPosition(_zSS);
}

// Get the current position of a single stage
int M3LS::getAxisPosition(int pin){
    //String response = sendSPICommand("<10>", pin);
    // TODO 
    // Extract relevant info from response...
    return 0;
}

void M3LS::moveToTargetPosition(){
    // TODO
    return;
}