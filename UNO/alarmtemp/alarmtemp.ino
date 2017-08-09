//in alarm
const int alarm=8;const int abtn=3;

    int LM35=A0;//LM35测试端接模拟端A7
    float float_LM35;//使用浮点记录并计算数据
    float m;
    //getbutton
    int bsta=0;float tsave=0;
    void setup()
    {
     //define adjust abtn
     pinMode(abtn,INPUT);
      //define alarm
     pinMode(alarm,OUTPUT);
      
      //define serial 
      Serial.begin(9600);//注意这个首字母必须大写
    }
    void loop()
    {
      bsta=digitalRead(abtn);
      m=analogRead(LM35);//读取A7端口模拟值
      float_LM35=(float)m/1024*500;//计算结果
      Serial.println(float_LM35,4);//定义小数点后位数
      delay(500);//每500毫秒读取一次温度
      //save the adjvalue
      if(bsta==HIGH){
        tsave=float_LM35;
      }else{
        //nothing
        Serial.print("tsave= ");Serial.println(tsave);
      }
      //change the alarm
      if(float_LM35>tsave+2){
        digitalWrite(alarm,HIGH);
      }else{
        digitalWrite(alarm,LOW);
      }
  }
