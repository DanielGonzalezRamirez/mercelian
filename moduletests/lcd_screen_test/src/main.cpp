#include <Arduino.h>
#include <Wire.h> // Library for I2C communication
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"
#include <LiquidCrystal_I2C.h> // Library for LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);
 
RTC_DS3231 RTC;     // Setup an instance of DS1307 naming it RTC

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Set serial port speed
  lcd.begin(4, 5);
  lcd.backlight();
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC
  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
  Serial.print("Time and date set");
  lcd.setCursor(0, 0);
  lcd.print("Real Time Clock");
  delay(3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = RTC.now();
 
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
 
  
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  
  lcd.setCursor(6, 0);
  lcd.print(now.year(), DEC);
  lcd.print(":");
  lcd.print(now.month(), DEC);
  lcd.print(":");
  lcd.print(now.day(), DEC);
 
  lcd.setCursor(6, 1);
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC); 
  delay(1000);
  lcd.clear();
}