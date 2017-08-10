/*
  get infrared port
  led OFF as somebody
  led ON is nobody
*/
const int pinIn=5;int stIn=0;
int scount=0;int lcount=0;int tcount=0;int ncount=0;
//led show
int ledp=9;
//alram
int armp=10;
//inputString
String inputString = "";         // a string to hold incoming data

void setup(){
  pinMode(pinIn,INPUT);
  pinMode(ledp,OUTPUT);
  pinMode(armp,OUTPUT);
  //Serial initial
  Serial.begin(9600);
}

void loop(){
  stIn=digitalRead(pinIn);
  //Serial.println(stIn);
  if(stIn==HIGH){
    //  Serial.println(" Somebody ");
      scount++;  
      digitalWrite(ledp,LOW);
  }else{
    //  Serial.println(" Nobody ");
      digitalWrite(ledp,HIGH);
  }
  lcount++;
  
  Serial.print(scount);Serial.print("/");Serial.print(lcount);
  Serial.print("/");Serial.print(tcount); Serial.print("/"); Serial.println(ncount);
  if(lcount>=60){
    if(scount==0){
    Serial.println("I'm sure it's nobody in 60 seconds");
    ncount++;
  }else{
      digitalWrite(armp,HIGH);
      delay(500);
      digitalWrite(armp,LOW);
    tcount++;
  }
    lcount=0;
    scount=0;  
    //tcount show the 30 mini
    if(tcount>=30){
    //alarm
     alarms();
     tcount=0;   
    }
    //noboby >5 then tcount=0
    if(ncount>=5){
      ncount=0;
      tcount=0;
    }
}
  if(Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      alarms();
    } 
  }

  delay(1000);
}

void alarms(){
     digitalWrite(armp,HIGH);
    delay(2500);
    digitalWrite(armp,LOW);
}
