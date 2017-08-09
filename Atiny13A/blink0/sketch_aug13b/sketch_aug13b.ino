const int ledp=0;

void setup(){
  pinMode(ledp,OUTPUT);
}

void loop(){

    digitalWrite(ledp,HIGH);
    delay(1000);
    digitalWrite(ledp,LOW);
    delay(1000);

}
