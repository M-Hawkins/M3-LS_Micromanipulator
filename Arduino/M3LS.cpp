/*
*/

#include "Arduino.h"
#include "M3LS.h"

// Class constructor for a three axis M3LS micromanipulator setup
M3LS::M3LS(int X_SS, int Y_SS, int Z_SS){
    // Store pin assignments
    _xSS = X_SS;
    _ySS = Y_SS;
    _zSS = Z_SS;

    // Configure slave select pins as outputs
    pinMode(_xSS, OUTPUT);
    pinMode(_ySS, OUTPUT);
    pinMode(Z_SS, OUTPUT);

    // Disable all stages
    digitalWrite(_xSS, HIGH);
    digitalWrite(_ySS, HIGH);
    digitalWrite(_zSS, HIGH);
}

// // Gets and stores the current X, Y, and Z position of the stages
// void getCurrentPosition(){
//     xPos = getAxisPosition(_xSS);
//     yPos = getAxisPosition(_ySS);
//     zPos = getAxisPosition(_zSS);
// }

// // Get the current position of a single stage
// int getAxisPosition(int pin){
//     digitalWrite(pin, LOW);
//     sendSPICommand(10);
//     waitForResponse();
//     // TODO
//     // Read response into var to return
//     // 8 bytes at a time
//     digitalWrite(pin, HIGH);
//     return 0;
// }

// void moveToTargetPosition(){
//   r eturn;
// }

// // Helper function which waits for a response over SPI
// void waitForResponse(){
//     // TODO
//     // Check until a 1 is not returned
//     // May have to return this value
//     return;
// }

// // Helper function used to send SPI commands specific to the M3-LS
// void sendSPICommand(int commandNumber, String args = ""){
//     // Build command as a string
//     String commandString = "<" + String(commandNumber) + ">\r";

//     // Transmit the string over SPI, one char at a time
//     for (unsigned int i = 0; i < commandString.length(); i++){
//         SPI.transfer(commandString[i]);
//     }
// }