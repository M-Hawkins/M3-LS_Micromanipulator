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
        // Constructors
        M3LS(int X_SS);
        M3LS(int X_SS, int Y_SS);
        M3LS(int X_SS, int Y_SS, int Z_SS);
        // Variables
        long currentPosition[3];
        // Functions
        long* getCurrentPosition();
        void moveToTargetXPosition(long target);
    private:
        // Variables
        int numAxes;
        int pins[3];
        char sendChars[50];
        char recvChars[50];
        // Functions
        long getAxisPosition(int pin);
        void sendSPICommand(int pin);
};

#endif
