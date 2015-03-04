/********************************
Program Name: rfDuinoAnalogReadnSend
Version: 3
Arduino: rfDuino
Last Update: March 4, 2015
********************************/



//#define DEBUG

//*******************************
// Defined Pins
//*******************************
#define Tx 0 // BT Mate Tx --> Arduin D0
#define Rx 1 // BT Mate Rx --> Arduin D1
#define analogPin 6
//*******************************

//*******************************
//BT MATE COMMANDS
//*******************************
#define START 0x00
#define STOP 0xFF
#define DISCONNECT 0x55
//*******************************
//Variables
//*******************************
short valueECG;
short *intPtr;
char *charPtr1;
char *charPtr2;
char cmd;

#define DURATION_microSec 2620 // Sampling Rate of 360 Hz (1.20 * 2 * 150 Hz)



//*******************************
// Set-Up
//*******************************

void setup()  
{
 
 intPtr = &valueECG;
 charPtr1 = (char*) intPtr;
 charPtr2 = charPtr1 + 1;
 cmd = 0x12; 
 Serial.begin(115200); 

}
//*******************************
// Main Loop
//*******************************
void loop() // run over and over
{
  
  //If data is available, read it:
  if (Serial.available()){
        cmd = (char) Serial.read();
    }

 if (cmd == START){
        valueECG = analogRead(analogPin); 
        writeECG();
        delayMicroseconds(DURATION_microSec);
  }
  else if ((cmd == STOP) || (cmd == DISCONNECT)){
        //RFduino_systemReset();
  }
 
}


//*******************************
// WriteECG()
// Transmit data via Bluetooth to the Android Application
//*******************************
void writeECG(){
    Serial.write('\n'); 
    Serial.write(*charPtr1);
    Serial.write(*charPtr2);
}
