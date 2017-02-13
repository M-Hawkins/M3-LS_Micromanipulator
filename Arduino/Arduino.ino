#include <SPI.h>
#include "M3LS.h"

void setup() {
    M3LS m3(1, 2, 3);
    SPI.begin();
    delay(100);
}

void loop() {
}
