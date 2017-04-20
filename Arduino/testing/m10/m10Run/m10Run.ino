#include "M3LS.h"

int xpin = A3; int ypin = A2; int zpin = A0;

M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Initialize M3LS
    myM3LS.begin();

    // Set handlers for moving the Z axis up or down
    myM3LS.bindButton(1, M3LS::ToggleHold);
    myM3LS.bindButton(2, M3LS::ZDown);
    myM3LS.bindButton(3, M3LS::ZUp);
    myM3LS.bindButton(4, M3LS::SetHome);
    myM3LS.bindButton(5, M3LS::ReturnHome);
    myM3LS.bindButton(6, M3LS::ToggleVelocity);
    myM3LS.bindButton(7, M3LS::InvertX);
    myM3LS.bindButton(8, M3LS::InvertY);
    myM3LS.bindButton(9, M3LS::InvertZ);
    myM3LS.bindButton(10, M3LS::InvertS);
    myM3LS.bindButton(11, M3LS::CenterAxes);

    myM3LS.invertXAxis(true);
    myM3LS.invertSAxis(true);

    delay(1000);
}

void loop(){
    myM3LS.run();
}
