#include <EtherCard.h>

static byte mymac[] = {0x74,0x69,0x69,0x2D,0x30,0x31}; ///不要修改这里，如果不行再试修改
static byte myip[] = {192,168,99,247};
// gateway ip address
static byte gwip[] = { 192,168,99,1 };
//dns ip
static byte dnsip[]={192,168,99,1};
//netmask
static byte netmask[]={255,255,255,0};
byte Ethernet::buffer[700];

const int ledPin = 3;
boolean ledStatus;

char* on = "ON";
char* off = "OFF";
char* statusLabel;
char* buttonLabel;

void setup () {

  Serial.begin(9600);
  Serial.println("WebLed Demo");

  if (!ether.begin(sizeof Ethernet::buffer, mymac, 10))
    Serial.println( "Failed to access Ethernet controller");
else
   Serial.println("Ethernet controller initialized");

  if (!ether.staticSetup(myip,gwip,dnsip,netmask)){
    Serial.println("Failed to set IP address");
  }else{
    Serial.println("Set IP OK!");
  }

  Serial.println();
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  ledStatus = false;
}
  
void loop() {

  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
//  delay(1000);
//  ether.printIp("IP:  ", ether.myip);
//  ether.printIp("Netmask:  ", ether.netmask);
//  ether.printIp("gwip:  ", ether.gwip);
  
  if(pos) {
   
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=ON") != 0) {
      Serial.println("Received ON command");
      ledStatus = true;
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=OFF") != 0) {
      Serial.println("Received OFF command");
      ledStatus = false;
    }
   
    if(ledStatus) {
      digitalWrite(ledPin, HIGH);
      statusLabel = on;
      buttonLabel = off;
    } else {
      digitalWrite(ledPin, LOW);
      statusLabel = off;
      buttonLabel = on;
    }
      
    BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
      "<html><head><title>WebLed</title></head>"
      "<body>LED Status: $S "
      "<a href=\"/?status=$S\"><input type=\"button\" value=\"$S\"></a>"
      "</body></html>"      
      ), statusLabel, buttonLabel, buttonLabel);
    ether.httpServerReply(bfill.position());
  }
}
