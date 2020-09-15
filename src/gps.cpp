#include <Arduino.h>
#include <main.h>
#include <button_read_int.h>
#include <neopixel.h>
#include <nextion.h>
#include <inputverb.h>
#include <inputnoun.h>
#include <globals.h>
#include <TimeLib.h>
#include <time.h>
#include <math.h>
#include <TinyGPS++.h>
#include <gps.h>
#include <SoftwareSerial.h>


// The TinyGPS++ object
TinyGPSPlus gps;
//SoftwareSerial ss(14, 15);

byte gpsData;

void gps_displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    setLamp(green, lampPosition);
  }
  else
  {
    Serial.print(F("INVALID"));
    setLamp(red, lampPosition);
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void gps_setup()
{
  
  //ss.begin(9600);
  Serial3.begin(9600);
}

void gps_test()
{
  //gpsData = Serial3.read();
  //Serial.write(gpsData);
  // This sketch displays information every time a new sentence is correctly encoded.
  if (toggle1000 == false && gpsprinttoogle == false)
  {
    while (Serial3.available() > 0)
    {
      if (gps.encode(Serial3.read()))
      {
        gps_displayInfo();
      }
    }
    gpsprinttoogle = true;
  }
  else if (toggle1000 == true && gpsprinttoogle == true)
  {
    gpsprinttoogle = false;
  }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  
}

