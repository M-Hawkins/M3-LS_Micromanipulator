/*
UnitTest.ino - A collection of unit tests for the custom M3-LS library
Created by Matthew Hawkins
Copyright info?

Utilizes ArduinoUnit, available from:
https://github.com/mmurdoch/arduinounit/
*/
#include <ArduinoUnit.h>
#include "M3LS.h"

test(ok) {
  int x=3;
  int y=3;
  assertEqual(x,y);
}

test(bad){
  int x=3;
  int y=3;
  assertNotEqual(x,y);
}

void setup(){
    Serial.begin(9600);
}

void loop(){
    Test::run();
}