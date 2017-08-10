//digital 2 is ok(pin 2) but the other failed?
int buzzer=2;

void setup() 
{ 
    pinMode(buzzer,OUTPUT);
    pinMode(1,OUTPUT);
} 

void loop() 
{ 
    unsigned char i,j;
          while(1) 
          { 
                  digitalWrite(1,HIGH);   
                  delay(1500);              
                  for(i=0;i<80;i++)
                  { 
                    digitalWrite(buzzer,HIGH);
                    delay(1);
                    digitalWrite(buzzer,LOW);
                    delay(1);
                  } 

                  for(i=0;i<100;i++)
                  { 
                    digitalWrite(buzzer,HIGH);
                    delay(2);
                    digitalWrite(buzzer,LOW);
                    delay(2);
                  } 
                  digitalWrite(1,LOW);                        
                  delay(1500);
          } 
    } 

