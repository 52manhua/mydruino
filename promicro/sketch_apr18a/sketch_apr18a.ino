#include "Keyboard.h"
void setup() {
  // initialize control over the keyboard:
  Keyboard.begin();


}

void loop() {
  // put your main code here, to run repeatedly:
  Keyboard.print("Hello Kitty!");
  delay(5000);
}
