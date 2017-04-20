# M3-LS Micromanipulator
This Arduino-based solution utilizes 
[M3-LS linear smart stages](http://www.newscaletech.com/micro-mechatronics/m3-linear-stages.php) 
to provide cell biology researchers with an accessible method for nanoscale 
interaction with living cells. 

***

## Hardware Requirements
1. 3x [M3-LS linear smart stages](http://www.newscaletech.com/micro-mechatronics/m3-linear-stages.php)
2. 1x [Arduino Due](https://www.arduino.cc/en/Main/arduinoBoardDue)
3. 1x [Arduino USB Host Shield](https://www.arduino.cc/en/Main/ArduinoUSBHostShield)
4. TODO: Circuit / Breakout Board
5. TODO: Brackets
6. TODO: Mounting
7. TODO: Needle Holder

## Software Dependencies
1. This library's [latest release](https://github.com/M-Hawkins/M3-LS_Micromanipulator/releases)
2. The latest release of the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
3. The [USB Host Shield Library](https://github.com/felis/USB_Host_Shield_2.0)

***

## Setup
First, download this library's [latest release.](https://github.com/M-Hawkins/M3-LS_Micromanipulator/releases)
Open up your Arduino IDE and navigate to 
`Sketch->Include Library->Add .ZIP Library...`
. Locate and select the release you just downloaded. 
If you have not done so previously, you must also install the USB host shield
library. This can be done by going to 
`Sketch->Include Library->Manage Libraries...->USB Host Shield Library 2.0->Install`
. 


TODO: Shield(s) physical setup guide (with pictures)

***

## Customization
A handful of sketches are including to get your system up and running as 
quickly as possible. These can be found within the Arduino IDE at 
`File->Examples->M3LS`. The most basic of these sketches is `basicExample`, 
shown below. 

```C++
#include "M3LS.h"

// Select which pins will be used for the X, Y, and Z axis
int xpin = A3; int ypin = A2; int zpin = A0;

// Initialize the library with your three selected pins
M3LS myM3LS(xpin, ypin, zpin);

void setup(){
    // Run the library's setup routine
    myM3LS.begin();

    // Set which buttons will move the Z axis up and down
    myM3LS.bindButton(2, M3LS::ZDown);
    myM3LS.bindButton(3, M3LS::ZUp);
}

void loop(){
    // Have the library run continuously
    myM3LS.run();
}
```

Note that the faded lines preceeded with "`//`" are inactive.

Joysticks and personal preference can vary significantly. 
To accomadate this, different button assignments can be made easily. 
For example, to change the controller to use button #9 for moving the 
Z axis down and 7 for moving the Z axis up, edit the sketch as such:

```C++
myM3LS.bindButton(9, M3LS::ZDown);
myM3LS.bindButton(7, M3LS::ZUp);
```

If your joystick's buttons are not clearly labeled, please consult 
its user manual to determine the appropriate numbers to use.

In addition to remapping the desired buttons, the associated functionality 
can be adjusted as well. Please see `fullExample` and the list of available 
commands below for more examples. 

***

## Available Commands
| Command | Code Snippet | Description |
|---|----|---:|
| ActiveMovement | `myM3LS.bindButton(1, M3LS::ActiveMovement);` | When held, allows for needle movement while in the hold state. |
| SetHome | `myM3LS.bindButton(2, M3LS::SetHome);` | Store the needle’s current position as the home position. |
| ReturnHome | `myM3LS.bindButton(3, M3LS::ReturnHome);` | Moves the needle to the stored home position. |
| CenterAxes | `myM3LS.bindButton(4, M3LS::CenterAxes);` | Recenters the needle. |
| ToggleHold | `myM3LS.bindButton(5, M3LS::ToggleHold);` | Prevents new joystick inputs from moving the needle until toggled again.<br/>The current location is set as the new position mode center upon resuming. |
| ToggleVelocity | `myM3LS.bindButton(6, M3LS::ToggleVelocity);` | Toggles between manipulating the needle with absolute positioning or velocity based positioning.<br/>The current location is set as the new position mode center upon exiting velocity mode. |
| ZUp | `myM3LS.bindButton(7, M3LS::ZUp);` | Moves the needle’s position within the Z axis upward. |
| ZDown | `myM3LS.bindButton(8, M3LS::ZDown);` | Moves the needle’s position within the Z axis downward. |
| InvertX | `myM3LS.bindButton(9, M3LS::InvertX);` | Toggles the direction joystick inputs will cause the X axis to travel in. |
| InvertY | `myM3LS.bindButton(10, M3LS::InvertY);` | Toggles the direction joystick inputs will cause the Y axis to travel in. |
| InvertZ | `myM3LS.bindButton(11, M3LS::InvertZ);` | Toggles the direction of travel of the ZUp and ZDown commands.  |
| InvertS | `myM3LS.bindButton(12, M3LS::InvertS);` | Toggles the direction of the sensitivity adjustment.  |


