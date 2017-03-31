#include "M3LS.h"

int xpin = 4; int ypin = 2; int zpin = 3;

M3LS *myM3LS;

void setup(){
    // Initialize M3LS and USB shield
    myM3LS = new M3LS(xpin, ypin, zpin);
    myM3LS->initUSBShield();

    // Set handlers for up / down sensitivity
    // B2 -> z - 5
    // B3 -> z + 5

    delay(1000);
}

void loop(){
    myM3LS->run();
}
