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
    myM3LS->setControlMode(M3LS::open);
    myM3LS->setControlMode(M3LS::position);
}

void loop(){
    curMillis = millis();
    if(curMillis - lastMillis < INTERVAL){
        return;
    }

    lastMillis = curMillis;
    Usb.Task();

    Serial.print("Updating position to: ");
    Serial.print(Joy.getX());
    Serial.print(" ");
    Serial.print(Joy.getY());
    Serial.print(" ");
    Serial.println(Joy.getZ());
    myM3LS->updatePosition(Joy.getX(), 255-Joy.getY(), 128);
    myM3LS->setBounds(255-Joy.getZ());


}
