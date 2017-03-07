#include "M3LS.h"

int xpin = 2;
int ypin = 3;
int zpin = 4;
int xjoystickPin = A6;
int yjoystickPin = A5;
int zjoystickPin = A4;

int returnHomePin = 6;
int setHomePin = 7;
int boundsUpPin = 8;
int boundsDownPin = 9;
int holdPin = 10;
int switchPin = 11;

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
  
  myM3LS->setControlMode(M3LS::open);
  myM3LS->setControlMode(M3LS::position);
}

void loop(){
  //TODO: Set wasPressed to false on else
  if (digitalRead(returnHomePin)){
    if (!wasPressed[0]){
      myM3LS->returnHome();
      wasPressed[0] = true;
    }
  } else {
    wasPressed[0] = false;
  }
  
  if (digitalRead(setHomePin)){
    if (!wasPressed[1]){
      myM3LS->setHome();
      wasPressed[1] = true;
    }
  } else {
    wasPressed[1] = false;
  }
  
  if (digitalRead(boundsUpPin)){
    if (!wasPressed[2]){
      myM3LS->boundsLarger();
      wasPressed[2] = true;
    }
  } else {
    wasPressed[2] = false;
  }
  
  if (digitalRead(boundsDownPin)){
    if (!wasPressed[3]){
      myM3LS->boundsSmaller();
      wasPressed[3] = true;
    }
  } else {
    wasPressed[3] = false;
  }
  
  if (digitalRead(holdPin)){
    if (!wasPressed[4]){
      if (myM3LS.currentControlMode == hold){
        myM3LS->setControlMode(M3LS::position);
      } else {
        myM3LS->setControlMode(M3LS::hold);
      }
      wasPressed[4] = true;
    }
  } else {
    wasPressed[4] = false;
  }

  myM3LS->updatePosition(1024-analogRead(xjoy), 1024-analogRead(yjoy), 1024-analogRead(zjoy));
  delay(50);
}
