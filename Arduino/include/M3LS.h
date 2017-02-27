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
        // Enums
        enum ControlMode {position, velocity};
        enum Axes {X, Y, Z, XY, XZ, YZ, XYZ};
        // Variables
        ControlMode currentControlMode;
        // Constructors
        M3LS(int X_SS);
        M3LS(int X_SS, int Y_SS);
        M3LS(int X_SS, int Y_SS, int Z_SS);
        // Functions
        void setControlMode(ControlMode newMode);
        void updatePosition(long xPos, long yPos, long zPos);
        void setSensitivity(int speed);
        void setHome();
        void returnHome();
    private:
        // Variables
        int numAxes;
        int pins[3];
        char sendChars[50];
        char recvChars[50];
        long currentPosition[3];
        long homePosition[3];
        // Functions
        void getCurrentPosition();
        long getAxisPosition(int pin);
        void moveToTargetPosition(long target0);
        void moveToTargetPosition(long target0, Axes a);
        void moveToTargetPosition(long target0, long target1);
        void moveToTargetPosition(long target0, long target1, Axes a);
        void moveToTargetPosition(long target0, long target1, long target2);
        void moveToTargetPosition(long target0, long target1, long target2, Axes a);
        void setTargetPosition(long target);
        int sendSPICommand(int pin);
};

#endif
