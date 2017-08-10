void setup() {
  //all digital Pin 0,1,2 Test:
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(1, HIGH); 
  digitalWrite(2, LOW); 
  digitalWrite(0, HIGH);
  delay(500);
  digitalWrite(1, LOW); 
  digitalWrite(2, HIGH); 
  digitalWrite(0, LOW);
  delay(500);
}
