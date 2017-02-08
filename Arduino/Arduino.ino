#include <SPI.h>

// SCK  = 13
// MISO = 12
// MOSI = 11

// Initialize pin numbers and constants
const int X_SS = 8;
const int Y_SS = 9;
const int Z_SS = 10;
const int MAX_TIMEOUT_ATTEMPTS = 1000;

// Initialize variables
int xPos = 0;
int yPos = 0;
int zPos = 0;
int numAttempts = 0;

void setup() {
  // Configure slave select pins as outputs
  pinMode(X_SS, OUTPUT);
  pinMode(Y_SS, OUTPUT);
  pinMode(Z_SS, OUTPUT);

  // Disable all stages
  digitalWrite(X_SS, HIGH);
  digitalWrite(Y_SS, HIGH);
  digitalWrite(Z_SS, HIGH);

  SPI.begin();
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// Gets and stores the current X, Y, and Z position of the stages
void getCurrentPosition(){
  xPos = getAxisPosition(X_SS);
  yPos = getAxisPosition(Y_SS);
  zPos = getAxisPosition(Z_SS);
}

// Get the current position of a single stage
int getAxisPosition(int pin){
  digitalWrite(pin, LOW);
  sendSPICommand(10);
  waitForResponse();
  // TODO
  // Read response into var to return
  // 8 bytes at a time
  digitalWrite(pin, HIGH);
  return 0;
}

void moveToTargetPosition(){
  return;
}

// Helper function which waits for a response over SPI
void waitForResponse(){
  // TODO
  // Check until a 1 is not returned
  // May have to return this value
  return;
}

// Helper function used to send SPI commands specific to the M3-LS
void sendSPICommand(int commandNumber){
  // Build command as a string
  String commandString = "<" + String(commandNumber) + ">\r";

  // Transmit the string over SPI, one char at a time
  for (unsigned int i = 0; i < commandString.length(); i++){
    SPI.transfer(commandString[i]);
  }
}
