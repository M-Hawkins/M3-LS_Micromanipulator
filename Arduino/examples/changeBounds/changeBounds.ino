#include "M3LS.h"

int xpin = 2;
int ypin = 3;
int zpin = 4;

int xjoy = A6;
int yjoy = A5;
int zjoy = A4;

int boundsUp = 10;
int boundsDown = 6;

bool wasPressed = false;

M3LS *myM3LS;

void setup(){
    Serial.begin(9600);
    Serial.println("Testing M3LS bounds change");
    myM3LS = new M3LS(xpin, ypin, zpin);
    Serial.println("Done instantiating M3LS");
    myM3LS->calibrate();
    pinMode(xjoy, INPUT);
    pinMode(yjoy, INPUT);
    pinMode(zjoy, INPUT);
    pinMode(boundsUp, INPUT);
    pinMode(boundsDown, INPUT);
}

void loop(){
    if(digitalRead(boundsUp) == HIGH){
        if(wasPressed); // do nothing
        else{
            myM3LS->boundsLarger();
            wasPressed = true;
        }

    } else wasPressed = false;
    if(digitalRead(boundsDown) == HIGH){
        if(wasPressed);
        else{
            myM3LS->boundsSmaller();
            wasPressed = true;
        }
    } else wasPressed = false;

    // Serial.print("Current Pos: ");
    // myM3LS->getCurrentPosition();
    // Serial.println(myM3LS->currentPosition[0]);
    // Serial.println(myM3LS->currentPosition[1]);
    // Serial.println(myM3LS->currentPosition[2]);
    myM3LS->updatePosition(1024-analogRead(xjoy), 1024-analogRead(yjoy), 1024-analogRead(zjoy));
    delay(50);
}
