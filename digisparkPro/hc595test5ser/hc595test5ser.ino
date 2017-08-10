// Lab13 使用 74HC595 與七段顯示器製作倒數功能
// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7
//                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED

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

// 接 74HC595 的 ST_CP (pin 12,latch pin)
int latchPin = 5;
// 接 74HC595 的 SH_CP (pin 11, clock pin)
int clockPin = 4;
// 接 74HC595 的 DS (pin 14)
int dataPin = 2;
 

void setup() {
  // 將 latchPin, clockPin, dataPin 設置為輸出
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void sevenSegWrite(byte digit) {
  // 送資料前要先把 latchPin 拉成低電位
  digitalWrite(latchPin, LOW);
  // 送出數字的位元資料 (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]); 
  // 送完資料後要把 latchPin 拉回成高電位
  digitalWrite(latchPin, HIGH);

}
 
void loop() {      
  // 從 9 倒數到 0
//  for (byte digit = 10; digit > 0; --digit) {
//  // if (Serial.available() > 0) {
//  sevenSegWrite(Serial.read()-48);
//   delay(1000);
//   }
  sevenSegWrite(7);
}



