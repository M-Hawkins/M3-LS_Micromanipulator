#include "include/M3LS.h"

M3LS m3 = M3LS(1);
long* currentPosition;

void setup() {
    Serial.begin(9600);
    delay(100);
    m3.moveToTargetPosition(1000L, 2000L, 3000L);
}

void loop() {
    currentPosition = m3.getCurrentPosition();
    Serial.println(String(m3.currentPosition[0]) + ", " + 
                   String(m3.currentPosition[1]) + ", " + 
                   String(m3.currentPosition[2]));
    m3.moveToTargetPosition(currentPosition[0] + 100L, 
                            currentPosition[1] + 200L, 
                            currentPosition[2] + 300L);
    delay(3000);
}
