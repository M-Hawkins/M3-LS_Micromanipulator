#include "hidjoystickrptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
joyEvents(evt),
oldHat(0xDE),
oldButtons(0) {
        for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
                oldPad[i] = 0xD;
}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
    // Serial.println(len);
    switch(len){
        case 5:
            jtype = SimpleLogitech;
            break;
        case 19:
            jtype = ThrustMaster;
            break;
    }

    bool match = true;

    // Checking if there are changes in report since the method was last called
    for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
            if (buf[i] != oldPad[i]) {
                    match = false;
                    break;
            }

    // Calling Game Pad event handler
    if (!match && joyEvents) {
            for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) oldPad[i] = buf[i];
    }
}

uint16_t JoystickReportParser::getButtons(void){
    switch(jtype){
        case SimpleLogitech:
            return (uint16_t)(((uint16_t)oldPad[4] << 8) | oldPad[3]);
        case ThrustMaster:
            return (uint16_t)(((uint16_t)oldPad[1]&0xF << 8) | oldPad[0]);
    }
    // bit vector of buttons. Simply toggles each bit vector when pressed
    return (uint16_t)(((uint16_t)oldPad[4] << 8) | oldPad[3]);
}

uint8_t JoystickReportParser::getX(void){
    switch(jtype){
        case SimpleLogitech:
            return oldPad[0];
        case ThrustMaster:
            return oldPad[3];
    }
    return oldPad[0];
}


uint8_t JoystickReportParser::getY(void){
    switch(jtype){
        case SimpleLogitech:
            return oldPad[1];
        case ThrustMaster:
            return oldPad[4];
    }
    return oldPad[1];
}

uint8_t JoystickReportParser::getZ(void){
    switch(jtype){
        case SimpleLogitech:
            return oldPad[2];
        case ThrustMaster:
            return 255-oldPad[6];
    }
    return oldPad[2];
}
