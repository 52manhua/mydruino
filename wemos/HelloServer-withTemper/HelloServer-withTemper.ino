#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "TP-Link_Gold";
const char* password = "yc888888";

ESP8266WebServer server(80);

const int led = 13;

//读取温度
float float_LM35;//使用浮点记录并计算数据
float m;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
  //server.send(200, "text/plain", "this works as well\n");

   m=analogRead(A0);//读取A0端口模拟值
   //3.3v 1024*330 5.0v 1024*500
   float_LM35=(float)m/1024*330;//计算结果
  // Serial.println(float_LM35,4);//定义小数点后位数

  char charVal[7];               //temporarily holds data from vals 
  String stringVal = "";     //data on buff is copied to this string
  
  dtostrf(float_LM35, 4, 4, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  //convert chararray to string
  for(int i=0;i<sizeof(charVal);i++)
  {
    stringVal+=charVal[i];
  }
    server.send(200,"text/plain",stringVal+"\n");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
