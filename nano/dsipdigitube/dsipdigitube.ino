//boss: show 0.35
// include the SevenSegmentTM1637 library
#include "SevenSegmentTM1637.h"

const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

float f=0.35;

void setup(){
  Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
  //display.print(2.85);      // display INIT on the display
  delay(2000);  
}

void loop(){
  byte  rawData;
  display.print("256");
  // display degree symbol on position 3 plus set lower colon
  rawData = B11100011;
  display.printRaw(rawData, 3);
  //
  display.setColonOn(1);
  delay(1000);
  
  display.clear();
  int a = f * 100;
  display.print(a);
  delay(1000);
}
