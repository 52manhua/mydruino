int state=0;
int a_state=0;
//mq-2 input port 12
int d_getmq=12;
int a_getmq=A0;
//led output
int oled=2;

//show the value
// include the SevenSegmentTM1637 library
#include "SevenSegmentTM1637.h"
const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);


void setup(){
  pinMode(oled,OUTPUT);
  pinMode(a_getmq,INPUT);
  
  Serial.begin(9600);
  //set up the tm1637
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
}

void loop(){
  delay(1000);
  //state=digitalRead(d_getmq);
  
  if( state == 1){
    digitalWrite(oled, HIGH);
  }else{
    digitalWrite(oled, LOW);
  }
  
  a_state=analogRead(0);
  float vol=5.00*(a_state/1023.00);
  Serial.println(vol);
  //display in tm1637
  display.clear();
  int a = vol * 100;
  display.print(a); 
  
  if(vol < 1){
    byte  rawData;
    // display degree symbol on position 3 plus set lower colon
    rawData = B11100011;
    display.printRaw(rawData, 3);
  }
  
 if( vol > 0.6){
    digitalWrite(oled, HIGH);
  }else{
    digitalWrite(oled, LOW);
  }
}
