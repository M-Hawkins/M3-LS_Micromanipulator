#include "M3LS.h"

int xpin = 4;
int ypin = 2;
int zpin = 3;
int xjoystickPin = A6;
int yjoystickPin = A5;
int zjoystickPin = A7;

M3LS *myM3LS;

void setup(){
    Serial.begin(9600);
    Serial.println("Testing M3LS Joystick movement");
    myM3LS = new M3LS(xpin, ypin, zpin);
    Serial.println("Done instantiating M3LS");
    pinMode(xjoystickPin, INPUT);
    pinMode(yjoystickPin, INPUT);
    pinMode(zjoystickPin, INPUT);
}

void loop(){
    int nextPosx = map(analogRead(xjoystickPin)/8, 0, 127, 500, 11500);
    int nextPosy = map(analogRead(yjoystickPin)/8, 0, 127, 500, 11500);
    int nextPosz = map(analogRead(zjoystickPin)/8, 0, 127, 500, 11500);
    Serial.print("Current Pos: ");
    myM3LS->getCurrentPosition();
    Serial.println(myM3LS->currentPosition[0]);
    Serial.println(myM3LS->currentPosition[1]);
    Serial.println(myM3LS->currentPosition[2]);
    Serial.print("Moving to ");
    Serial.println(nextPosx);
    Serial.println(nextPosy);
    Serial.println(nextPosz);
    myM3LS->updatePosition(nextPosx, nextPosy, nextPosz);
    delay(100);
}
