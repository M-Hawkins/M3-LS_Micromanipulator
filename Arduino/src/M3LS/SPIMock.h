/*
M3LS.h - An Arduino library for translating high level commands to M3-LS API
         calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#ifndef SPIMock_h
#define SPIMock_h

#ifndef TESTING
#include "Arduino.h"
#endif

class SPIMock{
    public:
        // Constructor
        SPIMock();
        // Function
        char* sendSPICommand(char* message, int pin);
};

#endif
