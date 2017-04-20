#include "M3LS.h"

// Select which pins will be used for the X, Y, and Z axis
int xpin = A3; int ypin = A2; int zpin = A0;

// Initialize the library with your three selected pins
M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Run the library's setup routine
    myM3LS.begin();

    // Set which buttons will move the Z axis up and down
    myM3LS.bindButton(2, M3LS::ZDown);
    myM3LS.bindButton(3, M3LS::ZUp);
}

void loop(){
    // Have the library run continuously
    myM3LS.run();
}
