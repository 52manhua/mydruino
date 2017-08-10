/*
 * 这个程序可以让数码管按顺序变化
 */
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
  for(int i=1;i<129;i=i+i)
  {
    digitalWrite(latch,LOW);
    shiftOut(data1,clock1,MSBFIRST,i);
    digitalWrite(latch,HIGH);
    delay(1000);
  }
}
