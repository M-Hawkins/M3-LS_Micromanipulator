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
        M3LS(int X_SS, int Y_SS, int Z_SS);
        int currentPosition[3];
        void getCurrentPosition();
        void moveToTargetPosition();
    private:
        int _xSS;
        int _ySS;
        int _zSS;
        int getAxisPosition(int pin);
};

#endif
