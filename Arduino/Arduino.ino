#include <SPI.h>

//SCK  = 13
//MISO = 12
//MOSI = 11
//SS are active low

const int X_SS = 8;
const int Y_SS = 9;
const int Z_SS = 10;
const int MAX_TIMEOUT_ATTEMPTS = 1000;

int xPos = 0;
int yPos = 0;
int zPos = 0;
int numAttempts = 0;

void setup() {
  pinMode(X_SS, OUTPUT);
  pinMode(Y_SS, OUTPUT);
  pinMode(Z_SS, OUTPUT);
  SPI.begin();
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:

}

//"when fetching  a reply from  the M3‐LS,  it  is  recommended that  each  SPI 
//exchange  be  spaced  by  60  µsec  in  order to  guarantee that  duplicate bytes are not received"

void getCurrentPosition(){
  
}

void moveToTargetPosition(){
  
}

//...and anything else you can think of

