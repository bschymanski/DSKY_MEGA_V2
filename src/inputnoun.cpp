#include <Arduino.h>
#include <main.h>
#include <button_read_int.h>
#include <neopixel.h>
#include <nextion.h>
#include <inputverb.h>
#include <inputnoun.h>
#include <globals.h>

void clearNounfunction()
{

}


void input_Noun()
{
  lightNounlamp(yellow);
  printVerbNounProg();
}