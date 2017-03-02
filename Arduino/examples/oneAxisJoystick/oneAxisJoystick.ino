#include "M3LS.h"

int xpin = 4;
int joystickPin = 6;

M3LS *myM3LS;

void setup(){
    Serial.begin(9600);
    Serial.println("Testing M3LS Joystick movement");
    myM3LS = new M3LS(xpin);
    Serial.println("Done instantiating M3LS");
    pinMode(joystickPin, INPUT);
}

void loop(){
    int nextPos = map(analogRead(joystickPin), 0, 1023, 500, 11500);
    Serial.print("Current Pos: ");
    Serial.println(myM3LS->currentPosition[0]);
    Serial.print("Moving to ");
    Serial.println(nextPos);
    delay(1000);
}
