
#include <Adafruit_Fingerprint.h>

#define SIM800 Serial3
#define mySerial Serial2

#define VOLTAGE_READ PB0
#define RELAY1 PA7 //ACC
#define RELAY2 PA6 //ON
#define RELAY3 PA5 //INGITION
#define RELAY4 PA4 //Alligator
#define IGNITION_12V PB12
#define DTR PB14
#define INTERRUPT1 PB15

#include "additional_functions.h"
#include "EEPROM.h"
#include "voltage_read.h"
#include "thermistor.h"
#include "tachometer.h"
#include "ignition.h"
#include "sim800l.h"
#include "Fingerprint.h"
#include "call.h"
#include "sms.h"
#include "FancyDelay.h"

void setup() { 
  // put your setup code here, to run once:
//----------------- RELAYS-------------------------------------------------------------
pinMode(DTR,OUTPUT);
pinMode(RELAY1,OUTPUT);
pinMode(RELAY2,OUTPUT);
pinMode(RELAY3,OUTPUT);
pinMode(RELAY4,OUTPUT);
digitalWrite(DTR, LOW); // пробуждаем GSM модуль
digitalWrite(RELAY1, HIGH);
digitalWrite(RELAY2, HIGH);
digitalWrite(RELAY3, HIGH);
digitalWrite(RELAY4, HIGH);
pinMode(IGNITION_12V, INPUT);
//----------------- SIM800----------------------------------------------------------------
Serial.begin(57600);
SIM800.begin(57600);
finger.begin(57600);
delay(1000);
Serial.println("START");
sim800_init();
//-----------------FINGERPRINT------------------------------------------------------------
//FingerPrint_init();
//----------------------------TACHOMETER--------------------------------------------------
pinMode(INTERRUPT1, INPUT_PULLDOWN);
attachInterrupt(INTERRUPT1,incrementRpmCount, FALLING);
//----------------------------------------------------------------------------------------
EEPROM_list();
}

void loop() 
{
//getFingerprintID();  
//----------------------------------------------------------------------        
if(accum_check==true && !engine_check() && voltage_read()<voltage)
  {
  engine_on();
  }
if(auto_ignition==1) // машина запущена
  {  
  if(warmup_long<millis()) auto_ignition=0; 
  Serial.print("averagedRpm=");  
  Serial.println(averagedRpm); 
  if(Thermister()>=tempeture_cabin)
    {      
    tempeture_cabin=100;
    MakeCall(Temp_Phone,3); 
    delay(1000);
    }
  if(averagedRpm>2000)  
    {
    auto_ignition=0;
    engine_off();
    Serial.println("auto_ignition=0");   
    }
  }
//------------------------------------------------------------   
delay(100);
String inputString; // строка которая формируется из байтов
while(SIM800.available()>0) inputString=SIM800.readString();
while (Serial.available()>0) {inputString=Serial.readString();sendATCommand(inputString,true);}
inputString.toUpperCase();  // увеличиваем всё до больших букв  
inputString.trim(); 
if(inputString!="") Serial.println(inputString);     
sms(inputString);
calls(inputString);  
inputString="";
}
