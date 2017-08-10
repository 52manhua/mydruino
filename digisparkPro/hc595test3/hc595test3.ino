int latch=5;
int clock1=4;
int data1=2;

void setup()
{
  pinMode(latch,OUTPUT);
  pinMode(clock1,OUTPUT);
  pinMode(data1,OUTPUT);  
}

void loop()
{
  for(int i=1;i<129;i=1+2*i)
  {
    digitalWrite(latch,LOW);
    shiftOut(data1,clock1,MSBFIRST,i);
    digitalWrite(latch,HIGH);
    delay(500);
  }
}
