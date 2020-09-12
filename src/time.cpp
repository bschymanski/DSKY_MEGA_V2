#include <Arduino.h>
#include <main.h>
#include <button_read_int.h>
#include <neopixel.h>
#include <nextion.h>
#include <inputverb.h>
#include <inputnoun.h>
#include <globals.h>
#include <time.h>
#include <math.h>

/*
#include <Wire.h>
#include <RTClib.h>

DS3231 rtc;
*/

//https://github.com/NorthernWidget/DS3231
#include <DS3231.h>
#include <Wire.h>
#include <TimeLib.h>
#include <Timezone.h>

DS3231 clock;
RTClib myRTC;
bool century = false;
bool h12Flag;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;

// Timezone stuff
//https://github.com/JChristensen/Timezone?utm_source=platformio&utm_medium=piohome
/*
Define a TimeChangeRule as follows:
TimeChangeRule myRule = {abbrev, week, dow, month, hour, offset};
Where:
abbrev is a character string abbreviation for the time zone; it must be no longer than five characters.
week is the week of the month that the rule starts.
dow is the day of the week that the rule starts.
hour is the hour in local time that the rule starts (0-23).
offset is the UTC offset in minutes for the time zone being defined.
For convenience, the following symbolic names can be used:
week: First, Second, Third, Fourth, Last
dow: Sun, Mon, Tue, Wed, Thu, Fri, Sat
month: Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
*/
TimeChangeRule myDST = {"EDT", Last, Sun, Mar, 2, +120};    //Daylight time = UTC + 2 hours
TimeChangeRule mySTD = {"EST", Last, Sun, Oct, 2, +60};     //Standard time = UTC + 1 hours

Timezone myTZ(myDST, mySTD);


TimeChangeRule* tcr;               //pointer to the time change rule, use to get TZ abbrev
time_t now_time_t, utc_time_t, local_time_t;


void display_time()
{
  /*
  DateTime now = rtc.now();
  Serial.print(" since midnight 1970/1/1 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");
  Serial.print(now.year());
  Serial.print(".");
  Serial.print(now.month());
  Serial.print(".");
  Serial.print(now.day());
  Serial.print(" ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(" ");
  Serial.print(now.second());
  Serial.print(".");
  */
 	// send what's going on to the serial monitor.
	
	// Start with the year
	
  /*
  Serial.print("2");
	if (century) {			// Won't need this for 89 years.
		Serial.print("1");
	} else {
		Serial.print("0");
	}
	Serial.print(clock.getYear(), DEC);
	Serial.print(' ');
	
	// then the month
	Serial.print(clock.getMonth(century), DEC);
	Serial.print(" ");
  
	// then the date
	Serial.print(clock.getDate(), DEC);
	Serial.print(" ");
  
	// and the day of the week
	Serial.print(clock.getDoW(), DEC);
	Serial.print(" ");
  
	// Finally the hour, minute, and second
	Serial.print(clock.getHour(h12Flag, pmFlag), DEC);
	Serial.print(" ");
	Serial.print(clock.getMinute(), DEC);
	Serial.print(" ");
	Serial.print(clock.getSecond(), DEC);

  
	// Add AM/PM indicator
	if (h12Flag) {
		if (pmFlag) {
			Serial.print(" PM ");
		} else {
			Serial.print(" AM ");
		}
	} else {
		Serial.print(" 24h ");
	}
 
	// Display the temperature
	Serial.print("T=");
	Serial.print(clock.getTemperature(), 2);
  
	// Tell whether the time is (likely to be) valid
	if (clock.oscillatorCheck()) {
		Serial.print(" O+");
	} else {
		Serial.print(" O-");
	}
 
	// Indicate whether an alarm went off
	if (clock.checkIfAlarm(1)) {
		Serial.print(" A1!");
	}
 
	if (clock.checkIfAlarm(2)) {
		Serial.print(" A2!");
	}
 
	// New line on display
	Serial.println();
	
	// Display Alarm 1 information
	Serial.print("Alarm 1: ");
	clock.getA1Time(alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits, alarmDy, alarmH12Flag, alarmPmFlag);
	Serial.print(alarmDay, DEC);
	if (alarmDy) {
		Serial.print(" DoW");
	} else {
		Serial.print(" Date");
	}
	Serial.print(' ');
	Serial.print(alarmHour, DEC);
	Serial.print(' ');
	Serial.print(alarmMinute, DEC);
	Serial.print(' ');
	Serial.print(alarmSecond, DEC);
	Serial.print(' ');
	if (alarmH12Flag) {
		if (alarmPmFlag) {
			Serial.print("pm ");
		} else {
			Serial.print("am ");
		}
	}
	if (clock.checkAlarmEnabled(1)) {
		Serial.print("enabled");
	}
	Serial.println();
 
	// Display Alarm 2 information
	Serial.print("Alarm 2: ");
	clock.getA2Time(alarmDay, alarmHour, alarmMinute, alarmBits, alarmDy, alarmH12Flag, alarmPmFlag);
	Serial.print(alarmDay, DEC);
	if (alarmDy) {
		Serial.print(" DoW");
	} else {
		Serial.print(" Date");
	}
	Serial.print(" ");
	Serial.print(alarmHour, DEC);
	Serial.print(" ");
	Serial.print(alarmMinute, DEC);
	Serial.print(" ");
	if (alarmH12Flag) {
		if (alarmPmFlag) {
			Serial.print("pm");
		} else {
			Serial.print("am");
		}
	}
	if (clock.checkAlarmEnabled(2)) {
		Serial.print("enabled");
	}
 
	// display alarm bits
  Serial.println();
	Serial.print("Alarm bits: ");
	Serial.println(alarmBits, BIN);

	Serial.println();

  Serial.println("myRTC.now");
  DateTime now = myRTC.now();
  DateTime now_time_t = myRTC.now();
  time_t utc_time_t = now_time_t.unixtime();
  time_t local_time_t = myTZ.toLocal(utc_time_t, &tcr);
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
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
    
    Serial.println("Localtime");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(hour(local_time_t));
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    */

  DateTime now = myRTC.now();
  DateTime now_time_t = myRTC.now();
  time_t utc_time_t = now_time_t.unixtime();
  time_t local_time_t = myTZ.toLocal(utc_time_t, &tcr);
  int tempmonth = now.month();
  int tempday = now.day();
  int temphour = hour(local_time_t);
  int tempmin = now.minute();
  int tempsec = now.second();
  int temptemp = round(clock.getTemperature());

  // Temperature
  if (temptemp >= 28)
  {
    setLamp(red, lampTemp);
  }
  else if (temptemp >= 26)
  {
    setLamp(yellow, lampTemp);
  }
  else if (temptemp <= 25)
  {
    setLamp(off, lampTemp);
  }
  if (temptemp <= 20)
  {
    setLamp(blue, lampTemp);
  }

  if (tempday >= 10)
  {
    int tempdone = tempday % 10;
    int tempdten = (tempday - tempdone) / 10;
    print_REG_NUM(1, 5, tempdten);
    print_REG_NUM(1, 4, tempdone);
  }
  else if (tempday < 10)
  {
    print_REG_NUM(1, 5, 0);
    print_REG_NUM(1, 4, tempday);
  }
  // Space between day and month
  print_REG_OFF(1, 3);
  if (tempmonth >= 10)
  {
  int tempmone = tempmonth % 10;
  int tempmten = (tempmonth - tempmone) / 10;
  print_REG_NUM(1, 2, tempmten);
  print_REG_NUM(1, 1, tempmone);
  }
  else if (tempmonth < 10)
  {
    print_REG_NUM(1, 2, 0);
    print_REG_NUM(1, 1, tempmonth);
  }



  // Hour and Minute on register 2
  if (temphour >= 10)
  {
  int temphpone = temphour % 10;
  int temphten = (temphour - temphpone) / 10;
  print_REG_NUM(2, 5, temphten);
  print_REG_NUM(2, 4, temphpone);
  }
  else if (temphour < 10)
  {
    print_REG_NUM(2, 5, 0);
    print_REG_NUM(2, 4, temphour);
  }
  // Space between hour and minute
  print_REG_OFF(2, 3);
  if (tempmin >= 10)
  {
  int tempmpone = tempmin % 10;
  int tempmten = (tempmin - tempmpone) / 10;
  print_REG_NUM(2, 2, tempmten);
  print_REG_NUM(2, 1, tempmpone);
  }
  else if (tempmin < 10)
  {
    print_REG_NUM(2, 2, 0);
    print_REG_NUM(2, 1, tempmin);
  }


  if (tempsec >= 10)
  {
  int tempsone = tempsec % 10;
  int tempsten = (tempsec - tempsone) / 10;
  print_REG_NUM(3, 2, tempsten);
  print_REG_NUM(3, 1, tempsone);
  }
  else if (tempsec < 10)
  {
    print_REG_NUM(3, 2, 0);
    print_REG_NUM(3, 1, tempsec);
  }
  // Space between day and month
  print_REG_OFF(3, 3);
  //temperature
  if (temptemp >= 10)
  {
  int temptone = temptemp % 10;
  int temptten = (temptemp - temptone) / 10;
  print_REG_NUM(3, 5, temptten);
  print_REG_NUM(3, 4, temptone);
  }
  else if (temptemp < 10)
  {
    print_REG_NUM(3, 5, 0);
    print_REG_NUM(3, 4, temptemp);
  }

}

void time_setup()
{
  //rtc.begin();
  
}