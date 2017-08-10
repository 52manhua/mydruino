#include<Keyboard.h>
/*
实现翻页键的功能。

*/
int inputpin=4;

void setup() {
  // put your setup code here, to run once:
  /*
  INPUT_PULLUP 信号 取反 
  */
  //pinMode(inputpin,INPUT_PULLUP);
  pinMode(inputpin,INPUT);
  Serial.begin(9600);
  ///
  Keyboard.begin();
}

int state=0;
void loop() {
  // put your main code here, to run repeatedly:
  state=digitalRead(inputpin);
  Serial.println(state);
  
  if(state==1){
    Keyboard.press(KEY_PAGE_DOWN);
    Keyboard.releaseAll();
    state=0;}//only click once~
  delay(50);// 50 is suitable
}
