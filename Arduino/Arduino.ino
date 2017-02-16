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
    delay(5000);
}
