/*
M3LS.h - An Arduino library for translating high level commands to M3-LS API
         calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#ifndef M3LS_h
#define M3LS_h

#include "Arduino.h"
#include "SPIMock.h"

class M3LS{
    public:
        // Constructors
        M3LS(int X_SS);
        M3LS(int X_SS, int Y_SS);
        M3LS(int X_SS, int Y_SS, int Z_SS);
        // Variables
        long* currentPosition;
        // Functions
        void getCurrentPosition();
        void moveToTargetPosition();
    private:
        // Variables
        int numAxes;
        int* pins;
        SPIMock spi = SPIMock();
        // Functions
        long getAxisPosition(int pin);
};

#endif
