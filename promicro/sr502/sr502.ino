/*
  Music define

*/
#define NOTE_D0 -1
#define NOTE_D1 262
#define NOTE_D2 294
#define NOTE_D3 330
#define NOTE_D4 350
#define NOTE_D5 393
#define NOTE_D6 441
#define NOTE_D7 495

#define NOTE_DL1 131
#define NOTE_DL2 147
#define NOTE_DL3 165
#define NOTE_DL4 175
#define NOTE_DL5 196
#define NOTE_DL6 221
#define NOTE_DL7 248

#define NOTE_DH1 525
#define NOTE_DH2 589
#define NOTE_DH3 661
#define NOTE_DH4 700
#define NOTE_DH5 786
#define NOTE_DH6 882
#define NOTE_DH7 990

#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

//这部分是用英文对应了拍子，这样后面也比较好看
int tune[] =
{
  NOTE_D1,NOTE_D1,NOTE_D5,NOTE_D5,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D0,
  NOTE_D4,NOTE_D4,NOTE_D3,NOTE_D3,NOTE_D2,NOTE_D2,NOTE_D1,NOTE_D0,
  NOTE_D5,NOTE_D5,NOTE_D4,NOTE_D4,NOTE_D3,NOTE_D3,NOTE_D2,NOTE_D0,
  NOTE_D5,NOTE_D5,NOTE_D4,NOTE_D4,NOTE_D3,NOTE_D3,NOTE_D2,NOTE_D0,
  NOTE_D1,NOTE_D1,NOTE_D5,NOTE_D5,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D0,
  NOTE_D4,NOTE_D4,NOTE_D3,NOTE_D3,NOTE_D2,NOTE_D2,NOTE_D1,NOTE_D0,
  
};//这部分就是整首曲子的音符部分，用了一个序列定义为tune，整数

float duration[]=
{
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  
};//这部分是整首曲子的接拍部分，也定义个序列duration，浮点（数组的个数和前面音符的个数是一样的，一一对应么）
int length;//这里定义一个变量，后面用来表示共有多少个音符

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
  /*music define*/
   length = sizeof(tune)/sizeof(tune[0]);//这里用了一个sizeof函数，可以查出tone序列里有多少个音符
  //
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
    
   for(int x=0;x<length;x++)//循环音符的次数
   {
    tone(armp,tune[x]);//此函数依次播放tune序列里的数组，即每个音符
    delay(400*duration[x]);//每个音符持续的时间，即节拍duration，400是调整时间的越大，曲子速度越慢，越小曲子速度越快，自己掌握吧
    noTone(armp);//停止当前音符，进入下一音符
   }
}
