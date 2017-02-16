/*
SPIMock.cpp - An Arduino library for testing M3-LS SPI responses
Created by Matthew Hawkins
Copyright info?
*/

#include "SPIMock.h"

// Temporary function for testing SPI signals
String SPIMock::sendSPICommand(String message, int pin){
    return "Test: " + String(pin);
}