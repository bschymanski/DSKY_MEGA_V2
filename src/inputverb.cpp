#include <Arduino.h>
#include <globals.h>
#include <main.h>
#include <button_read_int.h>
#include <neopixel.h>
#include <nextion.h>
//#include <inputverb.h>
#include <inputnoun.h>


void clearVerbfunction()
{
  verb_valid = false;
  noun_valid = false;
  verb = -1;
  noun = -1;
  verb_ten = -1;
  verb_one = -1;
  noun_ten = -1;
  noun_one = -1;
  actionRuning = actionNone;
  verb_error = false;
  noun_error = false;
  //clipnum = 1;
  printVerbNounProg();
  
}

void input_Verb()
{
  if ((verb_ten >= 0) && (verb_one >= 0) && (verb_valid != true) && (verb_error !=true) && (current_key == keyClear)) //we want to change the last digit, pressed keyclear
  {
    if ((verb_ten >= 0) && (verb_one <= 0) && (verb_valid != true) && (verb_error !=true))
    {
      verb_ten = -1;
      printVerbNounProg();
    }
    else if ((verb_ten >= 0) && (verb_one >= 0) && (verb_valid != true) && (verb_error !=true))
    {
      verb_one = -1;
      printVerbNounProg();
    }
  }
  else if ((verb_ten >= 0) && (verb_one >= 0) && (verb_valid != true) && (verb_error !=true) && (current_key == keyRelease)) // we entered both verb_ten and ver_1, but want to cancel anyway, pressed keyRelease
  {
    // restore the old verb, verb_ten, verb_one
  }
  else if ((verb_ten >= 0) && (verb_one >= 0) && (verb_valid != true) && (verb_error !=true) ) // we might possibly have a valid verb! Lets check it out
  {
    lightVerblamp(blue);
    int verb_temp = (verb_ten*10)+verb_one;
    short idx = 0;
    bool found = false;
    while ((idx < NUM_PROG_TABLE_ENTRIES) && (found == false))
        { // lets have a look at the Programtable for a valid verb
            if (ProgramTable[idx].VerbNumber == verb_temp)
            {
                old2_verb = old1_verb;
                old1_verb = verb;
                verb = verb_temp;
                verb_valid = true;
                found = true;
                if (verb != old1_verb)
                { // a new verb has been entered, but we had a valid verb before, now the old noun is invalid
                    old2_noun = old1_noun;
                    old1_noun = noun;
                    noun = nounNone;
                }
                //mode = modeIdle;
                lightVerblamp(green);
                printVerbNounProg();
                switch(current_key)
                {
                  case keyNoun:
                    //setLamp(yellow, lampProgCond);
                    inputmode = inputNoun;
                    input_Noun();
                    break;
                  case keyEnter:
                    inputmode = inputNoun;
                    blinkverb = true;
                    input_Noun();
                    printVerbNounProg();
                    break;
                }
                //setLamp(blue, lampVerb);
            }
            idx++;
        }
        if (verb_valid == false)
        { // we don't have a valid verb, sorry. Turn on the error lamp and clear verb_ten - noun_one variables
          setLamp(white, lampOprErr);
          verb_error = true;
        }
  }
  else if ((verb_valid != true) && (verb_error !=true)) // we do not have a valid verb yet
  {
    lightVerblamp(yellow);
    switch(current_key)
    {
      case keyVerb:
        clearVerbfunction();
        break;
      case keyNoun: // if we are in verbinput mode, why press the noun button, makes sense only if we already have a valid verb.
        if (verb_valid == true)
        {
            inputmode = inputNoun;
        }
        break;
      case keyRelease:  // we changed our mind and don't want to input a verb, back to idle mode
        if ((verb_ten <= 0) && (verb_one <= 0) && (verb_valid != true) && (verb_error !=true))
        {
          inputmode = inputIdle;
          lightVerblamp(green);
        }
        else if ((verb_valid != true) && (verb_error !=true))
        {
          inputmode = inputIdle;
          verb_ten = -1;
          verb_one = -1;
          printVerbNounProg();
          lightVerblamp(green);
        }
        break;
      case keyClear:
        if ((verb_ten >= 0) && (verb_one <= 0) && (verb_valid != true) && (verb_error !=true))
        {
          verb_ten = -1;
          printVerbNounProg();
        }
        else if ((verb_ten >= 0) && (verb_one >= 0) && (verb_valid != true) && (verb_error !=true))
        {
          verb_one = -1;
          printVerbNounProg();
        }
        break;
      // Now we are entering the numbers for the verb!
      case keyNumber0:  
      case keyNumber1:
      case keyNumber2:
      case keyNumber3:
      case keyNumber4:
      case keyNumber5:
      case keyNumber6:
      case keyNumber7:
      case keyNumber8:
      case keyNumber9:
        if (verb_valid == false)
        { // we don't have a valid verb yet, but we have entered a number, lets assing it to the proper place (first or second Digit)
          if (verb_ten < 0)
          { // First Verb Digit has been entered
            verb_ten = current_key_int;
            printVerbNounProg();
          }
          else if ((verb_ten >= 0) && (verb_one < 0))
          { // Second verb Digit has been entered
            verb_one = current_key_int;
            printVerbNounProg();
          }
        }
        break;
    }
  }
  else if ((verb_valid != true) && (verb_error ==true)) // we do not have a valid verb yet, a wrong verb has been entered
  {
    lightVerblamp(red);
    switch(current_key)
    {
      case keyClear:
        verb_ten = -1;
        verb_one = -1;
        noun_ten = -1;
        noun_one = -1;
        printVerbNounProg();
        setLamp(off, lampOprErr);
        verb_error = false;
        lightVerblamp(yellow);  // we cleared the wrong verb_ten and verb_one, but are still in verbinputmode
        break;
    }
    
  }
  else if ((verb_valid == true) && (noun_valid != true)) // we have a valid verb and now lets see what we comes next: Lamptest, Program Input, Verb input?
  {
    lightVerblamp(green);
    switch(current_key)
    {
      case keyClear:
        verb_ten = -1;
        verb_one = -1;
        noun_ten = -1;
        noun_one = -1;
        printVerbNounProg();
        verb_error = false;
        verb_valid = false;
        verb = 0;
        noun = 0;
        break;
    }
  }
  else if ((verb_valid == true) && (noun_valid == true)) // we have a valid verb and a valid noun, but we want to enter a new verb, so the old noun is invalid now
  {
    lightVerblamp(yellow);
  }
}
