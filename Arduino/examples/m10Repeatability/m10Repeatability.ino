#include "M3LS.h"

int xpin = A3; int ypin = A2; int zpin = A0;
M3LS::Axes axisList[4] = {M3LS::X, M3LS::Y, M3LS::Z, M3LS::XY};

M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Initialize M3LS
    myM3LS.begin();
    delay(1000);
}

void loop(){
    // Iterate over each axis
    for (int axisNum = 0; axisNum < 4; axisNum++){
        // Iterate over three trials
        for (int trial = 0; trial < 3; trial++){
            myM3LS.updatePosition(0, 0, 0, axisList[axisNum]);
            delay(3000);
            myM3LS.updatePosition(255, 255, 255, axisList[axisNum]);
            delay(3000);
        }
        // Recenter axis
        myM3LS.updatePosition(127, 127, 127, axisList[axisNum]);
        delay(3000);
    }
}
