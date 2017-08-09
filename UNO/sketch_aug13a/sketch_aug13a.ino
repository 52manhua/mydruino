    int LM35=A0;//LM35测试端接模拟端A7
    float float_LM35;//使用浮点记录并计算数据
    float m;
    void setup()
    {
       Serial.begin(9600);//注意这个首字母必须大写
    }
    void loop()
    {
      m=analogRead(LM35);//读取A7端口模拟值
      float_LM35=(float)m/1024*500;//计算结果
      Serial.println(float_LM35,4);//定义小数点后位数
      delay(500);//每500毫秒读取一次温度
    }
