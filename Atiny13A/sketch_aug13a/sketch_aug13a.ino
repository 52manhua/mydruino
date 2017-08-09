const int butp=2;const int ledp=3;
int states=0;

void setup(){
  pinMode(butp,INPUT);
  pinMode(ledp,OUTPUT);
}

void loop(){
  states = digitalRead(butp);
  
  if(states == HIGH){
    digitalWrite(ledp,HIGH);
  }
  else{
    digitalWrite(ledp,LOW);
  }
}
