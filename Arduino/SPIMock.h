/*
M3LS.h - An Arduino library for translating high level commands to M3-LS API
         calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#ifndef SPIMock_h
#define SPIMock_h

#include <Arduino.h>

class SPIMock{
    public:
        // Constructor
        SPIMock() = default;
        // Function
        String sendSPICommand(String message, int pin);
};

#endif
