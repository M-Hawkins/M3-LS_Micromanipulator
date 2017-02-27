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
        void moveToTargetPosition(long target0);
        void moveToTargetPosition(long target0, Axes a);
        void moveToTargetPosition(long target0, long target1);
        void moveToTargetPosition(long target0, long target1, Axes a);
        void moveToTargetPosition(long target0, long target1, long target2);
        void moveToTargetPosition(long target0, long target1, long target2, Axes a);
    private:
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
