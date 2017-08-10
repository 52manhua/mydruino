#include <TM1637.h>
//LED显示 Clk 3 io口  2  温湿度计 11 口？
#define CLK 3//pins definitions for TM1637 and can be changed to other ports       
#define DIO 2
TM1637 tm1637(CLK,DIO);
//温湿度计
#include <dht.h>
dht DHT;  
#define DHT11_PIN 11//put the sensor in the digital pin 11
  
void setup()  
{  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);

  pinMode(1, OUTPUT); //LED on Model A  or Pro
}  

int showmode=0;
void loop()  
{  
  
  // READ DATA  
 int chk = DHT.read11(DHT11_PIN);  
  switch (chk)  
  {  
//    case 0:  digitalWrite(1,HIGH); break;  
////    case -1: Serial.print("Checksum error,\t"); break;  
////    case -2: Serial.print("Time out error,\t"); break;  
//    default: digitalWrite(1,LOW); break;  
  }  
 //humidity and temperature display
 char tempchar[5];char humchar[5];
// int i=5;
 dtostrf(DHT.temperature,2,0,tempchar);
 dtostrf(DHT.humidity,2,0,humchar);
 // DISPLAT DATA  
//  for(i=0;i<=5;i++){
//    Serial.print(tempchar[i]);Serial.print(" ");
//  }
  //[0] is 2 %10
//  Serial.print(" [0] is");Serial.print((int)tempchar[0]);Serial.print("   ");
//  Serial.print(DHT.humidity,1);  
//  Serial.print(",\t");  
//  Serial.println(DHT.temperature,1);  
  if(showmode==0){
    tm1637.display(0,tempchar[0]-48);
    tm1637.display(1,tempchar[1]-48);
    tm1637.display(3,12);
    showmode=1;
    digitalWrite(1,HIGH);
  }else{
    tm1637.display(0,humchar[0]-48);
    tm1637.display(1,humchar[1]-48);
    tm1637.display(3,13);
    showmode=0;
    digitalWrite(1,LOW);
  }
  delay(1000);  
}  
