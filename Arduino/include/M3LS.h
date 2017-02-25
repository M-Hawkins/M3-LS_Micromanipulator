/*
M3LS.h - An Arduino library for translating high level commands to M3-LS API
         calls over SPI
Created by Matthew Hawkins
Copyright info?
*/

#ifndef M3LS_h
#define M3LS_h

#include "Arduino.h"

class M3LS{
    public:
        // Constructors
        M3LS(int X_SS);
        M3LS(int X_SS, int Y_SS);
        M3LS(int X_SS, int Y_SS, int Z_SS);
        // Variables
        long currentPosition[3];
        // Functions
        void setControlMode();
        void setHome();
        // returnHome();
        // setSensitivity();
        // setBounds();
        // Functions OLD
        long* getCurrentPosition();
        void moveToTargetPosition(long target);
        void moveToTargetPositionX(long target);
        void moveToTargetPositionY(long target);
        void moveToTargetPositionZ(long target);
        void moveToTargetPosition(long targetX, long targetY);
        void moveToTargetPositionXY(long targetX, long targetY);
        void moveToTargetPositionXZ(long targetX, long targetZ);
        void moveToTargetPositionYZ(long targetY, long targetZ);
        void moveToTargetPosition(long targetX, long targetY, long targetZ);
        void moveToTargetPositionXYZ(long targetX, long targetY, long targetZ);
    private:
        // Enums
        enum ControlMode {position, velocity};
        // Variables
        int numAxes;
        int pins[3];
        char sendChars[50];
        char recvChars[50];
        long homePosition[3];
        ControlMode currentControlMode;
        // Functions
        long getAxisPosition(int pin);
        void sendSPICommand(int pin);
        void setTargetPosition(long target);
};

#endif
