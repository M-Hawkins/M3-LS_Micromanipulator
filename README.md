# M3-LS Micromanipulator
This Arduino-based solution utilizes [M3-LS linear smart stages](http://www.newscaletech.com/micro-mechatronics/m3-linear-stages.php) to provide cell biology researchers with an accessible method for nanoscale interaction with living cells. 
***
## Hardware Requirements
1. 1x [Arduino Due](https://www.arduino.cc/en/Main/arduinoBoardDue)
2. 3x [M3-LS linear smart stages](http://www.newscaletech.com/micro-mechatronics/m3-linear-stages.php)
3. TODO: Brackets
4. TODO: Mounting
5. TODO: Needle Holder

## Software Dependencies
1. This library's [latest release](https://github.com/M-Hawkins/M3-LS_Micromanipulator/releases)
2. The latest release of the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
3. The [USB Host Shield Library](https://github.com/felis/USB_Host_Shield_2.0)
***
## Setup
An M3LS folder is provided that contains the Arduino library and examples folder. To install for use with the Arduino IDE, clone the repository and provide a link to the `M3LS` folder in `Arduino/libraries`.

TODO: Physical wiring guide (with pictures)
***
## Customization
The included sketch is set up to provide a working three axes micromanipulator controller out of the box. After opening this sketch in the Arduino IDE, you will see:
```C++
#include "M3LS.h"

int xpin = 1; int ypin = 2; int zpin = 3;

M3LS *myM3LS;

void setup(){
    // Initialize M3LS
    myM3LS = new M3LS(xpin, ypin, zpin);

    // Set handlers for moving the Z axis up or down
    //myM3LS->bindButton(1, M3LS::Commands::ToggleHold);
    myM3LS->bindButton(2, M3LS::Commands::ZUp);
    myM3LS->bindButton(3, M3LS::Commands::ZDown);
    //myM3LS->bindButton(4, M3LS::Commands::SetHome);
    //myM3LS->bindButton(5, M3LS::Commands::ReturnHome);

    delay(1000);
}

void loop(){
    myM3LS->run();
}
```
Note that the faded lines preceeded with "`//`" are inactive.

However, joysticks and personal preference vary significantly. Different button assignments can be made easily. For example, to change the controller to use button #7 for moving the Z axis up and 9 for moving the Z axis down, edit the sketch as such:
```C++
myM3LS->bindButton(7, M3LS::Commands::ZUp);
myM3LS->bindButton(9, M3LS::Commands::ZDown);
```
If your joystick's buttons are not clearly labeled, please consult its user manual to determine the appropriate numbers to use.

In addition to remapping the desired buttons, the associated functionality can be adjusted as well. In order to use the included position memory and retrieval functionality, remove the preceeding "`//`" from the following lines:
```C++
myM3LS->bindButton(4, M3LS::Commands::SetHome);
myM3LS->bindButton(5, M3LS::Commands::ReturnHome);
```
Each command can be enabled, disabled, or configuring in the same way. 
***
## Available Commands
| Command | Code Snippet | Description |
|---|----|---:|
| ToggleHold | `myM3LS->bindButton(1, M3LS::Commands::ToggleHold);` | TODO |
| ZUp | `myM3LS->bindButton(2, M3LS::Commands::ZUp);` | TODO |
| ZDown | `myM3LS->bindButton(3, M3LS::Commands::ZDown);` | TODO |
| SetHome | `myM3LS->bindButton(4, M3LS::Commands::SetHome);` | TODO |
| ReturnHome | `myM3LS->bindButton(5, M3LS::Commands::ReturnHome);` | TODO |

