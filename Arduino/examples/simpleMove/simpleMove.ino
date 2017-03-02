#include "M3LS.h"

int xpin = 4;

M3LS myM3LS(xpin);

void setup(){
    // Serial is already setup
    Serial.begin(9600);
    Serial.println("Testing M3LS Movement");
}

void loop(){
    Serial.println("Starting movement test.");
    delay(100);
    // for(int i=0; i<4; i++){
    //     myM3LS.updatePosition(1000+i*1000);
    //     delay(1000);
    // }
}
