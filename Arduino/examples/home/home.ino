#include "M3LS.h"

int xpin = 2;
int ypin = 3;
int zpin = 4;
int xjoystickPin = A5;
int yjoystickPin = A6;
int zjoystickPin = A7;

int homeCounter = 0;

M3LS *myM3LS;

void setup(){
    Serial.begin(9600);
    Serial.println("Testing M3LS Joystick movement");
    myM3LS = new M3LS(xpin, ypin, zpin);
    Serial.println("Done instantiating M3LS");
    pinMode(xjoystickPin, INPUT);
    pinMode(yjoystickPin, INPUT);
    pinMode(zjoystickPin, INPUT);
    myM3LS->setControlMode(M3LS::open);
    myM3LS->setControlMode(M3LS::position);
}

void loop(){
    homeCounter++;
    if (homeCounter == 200){
      myM3LS->getCurrentPosition();
      Serial.println("\n\n\nSetting home position to:");
      Serial.println(myM3LS->currentPosition[0]);
      Serial.println(myM3LS->currentPosition[1]);
      Serial.println(myM3LS->currentPosition[2]);
      myM3LS->setHome();
      Serial.println("\nActual Home");
      Serial.println(myM3LS->homePosition[0]);
      Serial.println(myM3LS->homePosition[1]);
      Serial.println(myM3LS->homePosition[2]);
    }
    if (homeCounter > 400){
      myM3LS->returnHome();
      delay(1000);
      myM3LS->getCurrentPosition();
      Serial.println("\nReturned to:");
      Serial.println(myM3LS->currentPosition[0]);
      Serial.println(myM3LS->currentPosition[1]);
      Serial.println(myM3LS->currentPosition[2]);
      homeCounter = 0;
    } else { 
      int nextPosx = map((1023 - analogRead(xjoystickPin))/8, 0, 127, 500, 11500);
      int nextPosy = map((1023 - analogRead(yjoystickPin))/8, 0, 127, 500, 11500);
      int nextPosz = map(analogRead(zjoystickPin)/8, 0, 127, 500, 11500);
      myM3LS->updatePosition(nextPosx, nextPosy, nextPosz);
    }
    delay(100);
}
