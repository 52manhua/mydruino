/*
  Melody
Plays a melody
circuit:
* 8-ohm speaker on digital pin 8
* mine is 8
created 21 Jan 2010
modified 30 Aug 2011
by Tom Igoe
This example code is in the public domain.
http://arduino.cc/en/Tutorial/Tone
*/
#include "pitches.h"

// notes in the melody:
// 乐谱
int melody[] = {
NOTE_G4,//5 
NOTE_G4,//5
NOTE_A4,//6
NOTE_G4,//5
NOTE_C5,//1.
NOTE_B4,//7
0,
NOTE_G4,//5
NOTE_G4,//5
NOTE_A4,//6
NOTE_G4,//5
NOTE_D5,//2.
NOTE_C5,//1.
0,
NOTE_G4,//5
NOTE_G4,//5
NOTE_G5,//5.
NOTE_E5,//3.
NOTE_C5,//1.
NOTE_B4,//7
NOTE_A4,//6
0,
NOTE_F5,//4.
NOTE_F5,//4.
NOTE_E5,//3.
NOTE_C5,//1.
NOTE_D5,//2.
NOTE_C5,//1.
0,
};
 
//Duration time of each melody
//延时
int noteDurations[] = {
  8,8,4,4,4,4,4,
  8,8,4,4,4,4,4,
  8,8,4,4,4,4,2,
  8,8,8,4,4,4,2,4
};
  
void setup() {

}

void loop() {
  // loop the music
  music();
}

void music(){
      // iterate over the notes of the melody:
      for (int thisNote = 0; thisNote < sizeof(noteDurations); thisNote++) {
          // to calculate the note duration, take one second
          // divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
              int noteDuration = 1000/noteDurations[thisNote];
              tone(1, melody[thisNote],noteDuration);
          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
              int pauseBetweenNotes = noteDuration * 1.30;
              delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(1);
    }
  }
