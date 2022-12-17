#include <TimeLib.h>
unsigned long prevv=0,current=0;
int forceonn=0;
bool allon=0;
typedef struct struct_messagea {
  float battvol;
  int invmosstat;
  int timeexp;
  int pwrsupp;
  int lowpwroff;
  int checkvol;
  int currprev;
  int usedmin;
  int invenable;
  int lightr;
  int startt;
  int stopp;
  int hourr;
  int minutee;
  int secondd;
} struct_messagea;
struct_messagea senddata;
struct_messagea recvdata;
bool invofff=0;
bool safemode=0;
uint8_t broadcastAddress[] = {0x2C, 0xF4, 0x32, 0x17, 0x3C, 0x94};
//2C:F4:32:17:3C:94
unsigned int daypeeks=1;
#include <espnow.h>
bool highh=1;
unsigned long peakss=0;
float prevvolt=0;
int tid;
bool timeauto=1;
// Fill-in information from your Blynk Template here
#define inverter_mos 0//.....
#define pump_mos 14//.....---
#define inverter_ac 5//.....
#define powersupplay_ac 12//......
#define Ac1 4//done relay
#define charge_1_mos 16//free
#define mainpower_mos 15//invertermainrelay
#define batt_voltage A0//.....
#define ac_inn 13//......
#include "ThingSpeak.h"
bool firsttimeinv=1;
#include <ESP8266WiFi.h>
WiFiClient  client;
#define Ac2 1
bool invenable=1;
unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "R96GMATVWIODZACC";

#define chargeled 2
int deepcharge = 0;
bool settt=0;
bool usedminute = 0;
bool timeexpired=0;
bool powersupplaymadehigh = 0;
bool checkvol=1;
bool lowpoweroff=0;
float batteryvoltage = 0;
unsigned long cur = 0;
unsigned long prev = 0;
unsigned long absorbtion = 0;
bool resu = 0;
bool invertermos_state = 0;
bool ac_innc = 0;
int bootwithoutwifi=0;
bool power1=0,power2=0,power3=0;

#define BLYNK_TEMPLATE_ID           "TMPL7W-4TEk7"
#define BLYNK_DEVICE_NAME           "Inverter"
//#define BLYNK_AUTH_TOKEN            "hV7y0oeEdVi7OZZVfBsVLf_DQdOpieas"

#include <ESP8266WiFi.h>
#include <espnow.h>

bool r8 = 0;
const char* ssidd     = "hlo12";
const char* passs = "1231231234";

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BlynkTimer timerr;
BlynkTimer nett;

WidgetTerminal terminal(V16);

#include <WidgetRTC.h>
WidgetRTC rtc;


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&recvdata, incomingData, sizeof(recvdata));

}
 
void setup()
{


  
  pinMode(inverter_mos, OUTPUT);
  pinMode(pump_mos, OUTPUT);
  pinMode(inverter_ac, OUTPUT);
  pinMode(powersupplay_ac, OUTPUT);
  pinMode(Ac1, OUTPUT);
  pinMode(charge_1_mos, OUTPUT);
  pinMode(mainpower_mos, OUTPUT);
  digitalWrite(charge_1_mos,LOW);

  pinMode(ac_inn, INPUT_PULLUP);
  pinMode(Ac2,FUNCTION_3);
  pinMode(Ac2, OUTPUT);
  pinMode(chargeled, INPUT_PULLUP);
    digitalWrite(mainpower_mos, LOW);

  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
  digitalWrite(pump_mos, HIGH);
    digitalWrite(Ac2, HIGH);

  digitalWrite(inverter_ac, LOW);
  digitalWrite(powersupplay_ac, LOW);
  digitalWrite(Ac1, HIGH);
  powersupplaymadehigh=0;
  attachInterrupt(digitalPinToInterrupt(ac_inn), detectsMovement, CHANGE);
nett.setInterval(1456,sendd);

timerr.setInterval(51,mainthread);
timerr.setInterval(120,subthread1);
timerr.setInterval(6004,nowsend);

timerr.setInterval(700,protection);
timerr.setInterval(5001,autolight);
timerr.setInterval(20000,wificonn);

    WiFi.mode(WIFI_AP_STA);

  WiFi.begin(ssidd, passs);
  for (int wik = 0; wik <= 20; wik++) {
    delay(500);
    yield();
    bootwithoutwifi = 1;

    if (WiFi.status() == WL_CONNECTED) {
      bootwithoutwifi = 0;
      yield();
      break;
      break;

    }
    yield();

  }
//  Serial.begin(115200);
  delay(100);

  
  if (bootwithoutwifi == 0) {
    Serial.println("wifion");
    BlynkEdgent.begin();
    
  ThingSpeak.begin(client);
  } else {
    Serial.println("wifion");
  }


if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_register_recv_cb(OnDataRecv);

}



void wificonn(){


    WiFi.begin(ssidd, passs);

}
void autolight(){
  


if(hour()<16){
  if(batteryvoltage < 12.8 && checkvol==1){
  checkvol=0;
  }
}
if(hour()==2){
  daypeeks=0;
  invofff=0;
  allon=0;
}

if(allon==1){


  digitalWrite(mainpower_mos, HIGH);
  digitalWrite(Ac1, LOW);
  digitalWrite(Ac2, HIGH);

}else{
  
if((hour()==18 || hour()==19 || hour()==20) &&bootwithoutwifi == 0){
if(ac_innc == 1){
      digitalWrite(mainpower_mos, HIGH);
  digitalWrite(Ac1, LOW);
  digitalWrite(Ac2, HIGH);

}else if(timeexpired==1 && invertermos_state==1){
  digitalWrite(Ac1, HIGH);

   digitalWrite(Ac2, LOW);
      digitalWrite(mainpower_mos, HIGH);

  
}else{
 digitalWrite(Ac1, HIGH);

   digitalWrite(Ac2, HIGH);
      digitalWrite(mainpower_mos, LOW);

  
}

}else{
  
 digitalWrite(Ac1, HIGH);

   digitalWrite(Ac2, HIGH);
      digitalWrite(mainpower_mos, LOW);

}

}

}


void protection(){


if(!digitalRead(ac_inn)){
      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
}
  if (batteryvoltage < 12) {
lowpoweroff=1;

  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
  }

if(hour()<18 && timeexpired==1){
  
  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
}
if(safemode==1 && (hour()<18 || hour()>22)){


      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
timeexpired=1;
    
  
}
if(hour() < 7|| hour()>18){
  if (batteryvoltage < 12.07) {


      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
timeexpired=1;
    
  }
}else{

  if (batteryvoltage < 12.42) {


      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
timeexpired=1;
    
  }



  
}





}
void loop() {
  
  if (WiFi.status() == WL_CONNECTED) {
    BlynkEdgent.run();
    nett.run();
  }
timerr.run();
}


ICACHE_RAM_ATTR void detectsMovement() {

  
  if (digitalRead(ac_inn)) {
    Serial.println("inst");
    digitalWrite(inverter_ac, LOW);
    

  }else{

    
       settt=0;

  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
  }
            timerr.setTimeout(1000, pwcn);
  terminal.println("run");
    terminal.flush();
}

void mainthread(){
//Serial.print("runn");

if (batteryvoltage > 13.8 && highh==1) {
  highh=0;
}

  batteryvoltage = analogRead(A0)*0.0155755396;

//Serial.print(batteryvoltage);




  if (!digitalRead(ac_inn)) { //low yes
    chargeroutine();



    if (!ac_innc) {
      ac_innc = 1;
      chargesetup();
      terminal.println("accon");
      terminal.flush();

    }

  } else {
    
    if (ac_innc) {
      ac_innc = 0;
      invertersetup();
      
      terminal.println("accoff");
      terminal.flush();
    }
if(!lowpoweroff){
  
  

    inverterroutine();



  }else{
//    terminal.println("lowpow");

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;

    
  }
}
}
void nowsend(){

  

  
 senddata.battvol=batteryvoltage;
  senddata.invmosstat=invertermos_state;
  senddata.timeexp=timeexpired;
  senddata.pwrsupp=(power1||power2||power3);
  senddata.lowpwroff=lowpoweroff;
  senddata.checkvol=checkvol;
  senddata.currprev=(current-prevv);
  senddata.usedmin=usedminute;
  senddata.invenable=invenable;
  senddata.lightr=timeauto;


    senddata.hourr=hour();
  senddata.minutee=minute();
  senddata.secondd=second();

esp_now_send(broadcastAddress, (uint8_t *) &senddata, sizeof(senddata));



}

void subthread1(){


  if(batteryvoltage > 13 && checkvol==0){
  checkvol=1;
  }
if (batteryvoltage < 13.13 && highh==0 && hour()<16) {
  highh=1;
  peakss++;
  daypeeks++;
}


  
if((power1||power2||power3)&&powersupplaymadehigh==0){
powersupplaymadehigh=1;
  digitalWrite(powersupplay_ac, HIGH);

  
}

if(powersupplaymadehigh==1 && !(power1||power2||power3)){
powersupplaymadehigh=0;

  digitalWrite(powersupplay_ac, LOW);

  
}

  if (batteryvoltage < 12.04) {
lowpoweroff=1;

  }


  if (batteryvoltage > 12.5) {
lowpoweroff=0;
  }



  
//  if (batteryvoltage < 12.8 && settt==0 && ac_innc==1) {
//    power3=1;

//timerr.deleteTimer(tid);
//    tid=timerr.setTimeout(3900000, stopcharge);
//   settt=1;
//  }

}



void inverterroutine() {

usedminute=(!digitalRead(chargeled));

  if(timeexpired==0){
current=millis();


  if ((current-prevv)>45000){
    terminal.println("timeup");
    terminal.flush();


  if(firsttimeinv==1&&batteryvoltage < 12.35 &&invertermos_state == 1){
firsttimeinv=0;
digitalWrite(inverter_mos, HIGH);
delay(2500);
digitalWrite(inverter_mos, LOW);
    
  }

    
  if (!usedminute && forceonn==0){
      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
timeexpired=1;

    
  }else{

prevv=millis();
    
  }
}
}else{
  
  if (batteryvoltage < 12.3) {
      

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
daypeeks=0;
allon=0;

  }




      



if(allon ==1){
if(batteryvoltage > 12.25){
  
      digitalWrite(inverter_mos, LOW);
      invertermos_state = 1;
      
}else{
allon=0;

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      





  
}




}else{

  

  if(timeauto==1){
if((hour()==19 || hour()==20) &&(day()!=15||day()!=16) && bootwithoutwifi == 0){
if(batteryvoltage > 12.25 && daypeeks>0){
  
      digitalWrite(inverter_mos, LOW);
      invertermos_state = 1;
      
}else{

      daypeeks=0;

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      





  
}





}else{
      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      
}


  
}else{

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      
  
}
}

}
}


void invertersetup() {
  digitalWrite(Ac2, HIGH);
  digitalWrite(Ac1, HIGH);
  digitalWrite(mainpower_mos, LOW);
firsttimeinv=1;
  resu = 0;
  if(invenable==1){
  digitalWrite(inverter_mos, LOW);
  invertermos_state = 1;
  timeexpired=0;
  }else{
  timeexpired=1;

    
  }
//        checkvol=0;

power1=0;
power2=0;
power3=0;
//    digitalWrite(powersupplay_ac, LOW); // Set digital pin 2 HIGH
    terminal.println("invstart");
prevv=millis();

prevvolt=batteryvoltage;



}





void chargeroutine(){
  
      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
}

void chargesetup(){
       settt=0;
  digitalWrite(Ac2, HIGH);

  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
}

void pwcn() {

  if (!digitalRead(ac_inn)) {
    digitalWrite(inverter_ac, HIGH);
    Serial.println("inst1");

  }
      Serial.println("inst2");

}

void stopcharge() {
     settt=0;
//    digitalWrite(powersupplay_ac, LOW); // Set digital pin 2 HIGH
power3=0;
}

















void alloff(){

allon=0;


}



BLYNK_WRITE(V20) // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1)
  {
    allon=1;
    timerr.setTimeout(45000, alloff);

    
    terminal.println(param.asInt());
        terminal.flush();
}else
      {
        }
      }

BLYNK_WRITE(V15) // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1)
  {
    
if(digitalRead(ac_inn)){
    invertersetup();
    
    terminal.println(param.asInt());
        terminal.flush();
}
  }else
      {
        }
      }
    


BLYNK_WRITE(V17) // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1)
  {
    
    terminal.println(param.asInt());
        terminal.flush();

          digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
timeexpired=1;

    
  }else
      {
        }
      }




      
BLYNK_WRITE(V18) // Executes when the value of virtual pin 0 changes
{
  
    timeauto=param.asInt();
    terminal.println(param.asInt());
        terminal.flush();

    
    
      
        
      }


  
      
BLYNK_WRITE(V88) // Executes when the value of virtual pin 0 changes
{
  
    safemode=param.asInt();
    terminal.println(param.asInt());
        terminal.flush();

    
    
      
        
      }

//      
//BLYNK_WRITE(V67) // Executes when the value of virtual pin 0 changes
//{
//  
//    daypeeks=param.asInt();
//    terminal.println(param.asInt());
//        terminal.flush();
//
//    
//    
//      
//}
      
      
BLYNK_WRITE(V55) // Executes when the value of virtual pin 0 changes
{
  
    invenable=param.asInt();
    terminal.println(param.asInt());
        terminal.flush();

    
    
      
        
      }



  
BLYNK_WRITE(V19) // Executes when the value of virtual pin 0 changes
{
  
    forceonn=param.asInt();
    terminal.println(param.asInt());
        terminal.flush();

    
    
      
        
      }

      
BLYNK_WRITE(V16) // Executes when the value of virtual pin 0 changes
{



terminal.println(batteryvoltage);
terminal.println(lowpoweroff);
terminal.println(invertermos_state);
terminal.println(WiFi.macAddress());


    terminal.flush();

  terminal.println(hour());
    terminal.println(minute());
    terminal.flush();
  
}

BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
{

  if (param.asInt() > 1)
  {
    // execute this code if the switch widget is now ON
    analogWrite(pump_mos, param.asInt()); // Set digital pin 2 HIGH
//    digitalWrite(powersupplay_ac, HIGH); // Set digital pin 2 HIGH
    power1=1;
    terminal.println(param.asInt());
  }else
      {
        // execute this code if the switch widget is now OFF
        digitalWrite(pump_mos, LOW); // Set digital pin 2 LOW
//          digitalWrite(powersupplay_ac, LOW); // Set digital pin 2 HIGH
          power1=0;
        
      }
    }


    BLYNK_CONNECTED() {                  //When device is connected to server...
  rtc.begin();

}


void sendd(){
 if (WiFi.status() == WL_CONNECTED) {
Blynk.virtualWrite(V8,batteryvoltage);

  Blynk.virtualWrite(V1,invertermos_state);
  Blynk.virtualWrite(V4,(power1||power2||power3));
    Blynk.virtualWrite(V7,lowpoweroff);
//    Blynk.virtualWrite(V7,lowpoweroff);
    Blynk.virtualWrite(V9,checkvol);
        Blynk.virtualWrite(V14,usedminute);


 int aaasdx = ThingSpeak.writeField(myChannelNumber, 1, batteryvoltage, myWriteAPIKey);
         Blynk.virtualWrite(V75,peakss);

    Blynk.virtualWrite(V10,current);
        Blynk.virtualWrite(V11,prevv);
        Blynk.virtualWrite(V13,(current-prevv));
                Blynk.virtualWrite(V2,timeexpired);
                Blynk.virtualWrite(V67,daypeeks);

}}
