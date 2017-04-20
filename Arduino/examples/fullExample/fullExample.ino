#include "M3LS.h"

// Select which pins will be used for the X, Y, and Z axis
int xpin = A3; int ypin = A2; int zpin = A0;

// Initialize the library with your three selected pins
M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Run the library's setup routine
    myM3LS.begin();

    // Set which buttons will control a wide variety of functions
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

    // You can also set initial conditions directly
    myM3LS.setRefreshRate(40);
    myM3LS.invertXAxis(true);
    myM3LS.invertSAxis(true);
}

void loop(){
    // Have the library run continuously
    myM3LS.run();
}
