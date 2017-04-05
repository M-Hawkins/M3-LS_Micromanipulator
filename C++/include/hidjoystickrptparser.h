#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <usbhid.h>

struct GamePadEventData {
        uint8_t X, Y, Z1, Z2, Rz, A, B;
};

enum JoystickType { SimpleLogitech, ThrustMaster
};

class JoystickEvents {
public:
};

#define RPT_GEMEPAD_LEN		7

class JoystickReportParser : public HIDReportParser {
        JoystickEvents *joyEvents;

        uint8_t oldPad[RPT_GEMEPAD_LEN];
        uint8_t oldHat;
        uint16_t oldButtons;
        JoystickType jtype;

public:
        JoystickReportParser(JoystickEvents *evt);

        virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);

        uint8_t getX();
        uint8_t getY();
        uint8_t getZ();

        uint16_t getButtons();
};

#endif // __HIDJOYSTICKRPTPARSER_H__
