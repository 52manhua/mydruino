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
//中间信号 STCP
int latchPin = 5;
//将4号线接至 SHCP （最接近 GND）然后，接 5V 电源 测试成功 
int clockPin = 4;
//最接近电源信号 DS
int dataPin = 2;
 
//button
int inpin=8;int bstate=0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //input button
  pinMode(inpin,INPUT);
}

void sevenSegWrite(byte digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]); 
  digitalWrite(latchPin, HIGH);

}
 
int ccount=0;
void loop() {
  //get input
  bstate=digitalRead(inpin);
  if(bstate==HIGH){

    sevenSegWrite(ccount);
    Serial.println(ccount);
    ccount++;   
  }
  delay(200);
}
