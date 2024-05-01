#include "RTClib.h"
#include <ezButton.h>
#include <Adafruit_NeoPixel.h>
/*
 * Arduino: 
 * SCL = A5
 * SDA = A4
 */
#define LED_PIN    5
#define NUM_LEDS   7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

RTC_DS3231 rtc;
ezButton boton1(2),boton2(3),boton3(4),boton4(6);
int relay1=10,relay2=9,relay3=7,relay4=8;
//int waterlevel1 = 12, waterlevel2=11;

boolean estado1=false,estado2=false,estado3=false,estado4=false;
int temperatura1 = A3, temperatura2=A2, Humedad1=A7,Humedad2=A6;

//boolean SensorAgua=false;
boolean alarmaAct=false;
int alarmNum=4;
int alarmaOn[ 4 ][ 2 ] = { 
  { 8, 0 }, 
  { 12, 0 },
  { 16, 0 },
  { 20, 0 },
  };

int alarmaOff[ 4 ][ 2 ] = { 
  { 8, 30 }, 
  { 12, 30 },
  { 16, 30 },
  { 20, 30 },
  };

  
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)


void setup() {
  // put your setup code here, to run once:

  strip.begin();
  strip.show(); // Inicia todos los LEDs apagados
  //Inicializando Relays
 pinMode(relay1,OUTPUT);
 digitalWrite(relay1,LOW);  
 pinMode(relay2,OUTPUT);
 digitalWrite(relay2,LOW);  
 pinMode(relay3,OUTPUT);
 digitalWrite(relay3,LOW);  
 pinMode(relay4,OUTPUT);
 digitalWrite(relay4,LOW);
 
 //Inicializando RTC
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
    }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  //Inicializando Sensores
//  pinMode(waterlevel1,INPUT);
//  pinMode(waterlevel2,INPUT);

  

}

void loop() {
  boton1.loop();
  boton2.loop();
  boton3.loop();
  boton4.loop();
  

    unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    

     DateTime now = rtc.now();
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    int hora= now.hour();
    int minutos=now.minute();
    horaAlarma(now.hour(), now.minute());
    }
   

    if(boton1.isPressed()) {
      if(estado1==LOW){
        EncenderRelay(1);
      } else {
        ApagarRelay(1);
      }
    }
    if(boton2.isPressed()) {
      if(estado2==LOW){
        EncenderRelay(2);
      } else {
        ApagarRelay(2);
      }
    }
    if(boton3.isPressed()) {
      if(estado3==LOW){
        EncenderRelay(3);
      } else {
        ApagarRelay(3);
      }
    }
    if(boton4.isPressed()) {
      if(estado4==LOW){
        EncenderRelay(4);
      } else {
        ApagarRelay(4);
      }
    }
    
    
delay(100);
}

/*
boolean revisaNivelAgua(){
  int nivel1 = digitalRead(waterlevel1);
  int nivel2 = digitalRead(waterlevel2);
  
  if(nivel1 && nivel2){
    if(SensorAgua){
        strip.setPixelColor(0, strip.Color(255, 0, 0)); // LED 1
        strip.setPixelColor(2, strip.Color(255, 0, 0)); // LED 3
        strip.setPixelColor(4, strip.Color(255, 0, 0)); // LED 5
        strip.setPixelColor(6, strip.Color(255, 0, 0)); // LED 7
        strip.show();
        SensorAgua=false;
    }
    return true;
  } else {
    ApagarRelay(0);
    SensorAgua=true;
    if(!nivel1){
      strip.setPixelColor(0, strip.Color(1, 75, 160)); // LED 1
      strip.setPixelColor(2, strip.Color(1, 75, 160)); // LED 3
    }
    if(!nivel2){
      strip.setPixelColor(4, strip.Color(120, 40, 140)); // LED 5
      strip.setPixelColor(6, strip.Color(120, 40, 140)); // LED 7
    }
    strip.show();
    return false;
  }  
}
*/


boolean horaAlarma(int Hora, int Minuto){
/*  if(!revisaNivelAgua()){
    return;
  }
*/
  if(!alarmaAct){
    for (int i = 0; i < alarmNum; i++) {
      if(Hora == alarmaOn[i][0]){
        if(Minuto == alarmaOn[i][1]){
          EncenderRelay(0);
        }
      }
    }
  } else {
     for (int i = 0; i < alarmNum; i++) {
      if(Hora == alarmaOff[i][0]){
        if(Minuto == alarmaOff[i][1]){
          ApagarRelay(0);
        }
      }
    }
  }
}


void EncenderRelay(int n) {
/*  if(!revisaNivelAgua()){
    return;
  }
  */
  switch (n) {
    case 0:
            strip.setPixelColor(0, strip.Color(255, 0, 0)); // LED 1
            strip.setPixelColor(2, strip.Color(255, 0, 0)); // LED 3
            strip.setPixelColor(4, strip.Color(255, 0, 0)); // LED 5
            strip.setPixelColor(6, strip.Color(255, 0, 0)); // LED 7

            digitalWrite(relay1,HIGH);
            digitalWrite(relay2,HIGH);
            digitalWrite(relay3,HIGH);
            digitalWrite(relay4,HIGH);
            alarmaAct=true;
            estado1=HIGH;
            estado2=HIGH;
            estado3=HIGH;
            estado4=HIGH;
            break;
    case 1:
            strip.setPixelColor(0, strip.Color(255, 0, 0)); // LED 1
            digitalWrite(relay1,HIGH);
            estado1=HIGH;
            break;
    case 2:
            strip.setPixelColor(2 , strip.Color(255, 0, 0)); // LED 3
            digitalWrite(relay2,HIGH);
            estado2=HIGH;
            break;
    case 3:
            strip.setPixelColor(4, strip.Color(255, 0, 0)); // LED 5
            digitalWrite(relay3,HIGH);
            estado3=HIGH;
            break;
    case 4:
            strip.setPixelColor(6, strip.Color(255, 0, 0)); // LED 7
            digitalWrite(relay4,HIGH);
            estado4=HIGH;
            break;
  }
    strip.show();
    
}


void ApagarRelay(int n) {
  switch (n) {
    case 0:
            strip.setPixelColor(0, strip.Color(0, 0, 0)); // LED 1
            strip.setPixelColor(2, strip.Color(0, 0, 0)); // LED 3
            strip.setPixelColor(4, strip.Color(0, 0, 0)); // LED 5
            strip.setPixelColor(6, strip.Color(0, 0, 0)); // LED 7

            digitalWrite(relay1,LOW);
            digitalWrite(relay2,LOW);
            digitalWrite(relay3,LOW);
            digitalWrite(relay4,LOW);
            alarmaAct=false;
            estado1=LOW;
            estado2=LOW;
            estado3=LOW;
            estado4=LOW;
            break;
    case 1:
            strip.setPixelColor(0, strip.Color(0, 0, 0)); // LED 1
            digitalWrite(relay1,LOW);
            estado1=LOW;
            break;
    case 2:
            strip.setPixelColor(2 , strip.Color(0, 0, 0)); // LED 3
            digitalWrite(relay2,LOW);
            estado2=LOW;
            break;
    case 3:
            strip.setPixelColor(4, strip.Color(0, 0, 0)); // LED 5
            digitalWrite(relay3,LOW);
            estado3=LOW;
            break;
    case 4:
            strip.setPixelColor(6, strip.Color(0, 0, 0)); // LED 7
            digitalWrite(relay4,LOW);
            estado4=LOW;
            break;
  }
    strip.show();
    
}
