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
static uint32_t timer;
static uint32_t ptimer;

const int pdelay=1000;
const int ledPin = 3;
boolean ledStatus;

char* on = "ON";
char* off = "OFF";
char* statusLabel;
char* buttonLabel;
//ping get
char* lastmessage;
static boolean doping;

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
  
  // call this to report others pinging us
  ether.registerPingCallback(gotPinged);
  doping=false;  
  timer = -9999999; // start timing out right away
  ether.parseIp(ether.hisip, "192.168.99.155");
}

//pings 
  // called when a ping comes in (replies to it are automatic)
  static void gotPinged (byte* ptr) {
    ether.printIp(">>> ping from: ", ptr);
  } 
  
void loop() {

 //
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
//  delay(1000);
//  ether.printIp("IP:  ", ether.myip);
//  ether.printIp("Netmask:  ", ether.netmask);
//  ether.printIp("gwip:  ", ether.gwip);
 
 //messages got 
  if(pos) {
   
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=ON") != 0) {
      Serial.println("Received ON command");
      ledStatus = true;
    }
 
     if(strstr((char *)Ethernet::buffer + pos, "GET /?status=PING") != 0) {
      Serial.println("Received PING command");
      doping = true;
      ledStatus=false;
    }
   
    if(ledStatus) {
      digitalWrite(ledPin, HIGH);
      statusLabel = on;
      buttonLabel = off;
      
      delay(pdelay);
      digitalWrite(ledPin, LOW);
      statusLabel = off;
      buttonLabel = on;     
    } 
    

  
    BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
      "<html><head><title>NET BUTTON</title></head>"
      "<body>You Can click the button at remote~: $S "
      "<a href=\"/?status=ON\"><input type=\"button\" value=\"$S\"></a>"
      "<br>Ping status:$S<a href=\"/?status=PING\"><input type=\"button\" value=\"PING\"></a>"
      "</body></html>"      
      ), statusLabel, buttonLabel,lastmessage);
    ether.httpServerReply(bfill.position());
  }
 
 pings(); 
  
}

void pings(){
  //get ping response
  word len = ether.packetReceive(); // go receive new packets
  word pos = ether.packetLoop(len); // respond to incoming pings
  
  // report whenever a reply to our outgoing ping comes back
  if (len > 0 && ether.packetLoopIcmpCheckReply(ether.hisip)) {
    Serial.print("  ");
    Serial.print((micros() - timer) * 0.001, 3);
    Serial.println(" ms");
    lastmessage=" Get!";
    doping=false;
  }else{
//    Serial.print("There is some errors in Desip:");
//    ether.printIp(ether.hisip);
//    Serial.println();
  if(micros() - ptimer >= 15000000)lastmessage="  waiting~";
  }
  
  // ping a remote server once every few seconds
 //timing in micro second
  //if (micros() - timer >= 15000000) {
    if(doping){
    ether.printIp("Pinging: ", ether.hisip);
    timer = micros();
    ether.clientIcmpRequest(ether.hisip);
    //save ping timer
    ptimer=micros();
    
    doping=false;
  }
  //}
}
