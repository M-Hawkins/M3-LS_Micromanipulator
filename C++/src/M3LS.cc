/*
M3LS.cc - An Arduino library for translating high level commands to M3-LS API
           calls over SPI
Copyright info?
*/

#include "M3LS.h"

//If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.
// #define DEBUG
#ifdef DEBUG
    //DPRINT is a macro, debug print
    #define DPRINT(...)    Serial.print(__VA_ARGS__)
    //DPRINTLN is a macro, debug print with new line
    #define DPRINTLN(...)  Serial.println(__VA_ARGS__)
#else
    //Defines a blank line for both
    #define DPRINT(...)     
    #define DPRINTLN(...)
#endif

// Constructors
// Class constructor for a one axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS)
#ifndef MOCK
    : Usb(), Hub(&Usb), Hid(&Usb), Joy(&JoyEvents)
#endif
{
    // Initialize a one axis system
    numAxes = 1;
    pins[0] = X_SS;
}

// Class constructor for a two axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS, int Y_SS)
#ifndef MOCK
    : Usb(), Hub(&Usb), Hid(&Usb), Joy(&JoyEvents)
#endif
{
    // Initialize a two axis system
    numAxes = 2;
    pins[0] = X_SS;
    pins[1] = Y_SS;
}

// Class constructor for a three axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS, int Y_SS, int Z_SS)
#ifndef MOCK
    : Usb(), Hub(&Usb), Hid(&Usb), Joy(&JoyEvents)
#endif
{
    // Initialize a three axis system
    numAxes = 3;
    pins[0] = X_SS;
    pins[1] = Y_SS;
    pins[2] = Z_SS;
}

// Initialization and public high level functions
// Initializes internal parameters and calibrates the motors and USB shield
void M3LS::begin(){
    // Initialize all pins as unselected outputs
    for (int pin = 0; pin < numAxes; pin++){
        pinMode(pins[pin], OUTPUT);
        digitalWrite(pins[pin], HIGH);
    }

    // Set the default internal bounds, radius, refresh rate, etc.
    lastMillis = 0;
    radius = 5500;
    recenter(6000, 6000, 6000);
    refreshRate = 1000/50;
    currentZPosition = 125;
    invertX = false;
    invertY = false;
    invertZ = false;
    invertS = false;

#ifdef DEBUG
    Serial.begin(115200);
#endif

#ifndef MOCK
    // Initialize the USB shield
    initUSBShield();
#endif
    // Initialize SPI
    delay(50);
    SPI.begin();

    // Calibrate the stages
    calibrate();

    // Ensure the system is in position mode
    currentControlMode = position;
    setControlMode(M3LS::open);
    setControlMode(M3LS::position);
}

// The main event loop
void M3LS::run(){
    // Ensure that at least INTERVAL ms have passed since the last update
    curMillis = millis();
    if(curMillis - lastMillis < refreshRate){ return; }
    lastMillis = curMillis;

#ifndef MOCK
    // Get input from USB controller
    Usb.Task();
    curButtons = Joy.getButtons();

    // Default the Z axis to dead zone
    currentZPosition = 125;

    // Default hold position movement to its active state
    bool isActive = false;

    // Handle buttons that can be held down:
    if(curButtons){
        // Calculate which button was pressed
        int status = curButtons;
        int button = 1;
        while (status >>=1) { ++button; }

        // Retrieve the associated command
        Commands comm = buttonMap[button];

        // Handle requested command
        switch(comm){
             // These will run the Z axis at 'full speed' up or down
            case ZUp:               currentZPosition = 127 + 30;
                                    break;
            case ZDown:             currentZPosition = 127 - 30;
                                    break;
            // Handles the "hold trigger to move" functionality
            case ActiveMovement:    isActive = true;
                                    break;
        }
    }

    // Handle any buttons that have changed
    if(curButtons && lastButtons == 0){
        // Calculate which button was pressed
        int status = curButtons;
        int button = 1;
        while (status >>=1) { ++button; }

        // Retrieve the associated command
        Commands comm = buttonMap[button];

        // Handle requested command
        switch(comm){
            case SetHome:           setHome();
                                    break;
            case ReturnHome:        returnHome();
                                    break;
            case CenterAxes:        recenter(6000, 6000, 6000);
                                    moveToTargetPosition(6000, 6000);
                                    break;
            case ToggleHold:        if (currentControlMode == hold){
                                        setControlMode(position);
                                    } else if (currentControlMode == position){
                                        setControlMode(hold);
                                    }
                                    break;
            case ToggleVelocity:    if (currentControlMode == velocity){
                                        setControlMode(position);
                                    } else {
                                        setControlMode(velocity);
                                    }
                                    break;
            case InvertX:           invertXAxis(!invertX);
                                    break;
            case InvertY:           invertYAxis(!invertY);
                                    break;
            case InvertZ:           invertZAxis(!invertZ);
                                    break;
            case InvertS:           invertSAxis(!invertS);
                                    break;
        }
    }

    // Update the position and bounds based upon the joystick inputs
    updatePosition(Joy.getX() + invertX * (255 - 2 * Joy.getX()), 
        Joy.getY() + invertY * (255 - 2 * Joy.getY()), 
        currentZPosition + invertZ * (255 - 2 * currentZPosition), XY, isActive);
    setBounds(Joy.getZ() + invertS * (255 - 2 * Joy.getZ()));

    // Save the current button status
    lastButtons = curButtons;
#endif
}

// Binds a given button to a specified command
void M3LS::bindButton(int buttonNumber, Commands comm){
    buttonMap[buttonNumber] = comm;
}

// Sets the current refresh rate to the new value
void M3LS::setRefreshRate(int newRate){
    refreshRate = 1000 / newRate;
}

// Sets the current control mode to the new mode
void M3LS::setControlMode(ControlMode newMode){
    /*
    Send to controller:
        <20 X>\r
        7 bytes
        X = 0: Open loop mode
        X = 1: Closed loop mode
        X = R: Report current mode
    Receive from controller:
        <20 X IIII>\r
        12 bytes
        IIII is the closed loop control interval, units are 3.2us
        Ignored for our purposes
    */

    if (newMode == open && currentControlMode != open){
        memcpy(sendChars, "<20 0>\r", 7);
        for (int axis = 0; axis < numAxes; axis++){
            sendSPICommand(pins[axis], 7);
        }
    } else if(newMode != open && currentControlMode == open){
        memcpy(sendChars, "<20 1>\r", 7);
        for (int axis = 0; axis < numAxes; axis++){
            sendSPICommand(pins[axis], 7);
        }
    } else if(newMode == position && currentControlMode != position){
        // This is where re-centering has to occur.
        // Re-center bounds around the current position
        getCurrentPosition();
        recenter(currentPosition[0], currentPosition[1], currentPosition[2]);
    }
    currentControlMode = newMode;
}

// Store the current position as the home position
void M3LS::setHome(){
    getCurrentPosition();
    memcpy(homePosition, currentPosition, numAxes * sizeof(int));
    DPRINT("Setting home to ");
    DPRINT(homePosition[0]); DPRINT(" ");
    DPRINT(homePosition[1]); DPRINT(" ");
    DPRINTLN(homePosition[2]);
}

// Return to the stored home position
void M3LS::returnHome(){
    // Store current mode and switch to position mode
    ControlMode previousMode = currentControlMode;
    setControlMode(position);
    DPRINTLN("Returning home");
    DPRINT(homePosition[0]); DPRINT(" ");
    DPRINTLN(homePosition[1]);

    // Raise Z axis
    if (numAxes > 2){
        getCurrentPosition();
        // TODO: Determine an appropriate Z offset
        moveToTargetPosition(currentPosition[2] + 10 - (invertZ * 20), Z);
    }

    // Move X and Y to home position
    moveToTargetPosition(homePosition[0], homePosition[1], XY);
    recenter(homePosition[0], homePosition[1], homePosition[2]);

    // Restore previous mode
    setControlMode(previousMode);
}

// Sets the inversion status of the X axis
void M3LS::invertXAxis(bool newStatus){
    invertX = newStatus;
}

// Sets the inversion status of the Y axis
void M3LS::invertYAxis(bool newStatus){
    invertY = newStatus;
}

// Sets the inversion status of the Z axis
void M3LS::invertZAxis(bool newStatus){
    invertZ = newStatus;
}

// Sets the inversion status of the sensitivity axis
void M3LS::invertSAxis(bool newStatus){
    invertS = newStatus;
}

// Default method for updating the needle's position
void M3LS::updatePosition(int inp0, int inp1, int inp2){
    updatePosition(inp0, inp1, inp2, XYZ, false);
}

// Default method for updating the needle's position with a trigger parameter
void M3LS::updatePosition(int inp0, int inp1, int inp2, bool isActive){
    updatePosition(inp0, inp1, inp2, XYZ, isActive);
}

// Default method for updating the needle's position with an axis parameter
void M3LS::updatePosition(int inp0, int inp1, int inp2, Axes axis){
    updatePosition(inp0, inp1, inp2, axis, false);
}

// Update the needle's position based upon current mode and joystick inputs
void M3LS::updatePosition(int inp0, int inp1, int inp2, Axes axis, bool isActive){
    // Handle inputs based on the current control mode
    switch(currentControlMode)
    {
        case hold     : // Only execute a move command if the button is held
                        if (!isActive){
                            getCurrentPosition();
                            recenter(currentPosition[0], currentPosition[1], 
                                currentPosition[2]);
                            break;
                        }
        case position : // Map the inputs based on the current bounds
                        // Joystick reports 0-255
                        DPRINT("X: "); DPRINT(inp0); DPRINT(" ");
                        inp0 = map(inp0, 0, 255, 
                            center[0] - radius, center[0] + radius);
                        DPRINTLN(inp0);
                        DPRINT("Y: "); DPRINT(inp1); DPRINT(" ");
                        inp1 = map(inp1, 0, 255, 
                            center[1] - radius, center[1] + radius);
                        DPRINTLN(inp1);
                        moveToTargetPosition(inp0, inp1, axis);

                        // Treat the Z axis as if it is in velocity mode
                        inp2 = scaleToZones(7, inp2);;
                        advanceMotor(inp2, 2);
                        break;

        case velocity : // Set the speed and target positions based on
                        // displacement, divided between 7 zones
                        // This should result in zone 0 being a "dead zone."
                        int numZones = 7;
                        int inputs[3] = {inp0, inp1, inp2};

                        // Loop through each available axis
                        for (int axis = 0; axis < numAxes; axis++){
                            int inp = scaleToZones(numZones, inputs[axis]);
                            advanceMotor(inp, axis);
                        }
                        break;
    }
}

// Gets and stores the current position of each stage
void M3LS::getCurrentPosition(){
    for (int axis = 0; axis < numAxes; axis++){
        currentPosition[axis] = getAxisPosition(pins[axis]);
    }
}

// ---------------------------------------------------------------------------
// Private Functions
// Calibrate the stages
void M3LS::calibrate(){
    calibrateForward();
    calibrateReverse();
}

// Executes a forward calibration routine on all axes
void M3LS::calibrateForward(){
    /*
    Send to controller:
        <87 D>\r
        7 bytes
        D = 4: Reverse frequency sweep
        D = 5: Forward frequency sweep
    Receive from controller:
        <87 D XX FFFF>\r
        15 bytes
        Ignored for our purposes
    */

    // Build command and send it to SPI
    delay(250);
    memcpy(sendChars, "<87 5>\r", 7);
    for (int axis = 0; axis < numAxes; axis++){
        sendSPICommand(pins[axis], 7);
    }
    delay(250);
}

// Executes a reverse calibration routine on all axes
void M3LS::calibrateReverse(){
    /*
    Send to controller:
        <87 D>\r
        7 bytes
        D = 4: Reverse frequency sweep
        D = 5: Forward frequency sweep
    Receive from controller:
        <87 D XX FFFF>\r
        15 bytes
        Ignored for our purposes
    */

    delay(250);
    memcpy(sendChars, "<87 4>\r", 7);
    for (int axis = 0; axis < numAxes; axis++){
            sendSPICommand(pins[axis], 7);
    }
    delay(250);
}

// Instantiate the USB shield controller
void M3LS::initUSBShield(){
#ifndef MOCK
// Call initialization routines
    Usb.Init();
    Hid.SetReportParser(0, &Joy);
#endif
}

// Adjust the internal bounds based on a given number of encoder counts
void M3LS::setBounds(int amount){
    if(amount < 64){
        radius = map(amount, 0, 64, 10, 50);
    } else if(amount < 128){
        radius = map(amount, 64, 128, 50, 500);
    } else if(amount < 192){
        radius = map(amount, 128, 192, 500, 2250);
    } else
        radius = map(amount, 192, 255, 2250, 5500);
}

// Default single axis move command
void M3LS::moveToTargetPosition(int target0){
    moveToTargetPosition(target0, X);
}

// Move the specified axis to the target position
void M3LS::moveToTargetPosition(int target0, Axes axis){
    setTargetPosition(target0);
    sendSPICommand(pins[axis], 14);
}

// Default two axis move command
void M3LS::moveToTargetPosition(int target0, int target1){
    moveToTargetPosition(target0, target1, XY);
}

// Move the specified axes to the target positions
void M3LS::moveToTargetPosition(int target0, int target1, Axes axis){
    switch(axis)
    {
        case XY  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    break;
        case XZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[2], 14);
                    break;
        case YZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[1], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[2], 14);
                    break;
        default:    moveToTargetPosition(target0, target1, 0, axis);
                    break;
    }
}

// Default three axis move command
void M3LS::moveToTargetPosition(int target0, int target1, int target2){
    moveToTargetPosition(target0, target1, target2, XYZ);
}

// Move the specified axes to the target positions
void M3LS::moveToTargetPosition(int target0, int target1, int target2, Axes axis){
    switch(axis)
    {
        case X   :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    break;
        case Y   :  setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    break;
        case Z   :  setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
        case XY  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    break;
        case XZ  :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
        case YZ  :  setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
        case XYZ :  setTargetPosition(target0);
                    sendSPICommand(pins[0], 14);
                    setTargetPosition(target1);
                    sendSPICommand(pins[1], 14);
                    setTargetPosition(target2);
                    sendSPICommand(pins[2], 14);
                    break;
    }
}

// Map a joystick input to a smaller zone number
int M3LS::scaleToZones(int numZones, int input){
    return (round(input * (numZones - 1) / 255.0) 
        - ((numZones - 1) / 2)) * (radius / (numZones * 10) + 1);
}

// Set the target position to move to
void M3LS::setTargetPosition(int target){
    /*
    Send to controller:
        <08>\r
        4 bytes
    Receive from controller:
        <08>\r
        4 bytes
        Ignored for our purposes
    */

    // Build command and send it to SPI
    memcpy(sendChars, "<08 ", 4);
    sprintf(sendChars + 4, "%08X", target);
    memcpy(sendChars + 12, ">\r", 2);
}

// Move the needle a short distance based on each axis's current zone
void M3LS::advanceMotor(int inp, int axisNum){
    /*
    Send to controller:
        <06 D SSSSSSSS>\r
        16 bytes
        D = 0: Move backwards
        D = 1: Move forwards
        S... : Number of encoder counts to move
    Receive from controller:
        <06>\r
        5 bytes
        Ignored for our purposes
    */

    // Build command and send it to SPI
    memcpy(sendChars, "<06 ", 4);
    sprintf(sendChars + 4, "%01d", inp > 0);
    memcpy(sendChars + 5, " ", 1);
    sprintf(sendChars + 6, "%08X", abs(inp));
    memcpy(sendChars + 14, ">\r", 2);
    sendSPICommand(pins[axisNum], 16);
}

// Get the current position of a single stage
int M3LS::getAxisPosition(int pin){
    /*
    Send to controller:
        <10>\r
        5 bytes
    Receive from controller:
        <10 SSSSSS PPPPPPPP EEEEEEEE>\r
        30 bytes
        S... : Motor status, see datasheet
        P... : Absolute position in encoder counts
               This function will extract and store this value
        E... : Position error in encoder counts
    */

    // Build command and send it to SPI
    memcpy(sendChars, "<10>\r", 5);
    sendSPICommand(pin, 5);

    // Allocate space for, extract, and store the position value
    char position[11] = "0x";
    memcpy(position+2, recvChars + 11, 8);
    position[10] = 0;
    return strtol(position, NULL, 0);
}

// Set the specified coordinates as the new center
void M3LS::recenter(int newx, int newy, int newz){
    center[0]=newx;
    center[1]=newy;
    center[2]=newz;
}

// Sends a command over the SPI bus and writes the response to the buffer
int M3LS::sendSPICommand(int pin, int length){
#ifndef MOCK
    // Prepare the appropriate settings and clear the buffer
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
    memset(recvChars, 0, 100);
    digitalWrite(pin, LOW);
    delayMicroseconds(60);

    // Transfer the given command over SPI, one byte at a time
    for(int i = 0; i < length; i++){
        SPI.transfer(sendChars[i]);
        // Minimum delay time: 60 microseconds between SPI transfers.
        delayMicroseconds(60);
    }

    // Wait until the stage is ready to respond
    int j = 0;
    int counter = 0;
    // char DONE '\r';
    // char IN_PROGRESS 0x01;
    while('<' != (recvChars[j] = SPI.transfer(0x01))){
        delayMicroseconds(60);
        if (counter++ == 100) break;
    }
    delayMicroseconds(60);

    // Read in and store the response
    while('\r' != (recvChars[++j] = SPI.transfer(0x01))){
        delayMicroseconds(60);
        if(j >= 99){
            digitalWrite(pin, HIGH);
            SPI.endTransaction();
            return -1;
        }
    }
    // DPRINT("Received from M3-LS:");
    // DPRINTLN(recvChars);
    // DPRINT("Took ");
    // DPRINT(j-1);
    // DPRINTLN(" iterations.\n");
    digitalWrite(pin, HIGH);
    SPI.endTransaction();
#endif
    return 0;
}
