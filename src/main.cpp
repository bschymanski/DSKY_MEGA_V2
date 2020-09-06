#include <Arduino.h>
#include <main.h>
#include <arduino-timer.h>
#include <globals.h>
#include <neopixel.h>
#include <nextion.h>

// for the toggle variables
auto timer = timer_create_default();

void setup()
{
  Serial.begin(9600);
  timer.every(1000, toggle_timer_1000);
  timer.every(500, toggle_timer_500);
  timer.every(250, toggle_timer_250);
  NeoPixelSetup();
  //testLamp();
  // nextion Display Init
  Serial1.begin(9600);
  Serial1.print("baud=115200");
  Serial1.write(0xff);  //Send this three lines after each command sent to the nextion display.
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.end();
  Serial1.begin(115200);
  ELtestlamp();
}

void loop()
{
  // each loop, look if the toggle_timer* need to be updated
  timer.tick();
  /*
  now we have 3 gloal Toggles:
  toggle1000
  toggle500
  toggle250
  */
  
  /*
  blinkverb = true;
  blinknoun = true;
  blinkprog = true;
  verb_ten =3;
  verb_one =7;
  noun_ten = 0;
  noun_one = 2;
  prog_ten = 6;
  prog_one = 3;
  */
  printVerbNounProg();
  long number1 = -312;
  long number2 = -9512;
  long number3 = -810302;
  //extern void printRegister(int dregister, long number, bool leadzero, bool blink, bool alarm, bool signoff);
  printRegister(1, number1, false, false, false, true);
  printRegister(2, number2, false, false, false, true);
  printRegister(3, number3, false, false, false, true);
}