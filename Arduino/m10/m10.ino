#include "M3LS.h"
#include "hidjoystickrptparser.h"
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#define INTERVAL 50

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

int xpin = 4; int ypin = 2; int zpin = 3;
unsigned long lastMillis = 0;
unsigned long curMillis;
int lastButtons, curButtons;
int z = 125;
int LED = A7;
int ledstat = 0;

M3LS *myM3LS;

void setup(){
    pinMode(LED, OUTPUT);
    digitalWrite(LED, 0);
    Serial.begin(115200);
    Serial.println("Testing M3LS USB Joystick Movement");
    myM3LS = new M3LS(xpin, ypin, zpin);
    Serial.println("Done instantiating M3LS object");
    if(-1 == Usb.Init()){
        Serial.println("ERROR: OSC did not start.");
        digitalWrite(LED, 1);
    }
    delay(200);
    if(!Hid.SetReportParser(0, &Joy)){
        ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
        //digitalWrite(LED,1);
    }
    delay(1000);
}

void loop(){
    //digitalWrite(LED, ledstat);
    ledstat = !ledstat;
    // Ensure that at least INTERVAL ms have passed since the last update
    curMillis = millis();
    if(curMillis - lastMillis < INTERVAL){
        return;
    }
    lastMillis = curMillis;

    // Get input from USB controller
    Usb.Task();

    // Debug print outs
    /*
    Serial.print("Updating position to: ");
    Serial.print(Joy.getX());
    Serial.print(" ");
    Serial.print(255-Joy.getY());
    Serial.print(" ");
    Serial.println(Joy.getZ());
    */


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
