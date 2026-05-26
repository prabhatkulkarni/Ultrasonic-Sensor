#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<DHT.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int red = 5;
int green = 4;
int Echo = 7;
int Trig = 6;
float distance;
long duration;
float temperature;
float speed_sound;
void setup() {
    pinMode(red,OUTPUT);
    pinMode (green,OUTPUT);
    pinMode(Echo,INPUT);
    pinMode(Trig,OUTPUT);
    lcd.init();
    lcd.backlight();
    dht.begin();
    Serial.begin(9600);
}

void loop() {
  //measuring temperature and calculating speed of sound
    temperature = dht.readTemperature();
    speed_sound = 331 +(0.6*temperature);
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
  // Measure echo duration
    duration = pulseIn(Echo, HIGH);
  // Convert duration to distance (in cm)
    distance = (duration *speed_sound) / 20000;
    distance = distance + 0.5;
  // Print distance always
    Serial.print(distance);
    Serial.print("\n");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dist:");
    lcd.print(distance);
    lcd.print("cm ");

    lcd.setCursor(0,1);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C ");

    if(distance <= 60){

        digitalWrite(red,HIGH);
        digitalWrite(green,LOW);
        delay(100);}

    else{
        digitalWrite(red,LOW);
        digitalWrite(green,HIGH);
        delay(100);}
    delay(1000);
}

