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

M3LS *myM3LS;

void setup(){
    Serial.begin(115200);
    Serial.println("Testing M3LS USB Joystick Movement");
    myM3LS = new M3LS(xpin, ypin, zpin);
    Serial.println("Done instantiating M3LS object");
    if(-1 == Usb.Init()){
        Serial.println("ERROR: OSC did not start.");
    }
    delay(200);
    if(!Hid.SetReportParser(0, &Joy)){
        ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
    }
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

    // Debug print outs
    /*
    Serial.print("Updating position to: ");
    Serial.print(Joy.getX());
    Serial.print(" ");
    Serial.print(255-Joy.getY());
    Serial.print(" ");
    Serial.println(Joy.getZ());
    */

    // Update the position and bounds based upon the joystick inputs
    myM3LS->updatePosition(Joy.getX(), 255-Joy.getY(), 128);
    myM3LS->setBounds(Joy.getZ());

    curButtons = Joy.getButtons();
    if(curButtons && lastButtons == 0){ // if any button changed
        int status = curButtons;
        Serial.print("Button changed: ");
        int but = 1;
        while (status >>= 1) { ++but; }
        Serial.println(but);
    }
    lastButtons = curButtons;
}
