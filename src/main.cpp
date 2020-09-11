#include <Arduino.h>
#include <Wire.h>
#include <main.h>
#include <arduino-timer.h>
#include <globals.h>
#include <neopixel.h>
#include <nextion.h>
#include <button_read_int.h>
#include <inputverb.h>
#include <inputnoun.h>
#include <time.h>



// for the toggle variables
auto timer = timer_create_default();

void setup()
{
  // prepare the Pins for the keyboard and attach the interrupt
  configureCommon(); // Setup pins for interrupt
  attachInterrupt(digitalPinToInterrupt(commonPin), pressInterrupt, FALLING);

  Serial.begin(9600);
  Wire.begin();
  void time_setup();
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
  printVerbNounProg();
  printRegister(1, register_num_1, false, false, false, true);
  printRegister(2, register_num_2, false, false, false, true);
  printRegister(3, register_num_3, false, false, false, true);
  //display_time();

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
  
  blinkverb = true;
  blinknoun = true;
  blinkprog = true;
  verb_ten =3;
  verb_one =7;
  noun_ten = 0;
  noun_one = 2;
  prog_ten = 6;
  prog_one = 3;
  
  printVerbNounProg();
  long number1 = 312;
  long number2 = 9512;
  long number3 = 80302;
  //extern void printRegister(int dregister, long number, bool leadzero, bool blink, bool alarm, bool signoff);
  printRegister(1, number1, false, true, false, false);
  printRegister(2, number2, false, false, false, false);
  printRegister(3, number3, false, false, false, false);
  */
  // is a Program (major mode) running ?
  switch (progRunning)
  {
    case progNone:
      // No programm running yet
      setLamp(yellow, lampProgCond);
      // is an action running?
      switch (actionRuning)
      {
        case actionNone:
          //no action is running
          setLamp(white, lampSTBY);
          display_time();
          break;
        case actionLampTest:
          testLamp();
          actionRuning = actionNone;
          clearVerbfunction();
          break;
      }
      // END is an action running
      break;
    default:
      break;
  }
  // END is a Program (major mode) running ?

  // check the key, if one has been pressed:
  if (keypressed == true) // a key hase been pressed
  { 
    switch(current_key) // which key has been pressed?
    {
      case keyVerb:
        inputmode = inputVerb;
        break;
      default:
        break;
    }
    // check the input mode (Verb / Noun)
    switch (inputmode)
    {
      case inputIdle:
        break;
      case inputVerb:
        //lightVerblamp(yellow);
        input_Verb();
        break;
      case inputNoun:
        input_Noun();
        break;
    }
  // END check the input mode (Verb / Noun)
  old_key = current_key;
  keypressed = false;
  }
  printVerbNounProg(); 
  // END a key hase been pressed

  

  
  
}