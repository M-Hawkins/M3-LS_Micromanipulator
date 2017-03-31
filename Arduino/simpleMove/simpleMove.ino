/*
This sketch simply moves back and forth: from encoder
counts 500 to 11500
*/

#include "M3LS.h"

int xpin = 3;
int ypin = 2;
int zpin = 4;

M3LS *myM3LS;

void setup(){
    Serial.begin(9600);
    Serial.println("Testing M3LS Movement");
    Serial.println("About to construct M3LS object:");
    myM3LS = new M3LS(xpin, ypin, zpin);
    Serial.println("DONE instantiating object");
    delay(1000);
}

void loop(){
    Serial.println("Updating position to: 500");
    myM3LS->calibrateReverse();
    myM3LS->updatePosition(0, 0, 0);
    delay(10);
    myM3LS->updatePosition(0, 0, 0);
    delay(10);
    myM3LS->updatePosition(0, 0, 0);
    delay(2500);
    myM3LS->getCurrentPosition();
    Serial.print("Position: ");
    Serial.print(myM3LS->currentPosition[0]);
    Serial.print(" ");
    Serial.print(myM3LS->currentPosition[1]);
    Serial.print(" ");
    Serial.println(myM3LS->currentPosition[2]);

    Serial.println("Updating position to: 11500");
    myM3LS->calibrateForward();
    myM3LS->updatePosition(255, 255, 255);
    delay(10);
    myM3LS->updatePosition(255, 255, 255);
    delay(10);
    myM3LS->updatePosition(255, 255, 255);
    delay(2500);
    myM3LS->getCurrentPosition();
    Serial.print("Position: ");
    Serial.print(myM3LS->currentPosition[0]);
    Serial.print(" ");
    Serial.print(myM3LS->currentPosition[1]);
    Serial.print(" ");
    Serial.println(myM3LS->currentPosition[2]);
}
