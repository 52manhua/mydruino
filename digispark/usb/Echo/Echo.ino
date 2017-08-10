#include <DigiUSB.h>

void setup() {
  DigiUSB.begin();
  pinMode(1,OUTPUT);
}

void get_input() {
  int lastRead;
  // when there are no characters to read, or the character isn't a newline
  while (true) { // loop forever
    if (DigiUSB.available()) {
      // something to read
      lastRead = DigiUSB.read();
      DigiUSB.write(lastRead);

      if(lastRead == 48)digitalWrite(1,HIGH);
      if(lastRead == 49)digitalWrite(1,LOW);
      
      if (lastRead == '\n') {
        break; // when we get a newline, break out of loop
      }
    }
    
    // refresh the usb port for 10 milliseconds
    DigiUSB.delay(10);
  }
}

void loop() {
  // print output
  DigiUSB.println("Waiting for input...");
  // get input
  get_input();
}
