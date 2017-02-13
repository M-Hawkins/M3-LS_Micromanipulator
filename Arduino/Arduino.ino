#include <SPI.h>
#include "M3LS.h"

M3LS m3(1, 2, 3);

void setup() {
    SPI.begin();
    delay(100);
}

void loop() {
    m3.getCurrentPosition();
    m3.moveToTargetPosition();
}
