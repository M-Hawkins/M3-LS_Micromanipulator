/*
M3LS.h - An Arduino library for translating high level commands to M3-LS API
         calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#ifndef M3LS_h
#define M3LS_h

#include "Arduino.h"

class M3LS{
    public:
        M3LS(int X_SS);
        M3LS(int X_SS, int Y_SS);
        M3LS(int X_SS, int Y_SS, int Z_SS);
        int* currentPosition;
        void getCurrentPosition();
        void moveToTargetPosition();
    private:
        int numAxes;
        int* pins;
        int getAxisPosition(int pin);
};

#endif
