

#include <Adafruit_NeoPixel.h>

// Define the pin that the NeoPixel data line is connected to
#define PIN D8

// Define the number of NeoPixels
#define NUMPIXELS 6

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Define the analog pin for voltage measurement

// Define the voltage step for lighting up LEDs
#define VOLTAGE_STEP 0.1


#include <TimeLib.h>
unsigned long  current = 0, cprevv = 0, LeDTime = 0;
int forceonn = 0;
bool allon = 0;
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
bool invofff = 0;
bool safemode = 0;
uint8_t broadcastAddress[] = {0x2C, 0xF4, 0x32, 0x17, 0x3C, 0x94};
//2C:F4:32:17:3C:94
unsigned int daypeeks = 1;
unsigned int auxdaypeeks = 1;
unsigned int invonday = 0;
bool repusedmin = 0;
#include <espnow.h>
bool highh = 1;
unsigned long peakss = 0;
float prevvolt = 0;
int tid;
bool timeauto = 1;
// Fill-in information from your Blynk Template here
#define inverter_mos D5//.....inverter dc1
#define pump_mos 1//.....---servo
#define inverter_ac D1//.....delay thing2
#define powersupplay_ac D8//......
#define Ac1 D3//done relay3 cealing
#define charge_1_mos D0//free
#define mainpower_mos D4//invertermainrelay4 koom
#define batt_voltage A0//.....
#define Ac2 D2//6 //main ac

#define ac_inn D7//.....5
#define ussed_min D6
#include "ThingSpeak.h"
bool firsttimeinv = 1;
#include <ESP8266WiFi.h>
WiFiClient  client;
bool invenable = 1;
unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "R96GMATVWIODZACC";

int deepcharge = 0;
bool settt = 0;
bool usedminute = 0;
bool timeexpired = 0;
bool powersupplaymadehigh = 0;
bool checkvol = 1;
bool lowpoweroff = 0;
float batteryvoltage = 0;
unsigned long cur = 0;
unsigned long prev = 0;
unsigned long fiveminute = 0;


bool resu = 0;
bool invertermos_state = 0;
bool ac_innc = 0;
int bootwithoutwifi = 0;
bool power1 = 0, power2 = 0, power3 = 0;
bool invondaya = 0;


bool therewaspower = 1;
#define BLYNK_TEMPLATE_ID           "TMPL7W-4TEk7"
#define BLYNK_DEVICE_NAME           "Inverter"
//#define BLYNK_AUTH_TOKEN            "hV7y0oeEdVi7OZZVfBsVLf_DQdOpieas"

#include <ESP8266WiFi.h>
#include <espnow.h>

bool r8 = 0;
const char* ssidd     = "hlo12";
const char* passs = "1231231234";

#define BLYNK_FIRMWARE_VERSION        "0.3.3"

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
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&recvdata, incomingData, sizeof(recvdata));

}

void setup()
{



  pinMode(inverter_mos, OUTPUT);
  pinMode(inverter_ac, OUTPUT);
  pinMode(powersupplay_ac, OUTPUT);
  pinMode(Ac1, OUTPUT);
  pinMode(charge_1_mos, OUTPUT);
  pinMode(mainpower_mos, OUTPUT);
  digitalWrite(charge_1_mos, HIGH);

  pinMode(ac_inn, INPUT);
  pinMode(Ac2, FUNCTION_3);
  pinMode(Ac2, OUTPUT);
  pinMode(ussed_min, INPUT_PULLUP);
  digitalWrite(mainpower_mos, HIGH);

  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
  digitalWrite(Ac2, HIGH);

  digitalWrite(inverter_ac, HIGH);
  digitalWrite(powersupplay_ac, HIGH);
  digitalWrite(Ac1, HIGH);
  powersupplaymadehigh = 0;
  pixels.begin();

  attachInterrupt(digitalPinToInterrupt(ac_inn), detectsMovement, CHANGE);
  nett.setInterval(1456, sendd);

  timerr.setInterval(51, mainthread);
  timerr.setInterval(120, subthread1);
  // timerr.setInterval(6004, nowsend);

  timerr.setInterval(700, protection);
  timerr.setInterval(5001, autolight);
  timerr.setInterval(20000, wificonn);

  WiFi.mode(WIFI_STA);

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
  pwcn();
}



void wificonn() {


  WiFi.begin(ssidd, passs);

}
void autolight() {



  if (invertermos_state == 1 && timeexpired == 0) {
    updateLEDsBasedOnVoltage(batteryvoltage);

  } else if (ac_innc == 1) {
    updateSingleLEDBasedOnVoltage(batteryvoltage);

  } else if (therewaspower && batteryvoltage > 12.2 && (millis() - LeDTime) < 200000) {
    setAllWhite(250);

  } else if (therewaspower && batteryvoltage > 12.47 && daypeeks > 2) {
    if (hour() == 17 || hour() == 18 || hour() == 19 || hour() == 20 || hour() == 21) {
      int powee = (batteryvoltage - 12.46) * 1520;
      if (powee > 240) {
        powee = 240;
      }
      setAllWhite(powee);

    } else {

      setAllWhite(2);


    }



  } else {
    turnAllOff();

  }







  //  } else if ((hour() == 17 && minute() == 4 && second() < 20)   || (hour() == 6 && minute() == 4 && second() < 20)) {
  //
  //
  //
  //  } else {
  //
  //
  //  }
  //




  //  if (hour() < 16) {
  //    if (batteryvoltage < 12.8 && checkvol == 1) {
  //      checkvol = 0;
  //    }
  //  }

  if (hour() == 12 && minute() == 31 && second() < 20 && ac_innc) {
    therewaspower = 1;


  }




  if (hour() == 2 && minute() == 4) {
    therewaspower = 0;
    daypeeks = 0;
    auxdaypeeks = 0;
    invofff = 0;
    allon = 0;

    if (invondaya) {
      invonday++;
      invondaya = 0;
    }


  }

  if (allon == 1) {


    digitalWrite(mainpower_mos, LOW);
    digitalWrite(Ac1, LOW);
    digitalWrite(Ac2, HIGH);

  } else {

    if ((hour() == 19 || hour() == 20) && bootwithoutwifi == 0 && timeauto == 1) {
      if (ac_innc == 1) {
        digitalWrite(mainpower_mos, LOW);
        digitalWrite(Ac1, LOW);
        digitalWrite(Ac2, HIGH);

      } else if (timeexpired == 1 && invertermos_state == 1) {
        digitalWrite(Ac1, HIGH);

        digitalWrite(Ac2, LOW);
        digitalWrite(mainpower_mos, LOW);


      } else {
        digitalWrite(Ac1, HIGH);

        digitalWrite(Ac2, HIGH);
        digitalWrite(mainpower_mos, HIGH);


      }

    } else {

      digitalWrite(Ac1, HIGH);

      digitalWrite(Ac2, HIGH);
      digitalWrite(mainpower_mos, HIGH);

    }

  }

}


void protection() {



  if (digitalRead(ac_inn)) {
    digitalWrite(inverter_mos, HIGH);
    invertermos_state = 0;
  }
  if (batteryvoltage < 12) {
    lowpoweroff = 1;

    digitalWrite(inverter_mos, HIGH);
    invertermos_state = 0;
  }

  if (hour() < 17 && timeexpired == 1) {

    digitalWrite(inverter_mos, HIGH);
    invertermos_state = 0;
  }
  if (safemode == 1 && (hour() < 16 || hour() > 22)) {


    digitalWrite(inverter_mos, HIGH);
    invertermos_state = 0;
    timeexpired = 1;


  }
  if (hour() < 7 || hour() > 16 || forceonn == 1) {
    if (batteryvoltage < 12.0) {


      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      timeexpired = 1;

    }
  } else {

    if (batteryvoltage < 12.55 || daypeeks == 0) {


      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      timeexpired = 1;

    }




  }





}
void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    BlynkEdgent.run();
    nett.run();
  }
  timerr.run();


  if (lowpoweroff) {

    delay(100);
  }



}


ICACHE_RAM_ATTR void detectsMovement() {


  if (!digitalRead(ac_inn)) {
    Serial.println("inst");
    digitalWrite(inverter_ac, HIGH);


  } else {


    settt = 0;
    terminal.println("intrupt");

    digitalWrite(inverter_mos, HIGH);
    invertermos_state = 0;
  }
  timerr.setTimeout(1000, pwcn);
  terminal.println("run");
  terminal.flush();
}

void mainthread() {
  //Serial.print("runn");

  if (batteryvoltage > 13.89 && highh == 1) {
    highh = 0;
  }

  batteryvoltage = analogRead(A0) * 0.0182997118;








if(batteryvoltage > 14.4){
delay(1000);
  batteryvoltage = analogRead(A0) * 0.0182997118;

if(batteryvoltage > 14.4){
  digitalWrite(charge_1_mos, LOW);


  
}


  
}
if(batteryvoltage < 12.2){

  digitalWrite(charge_1_mos, HIGH);


}


  
  //  batteryvoltage = 12.9;

  //Serial.print(batteryvoltage);

  usedminute = (digitalRead(ussed_min));

  if (usedminute == 0 && repusedmin == 0) {
    delay(1500);
      usedminute = (digitalRead(ussed_min));
  if (usedminute == 0 && repusedmin == 0) {

    if (!digitalRead(ac_inn)) {
      invertersetup();
      fiveminute = millis() - 400000;

      terminal.println("SWICH ON");
      terminal.flush();

    }

    repusedmin = 1;
  }}


  if (usedminute == 1 && repusedmin == 1) {
    delay(1500);
      usedminute = (digitalRead(ussed_min));
      if (usedminute == 1 && repusedmin == 1) {

    repusedmin = 0;

    fiveminute = millis() - 400000;
    terminal.println("SWICH Off");

  }}


  if (digitalRead(ac_inn)) { //low yes
    chargeroutine();



    if (!ac_innc) {
      ac_innc = 1;
      chargesetup();
      terminal.println("accon");
      terminal.flush();

      therewaspower = 1;

    }

  } else {

    if (ac_innc) {
      LeDTime = millis();

      ac_innc = 0;
      invertersetup();

      terminal.println("accoff");
      terminal.flush();
    }
    if (!lowpoweroff) {



      inverterroutine();



    } else {
      //    terminal.println("lowpow");

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;


    }
  }
}
void nowsend() {




  senddata.battvol = batteryvoltage;
  senddata.invmosstat = invertermos_state;
  senddata.timeexp = timeexpired;
  senddata.pwrsupp = (power1 || power2 || power3);
  senddata.lowpwroff = lowpoweroff;
  senddata.checkvol = checkvol;
  senddata.currprev = (current - fiveminute);
  senddata.usedmin = usedminute;
  senddata.invenable = invenable;
  senddata.lightr = timeauto;


  senddata.hourr = hour();
  senddata.minutee = minute();
  senddata.secondd = second();

  esp_now_send(broadcastAddress, (uint8_t *) &senddata, sizeof(senddata));



}

void subthread1() {


  //  if (batteryvoltage > 13 && checkvol == 0) {
  //    checkvol = 1;
  //  }
  if (batteryvoltage < 13.13 && highh == 0 && hour() < 16) {
    highh = 1;
    peakss++;
    daypeeks++;
    auxdaypeeks++;
  }



  if ((power1 || power2 || power3) && powersupplaymadehigh == 0) {
    powersupplaymadehigh = 1;
    digitalWrite(powersupplay_ac, HIGH);


  }

  if (powersupplaymadehigh == 1 && !(power1 || power2 || power3)) {
    powersupplaymadehigh = 0;

    digitalWrite(powersupplay_ac, LOW);


  }

  if (batteryvoltage < 11.94) {//
    lowpoweroff = 1;

  }


  if (batteryvoltage > 12.5) {
    lowpoweroff = 0;
  }




  //  if (batteryvoltage < 12.8 && settt==0 && ac_innc==1) {
  //    power3=1;

  //timerr.deleteTimer(tid);
  //    tid=timerr.setTimeout(3900000, stopcharge);
  //   settt=1;
  //  }

}



void inverterroutine() {


  if (timeexpired == 0) {
    current = millis();


    if ((current - cprevv) > 14400000 || (current - cprevv) < 0) {

      terminal.println("timee2hr");
      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      timeexpired = 1;


    }




    if (firsttimeinv == 1 && batteryvoltage < 12.2 && invertermos_state == 1) {
      firsttimeinv = 0;
      digitalWrite(inverter_mos, HIGH);
      delay(4500);
      digitalWrite(inverter_mos, LOW);

    }
    //6,7,8,9

    int justhour = hour();
    usedminute = !(justhour >= 17 && justhour <= 21 && ((millis() - fiveminute) < 300000) && therewaspower) && (digitalRead(ussed_min));

    if (usedminute || invenable == 0) {
      delay(200);
      usedminute = !(justhour >= 17 && justhour <= 21 && ((millis() - fiveminute) < 300000) && therewaspower) && (digitalRead(ussed_min));

      if (usedminute || invenable == 0) {
        digitalWrite(inverter_mos, HIGH);
        invertermos_state = 0;
        timeexpired = 1;
        terminal.println("NOONUSEDMINN");
        LeDTime = millis();

      }
    }







  } else {



    if (batteryvoltage < 12.0) {


      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;
      daypeeks = 0;

    }



    if (timeauto == 1) {
      if ((hour() == 19 || hour() == 20) && (day() != 15 || day() != 16) && bootwithoutwifi == 0 && therewaspower == 0) {
        if (batteryvoltage > 12.23 && daypeeks > 0) {
          invondaya = 1;
          digitalWrite(inverter_mos, LOW);
          invertermos_state = 1;

        } else {

          daypeeks = 0;

          digitalWrite(inverter_mos, HIGH);
          invertermos_state = 0;







        }





      } else {
        digitalWrite(inverter_mos, HIGH);
        invertermos_state = 0;

      }



    } else {

      digitalWrite(inverter_mos, HIGH);
      invertermos_state = 0;


    }
  }

}



void invertersetup() {
  digitalWrite(Ac2, HIGH);
  digitalWrite(Ac1, HIGH);
  digitalWrite(mainpower_mos, HIGH);
  firsttimeinv = 1;
  resu = 0;
  fiveminute = millis() - 10;

  int justhour = hour();
  usedminute = !(justhour >= 17 && justhour <= 21 && ((millis() - fiveminute) < 300000) && therewaspower) && (digitalRead(ussed_min));

  if (invenable == 1 && !usedminute) {
    digitalWrite(inverter_mos, LOW);
    invertermos_state = 1;
    timeexpired = 0;
  } else {
    timeexpired = 1;


  }
  //        checkvol=0;

  power1 = 0;
  power2 = 0;
  power3 = 0;
  //    digitalWrite(powersupplay_ac, LOW); // Set digital pin 2 HIGH
  terminal.println("invstart");
  cprevv = millis();
  prevvolt = batteryvoltage;

  terminal.println("inv setup");

}





void chargeroutine() {

}

void chargesetup() {
  settt = 0;
  digitalWrite(Ac2, HIGH);
  terminal.println("ch setup");

  digitalWrite(inverter_mos, HIGH);
  invertermos_state = 0;
}

void pwcn() {

  if (digitalRead(ac_inn)) {
    digitalWrite(inverter_ac, LOW);
    Serial.println("inst1");

  }
  Serial.println("inst2");

}

void stopcharge() {
  settt = 0;
  //    digitalWrite(powersupplay_ac, LOW); // Set digital pin 2 HIGH
  power3 = 0;
}

















void alloff() {

  allon = 0;


}



BLYNK_WRITE(V20) // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1)
  {
    allon = 1;
    timerr.setTimeout(45000, alloff);


    terminal.println(param.asInt());
    terminal.flush();
  } else
  {
  }
}

BLYNK_WRITE(V15) // Executes when the value of virtual pin 0 changes
{
  if (param.asInt() == 1)
  {

    if (!digitalRead(ac_inn)) {
      invertersetup();

      terminal.println(param.asInt());
      terminal.flush();
    }
  } else
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
    timeexpired = 1;


  } else
  {
  }
}





BLYNK_WRITE(V18) // Executes when the value of virtual pin 0 changes
{

  timeauto = param.asInt();
  terminal.println(param.asInt());
  terminal.flush();





}




BLYNK_WRITE(V88) // Executes when the value of virtual pin 0 changes
{

  safemode = param.asInt();
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

  invenable = param.asInt();
  terminal.println(param.asInt());
  terminal.flush();





}




BLYNK_WRITE(V19) // Executes when the value of virtual pin 0 changes
{

  forceonn = param.asInt();
  terminal.println(param.asInt());
  terminal.flush();





}


BLYNK_WRITE(V16) // Executes when the value of virtual pin 0 changes
{



  terminal.println(batteryvoltage);
  terminal.println(analogRead(A0));

  terminal.println(lowpoweroff);
  terminal.println(invertermos_state);
  terminal.println(WiFi.macAddress());


  terminal.flush();

  terminal.println(hour());
  terminal.println(minute());
  terminal.println(auxdaypeeks);



  terminal.println(peakss);
  terminal.println(therewaspower);

  terminal.flush();

}

BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
{

  if (param.asInt() > 1)
  {
    // execute this code if the switch widget is now ON
    //    digitalWrite(powersupplay_ac, HIGH); // Set digital pin 2 HIGH
    power1 = 1;
    terminal.println(param.asInt());
  } else
  {
    // execute this code if the switch widget is now OFF
    //          digitalWrite(powersupplay_ac, LOW); // Set digital pin 2 HIGH
    power1 = 0;

  }
}


BLYNK_CONNECTED() {                  //When device is connected to server...
  rtc.begin();

}


void sendd() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.virtualWrite(V8, batteryvoltage);

    Blynk.virtualWrite(V1, invertermos_state);
    Blynk.virtualWrite(V4, (power1 || power2 || power3));
    Blynk.virtualWrite(V7, lowpoweroff);
    //    Blynk.virtualWrite(V7,lowpoweroff);
    Blynk.virtualWrite(V9, checkvol);
    Blynk.virtualWrite(V14, usedminute);


    int aaasdx = ThingSpeak.writeField(myChannelNumber, 1, batteryvoltage, myWriteAPIKey);
    Blynk.virtualWrite(V75, invonday);

    Blynk.virtualWrite(V10, current);
    Blynk.virtualWrite(V11, fiveminute);
    Blynk.virtualWrite(V13, (current - fiveminute));
    Blynk.virtualWrite(V2, timeexpired);
    Blynk.virtualWrite(V67, daypeeks);

  }
}




// Function to update LEDs based on the voltage
void updateLEDsBasedOnVoltage(float voltage) {
  int numLEDsToLight = 0;

  // Determine the number of LEDs to light up based on the voltage
  if (voltage >= 12.0) {
    numLEDsToLight = (int)((voltage - 12.0) / VOLTAGE_STEP);
    if (numLEDsToLight > NUMPIXELS) {
      numLEDsToLight = NUMPIXELS;
    }
  }

  // Calculate the color based on the voltage
  uint8_t red = 0;
  uint8_t green = 0;
  red = map(constrain(voltage * 1000, 12000, 12600), 12000, 12600, 100, 0);
  green = map(constrain(voltage * 1000, 12000, 12600), 12000, 12600, 0, 100);


  // Light up the appropriate number of LEDs with the calculated color
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i < numLEDsToLight) {
      pixels.setPixelColor(i, pixels.Color(red, green, 0));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn off the LED
    }
  }

  // Update the LEDs to show the changes
  pixels.show();
}

// Function to update a single LED based on the voltage
void updateSingleLEDBasedOnVoltage(float voltage) {

    int whitepix=daypeeks/100;


  // Turn off all LEDs initially
  for (int i = 0; i < NUMPIXELS; i++) {
    if(whitepix>i){
    pixels.setPixelColor(i, pixels.Color(1, 1, 1));

    }else{
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }}
  int ledIndex = 0;
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  // Determine which LED to light up based on the voltage
  if (voltage >= 13.3) {
    ledIndex = (int)((voltage - 13.3) / .15);

    // Calculate the color based on the voltage
    blue = 6;
  } else if (voltage >= 12.0) {
    ledIndex = (int)((voltage - 12.0) / VOLTAGE_STEP);

    red = 2;
    green = 2;

  }

  // Ensure ledIndex does not exceed the number of pixels
  if (ledIndex >= NUMPIXELS) {
    ledIndex = NUMPIXELS ;
  }

  // Light up the specific LED with the calculated color
  pixels.setPixelColor(ledIndex - 1, pixels.Color(red, green, blue));


  // Update the LEDs to show the changes
  pixels.show();



}

// Function to set all LEDs to white
void setAllWhite(int power) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(power, power, power)); // Set LED to white
  }
  pixels.show(); // Update the LEDs to show the changes
}

// Function to turn off all LEDs
void turnAllOff() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn off the LED
  }
  pixels.show(); // Update the LEDs to show the changes
}
