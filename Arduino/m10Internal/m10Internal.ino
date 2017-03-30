#include "M3LS.h"

#define INTERVAL 50

int xpin = 4; int ypin = 2; int zpin = 3;

int z = 125;

M3LS *myM3LS;

void setup(){
    myM3LS = new M3LS(xpin, ypin, zpin);
    myM3LS->initUSBShield();
    delay(1000);
}

void loop(){
    // Ensure that at least INTERVAL ms have passed since the last update
    curMillis = millis();
    if(curMillis - lastMillis < INTERVAL){
        return;
    }
    lastMillis = curMillis;

    // Get input from USB controller
    Usb.Task();
    curButtons = Joy.getButtons();

    // first, buttons that can be held down:
    if(curButtons){
        int status = curButtons;
        int button = 1;
        while (status >>=1) ++button;
        switch(button){
            case 2: z = max(0, z-5);
                break;
            case 3: z = min(255, z+5);
                break;
        }
    }
    if(curButtons && lastButtons == 0){ // if any button changed
        int status = curButtons;
        Serial.print("Button pressed: ");
        int button = 1;
        while (status >>= 1) { ++button; }
        Serial.println(button);

        switch (button) {
            case 1:
                break;
        }
    }
    lastButtons = curButtons;

    // Update the position and bounds based upon the joystick inputs
    myM3LS->updatePosition(Joy.getX(), 255-Joy.getY(), z);
    myM3LS->setBounds(Joy.getZ());
}
