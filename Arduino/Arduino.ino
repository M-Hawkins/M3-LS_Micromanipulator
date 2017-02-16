#include <SPI.h>
#include "M3LS.h"

M3LS m3(1, 2, 3);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    delay(100);
}

void loop() {
    m3.getCurrentPosition();
    Serial.println(String(m3.currentPosition[0]) + ", " + 
                   String(m3.currentPosition[1]) + ", " + 
                   String(m3.currentPosition[2]));
    delay(3000);
}
