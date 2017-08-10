int data = 2;
int clock = 4;
int latch = 5;
int ledState = 0;


const int ON = HIGH;
const int OFF = LOW;

void setup()
{
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);

}

void loop()
{
  for(int i=0;i<256;i++){
      updateLEDs(i);      
      delay(800);
    }
  
}

void updateLEDs(int value)
{
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, value);
  digitalWrite(latch, HIGH);
}
