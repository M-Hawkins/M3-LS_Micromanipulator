#include "M3LS.h"

int xpin = 3;
int ypin = 2;
int zpin = 4;
int xjoystickPin = A5;
int yjoystickPin = A6;
int zjoystickPin = A4;

int returnHomePin = 6;
int setHomePin = 7;
int boundsUpPin = 8;
int boundsDownPin = 9;
int holdPin = 10;
int switchPin = 11;

int switchVal = 0;
int prevVal = 0;

bool wasPressed[5] = {0};

M3LS *myM3LS;

void setup(){
  Serial.begin(9600);
  Serial.println("Testing M3LS Joystick movement");
  myM3LS = new M3LS(xpin, ypin, zpin);
  Serial.println("Done instantiating M3LS");

  pinMode(xjoystickPin, INPUT);
  pinMode(yjoystickPin, INPUT);
  pinMode(zjoystickPin, INPUT);
  pinMode(returnHomePin, INPUT);
  pinMode(setHomePin, INPUT);
  pinMode(boundsUpPin, INPUT);
  pinMode(boundsDownPin, INPUT);
  pinMode(holdPin, INPUT);
  pinMode(switchPin, INPUT);

  myM3LS->setControlMode(M3LS::open);
  myM3LS->setControlMode(M3LS::position);
}

void loop(){
  //TODO: Set wasPressed to false on else
  if (digitalRead(returnHomePin)){
    if (!wasPressed[0]){
      myM3LS->returnHome();
      wasPressed[0] = true;
      Serial.println("Return Home");
    }
  } else {
    wasPressed[0] = false;
  }

  if (digitalRead(setHomePin)){
    if (!wasPressed[1]){
      myM3LS->setHome();
      wasPressed[1] = true;
      Serial.println("Set Home");
    }
  } else {
    wasPressed[1] = false;
  }

  if (digitalRead(boundsUpPin)){
    if (!wasPressed[2]){
      myM3LS->boundsLarger();
      wasPressed[2] = true;
      Serial.println("Sens Up");
    }
  } else {
    wasPressed[2] = false;
  }

  if (digitalRead(boundsDownPin)){
    if (!wasPressed[3]){
      myM3LS->boundsSmaller();
      wasPressed[3] = true;
      Serial.println("Sens Down");
    }
  } else {
    wasPressed[3] = false;
  }

  if (digitalRead(holdPin)){
    if (!wasPressed[4]){
      if (myM3LS->currentControlMode == M3LS::hold){
        myM3LS->setControlMode(M3LS::position);
        Serial.println("Hold OFF");
      } else {
        myM3LS->setControlMode(M3LS::hold);
        Serial.println("Hold ON");
      }
      wasPressed[4] = true;
    }
  } else {
    wasPressed[4] = false;
  }

  switchVal = digitalRead(switchPin);
  if (switchVal != prevVal){
    if(switchVal){
      Serial.println("Switching to position mode");
      myM3LS->setControlMode(M3LS::position);
    } else {
      Serial.println("Switching to velocity mode");
      myM3LS->setControlMode(M3LS::velocity);
    }
  }
  prevVal = switchVal;

  myM3LS->updatePosition(1024-analogRead(xjoystickPin), 1024-analogRead(yjoystickPin), 1024-analogRead(zjoystickPin));
  // myM3LS->getCurrentPosition();
  // Serial.print(myM3LS->currentPosition[0]); Serial.print(" ");
  // Serial.println(myM3LS->currentPosition[1]);
  delay(50);
}
