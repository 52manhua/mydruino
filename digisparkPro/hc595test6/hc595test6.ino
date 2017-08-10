
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110,  // = 9
                             };


int latchPin = 5;
int clockPin = 4;
int dataPin = 2;
//////
int ch=0; 

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void sevenSegWrite(byte digit) {

  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]); 

  digitalWrite(latchPin, HIGH);

}
 
void loop() {      

//  for (byte digit = 10; digit > 0; --digit) {
//  sevenSegWrite(digit);
//    delay(2000);
//   }

if(ch==0){
    sevenSegWrite(7);
    ch=1;
  }
}



