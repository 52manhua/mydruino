#include <TM1637.h>
#define CLK 3//pins definitions for TM1637 and can be changed to other ports       
#define DIO 2
TM1637 tm1637(CLK,DIO);
//
#include <dht.h>
dht DHT;  
#define DHT11_PIN 15//put the sensor in the digital pin 4  
  
void setup()  
{  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  //
 Serial.begin(9600);
}  

int showmode=0;
void loop()  
{  
// READ DATA  
//  Serial.print("DHT11, \t");  
 int chk = DHT.read11(DHT11_PIN);  
  switch (chk)  
  {  
    case 0:  Serial.print("OK,\t"); break;  
    case -1: Serial.print("Checksum error,\t"); break;  
    case -2: Serial.print("Time out error,\t"); break;  
    default: Serial.print("Unknown error,\t"); break;  
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
  Serial.print(" [0] is");Serial.print((int)tempchar[0]);Serial.print("   ");
  Serial.print(DHT.humidity,1);  
  Serial.print(",\t");  
  Serial.println(DHT.temperature,1);  
  if(showmode==0){
    tm1637.display(0,tempchar[0]-48);
    tm1637.display(1,tempchar[1]-48);
    tm1637.display(3,12);
    showmode=1;
  }else{
    tm1637.display(0,humchar[0]-48);
    tm1637.display(1,humchar[1]-48);
    tm1637.display(3,13);
    showmode=0;
  }
  delay(1000);  
}  

//  
// END OF FILE  
//  
