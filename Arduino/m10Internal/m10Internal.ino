#include "M3LS.h"

int xpin = 4; int ypin = 2; int zpin = 3;

M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Initialize M3LS
    myM3LS.begin();

    // Set handlers for moving the Z axis up or down
    //myM3LS->bindButton(1, M3LS::ToggleHold);
    myM3LS.bindButton(2, M3LS::ZUp);
    myM3LS.bindButton(3, M3LS::ZDown);
    //myM3LS->bindButton(4, M3LS::SetHome);
    //myM3LS->bindButton(5, M3LS::ReturnHome);
    //myM3LS->bindButton(6, M3LS::ToggleVelocity);

    delay(1000);
}

void loop(){
    myM3LS.run();
}
