#include "M3LS.h"

int xpin = 4; int ypin = 2; int zpin = 3;

M3LS *myM3LS;

void setup(){
    // Initialize M3LS
    myM3LS = new M3LS(xpin, ypin, zpin);

    // Set handlers for moving the Z axis up or down
    myM3LS->bindButton(2, M3LS::Commands::ZUp);
    myM3LS->bindButton(3, M3LS::Commands::ZDown);

    delay(1000);
}

void loop(){
    myM3LS->run();
}
