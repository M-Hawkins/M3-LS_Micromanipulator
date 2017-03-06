#include "M3LS.h"

int xpin = 3;

M3LS *myM3LS;

void setup(){
    Serial.begin(9600);
    Serial.println("Testing M3LS Movement");
    Serial.println("About to construct M3LS object:");
    myM3LS = new M3LS(xpin);
    Serial.println("DONE instantiating object");

}

void loop(){
    Serial.println("Starting movement test.");
    delay(100);
    for(int i=0; i<12; i++){
        myM3LS->updatePosition(500+i*1000);
        delay(2000);
        myM3LS->getCurrentPosition();
        Serial.println(myM3LS->currentPosition[0]);
    }
}
