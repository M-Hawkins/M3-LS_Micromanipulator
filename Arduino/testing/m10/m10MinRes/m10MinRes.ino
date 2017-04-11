#include "M3LS.h"

int xpin = A3; int ypin = A2; int zpin = A0;
M3LS::Axes axisList[4] = {M3LS::X, M3LS::Y, M3LS::Z, M3LS::XY};
int step = 127;

M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Initialize M3LS
    myM3LS.begin();
    delay(1000);
    myM3LS.setBounds(0);
}

void loop(){
    // Iterate over each axis
    for (int axisNum = 0; axisNum < 4; axisNum++){
        step = 127;
        // Step forward ten times
        while (step < 137){
            step++;
            myM3LS.updatePosition(step, step, step, axisList[axisNum]);
            delay(1000);
        }
        
        // Step backwards ten times
        while (step > 127){
            step--;
            myM3LS.updatePosition(step, step, step, axisList[axisNum]);
            delay(1000);
        }

        // Recenter axis
        myM3LS.updatePosition(127, 127, 127, axisList[axisNum]);
        delay(3000);
    }
}
