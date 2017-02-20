/*
SPIMock.cpp - An Arduino library for testing M3-LS SPI responses
Created by Matthew Hawkins
Copyright info?
*/

#include "SPIMock.h"

// Default empty constructor
SPIMock::SPIMock(){

}

// Mock function for generating M3-LS responses
char* SPIMock::sendSPICommand(char* message, int pin){
    int command = message.substring(1, 3).toInt();
    if (command == 10){
        return "<10 123456 12345678 87654321>";
    } else {
        return "Unrecognized command: " + message + ", " + String(pin);
    }
}