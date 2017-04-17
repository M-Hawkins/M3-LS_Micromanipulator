/*
M3LS.h - An Arduino library for translating high level commands to M3-LS API
         calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#ifndef M3LS_h
#define M3LS_h

#define DONE '\r'
#define IN_PROGRESS 0x01

#include "Arduino.h"
#include "SPI.h"

#ifndef MOCK
    #include "hidjoystickrptparser.h"
    #include <usbhid.h>
    #include <hiduniversal.h>
    #include <usbhub.h>
#endif

class M3LS{
    public:
        // Enums
        enum Axes {X, Y, Z, XY, XZ, YZ, XYZ};
        enum ControlMode {hold, open, position, velocity};
        enum Commands {Def, ToggleHold, ToggleVelocity, SetHome, ReturnHome,
                        ZUp, ZDown, InvertX, InvertY, InvertZ, InvertS, CenterAxes};
        // Variables
        ControlMode currentControlMode;
        int currentPosition[3];
        int homePosition[3];
        // Constructors
        M3LS(int X_SS);
        M3LS(int X_SS, int Y_SS);
        M3LS(int X_SS, int Y_SS, int Z_SS);
        // Functions
        void calibrate();
        void calibrateForward();
        void calibrateReverse();
        void initUSBShield();
        void bindButton(int buttonNumber, Commands comm);
        void invertXAxis(bool newStatus);
        void invertYAxis(bool newStatus);
        void invertZAxis(bool newStatus);
        void invertSAxis(bool newStatus);
        void setRefreshRate(int newRate);
        void setControlMode(ControlMode newMode);
        void updatePosition(int inp0, int inp1, int inp2);
        void updatePosition(int inp0, int inp1, int inp2, bool isActive);
        void updatePosition(int inp0, int inp1, int inp2, Axes axis);
        void updatePosition(int inp0, int inp1, int inp2, Axes axis, bool isActive);
        void setHome();
        void returnHome();
        void getCurrentPosition();
        void setBounds(int amount);
        void run();
        void begin();
        void centerAxes();
    private:
        // Variables
        int numAxes;
        int pins[3];
        int radius;
        int center[3];
        int refreshRate;
        int currentZPosition;
        bool invertX;
        bool invertY;
        bool invertZ;
        bool invertS;
        Commands buttonMap[20];
        char sendChars[50];
        char recvChars[100];
        #ifndef MOCK
            // USB Shield
            USB Usb;
            USBHub Hub;
            HIDUniversal Hid;
            JoystickEvents JoyEvents;
            JoystickReportParser Joy;
        #endif
        // Timing
        unsigned long lastMillis;
        unsigned long curMillis;
        int lastButtons;
        int curButtons;
        // Functions
        int getAxisPosition(int pin);
        void moveToTargetPosition(int target0);
        void moveToTargetPosition(int target0, Axes a);
        void moveToTargetPosition(int target0, int target1);
        void moveToTargetPosition(int target0, int target1, Axes a);
        void moveToTargetPosition(int target0, int target1, int target2);
        void moveToTargetPosition(int target0, int target1, int target2, Axes a);
        void setTargetPosition(int target);
        void advanceMotor(int inp, int axisNum);
        void recenter(int newx, int newy, int newz);
        int sendSPICommand(int pin, int length);
        int scaleToZones(int numZones, int input);
};

#endif
