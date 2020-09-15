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
  printVerbNounProg();
  if ((noun_ten < 0) && (noun_one < 0) && (noun_valid != true) && (noun_error !=true) && (current_key == keyRelease)) // we entered both noun_ten and noun_one, but want to cancel anyway, pressed keyRelease
  {
    clearNounfunction();
    clearVerbfunction();
    lightNounlamp(green);
    lightVerblamp(green);
    actionRuning = actionNone;
  } 
  else if ((noun_ten >= 0) && (noun_one >= 0) && (noun_valid != true) && (noun_error !=true) && (current_key == keyRelease)) // we entered both noun_ten and noun_one, but want to cancel anyway, pressed keyRelease
  {
    clearNounfunction();
    clearVerbfunction();
    lightNounlamp(green);
    lightVerblamp(green);
    actionRuning = actionNone;
    lightNounlamp(orange);
  }
  else if ((noun_ten >= 0) && (noun_one >= 0) && (noun_valid != true) && (noun_error !=true) ) // we might possibly have a valid noun! Lets check it out
  {
    lightNounlamp(blue);
    int noun_temp = (noun_ten*10)+noun_one;
    short idx = 0;
    bool found = false;
    while ((idx < NUM_PROG_TABLE_ENTRIES) && (found == false))
        { // lets have a look at the Programtable for a valid verb
          if (ProgramTable[idx].NounNumber == noun_temp)
          {
              old2_noun = old1_noun;
              old1_noun = noun;
              noun = noun_temp;
              noun_valid = true;
              found = true;
              //prog = ProgramTable[idx].ProgramNumber;
              setLamp(red, lampProgCond);
              short idx2 = 0;
              bool found2 = false;
              while ((idx2 < NUM_PROG_TABLE_ENTRIES) && (found2 == false))
              {
                //setLamp(orange, lampProgCond);
                //Serial.print("verb : ");Serial.println(verb);
                //Serial.print("idx : ");Serial.println(idx2);
                if (ProgramTable[idx2].VerbNumber == verb)
                {
                  setLamp(white, lampProgCond);
                  if (ProgramTable[idx2].NounNumber == noun)
                  {
                    found2 = true;
                    prog = ProgramTable[idx2].ProgramNumber;
                    actionRuning = ProgramTable[idx2].action;
                    if (prog != progNotUsed)
                    {
                      setLamp(blue, lampProgCond);
                      prog_valid = true;
                      progRunning = prog;
                      prog_found = true;
                    }
                    else if (actionRuning != actionNone)
                    {
                      setLamp(red, lampProgCond);
                      action_valid = true;
                      action_found = true;
                    }
                    //clearVerbfunction();
                    //Serial.print("verb : ");Serial.print(verb);
                    //Serial.print(" Verbnumber : ");Serial.println(ProgramTable[idx2].VerbNumber);
                    //Serial.print("noun : ");Serial.print(noun);
                    //Serial.print(" Nounnumber : ");Serial.println(ProgramTable[idx2].NounNumber);
                    //Serial.println(ProgramTable[idx].action);
                    //Serial.print(" ProgramNumber : ");Serial.println(ProgramTable[idx2].ProgramNumber);
                  }
                }
              idx2++;
              }
              
              if (noun != old1_noun)
              { // a new noun has been entered, but we had a valid noun before, now the old noun is invalid
              }
              //mode = modeIdle;
              lightNounlamp(green);
              printVerbNounProg();
              switch(current_key)
              {
                case keyEnter:
                  //setLamp(yellow, lampProgCond);
                  //actionRuning = actionNone;
                  //setLamp(green, lampProgCond);
                  if (prog != progNotUsed)
                  {
                    prog_valid = true;
                    setLamp(off, lampProgCond);
                    printVerbNounProg();
                    inputmode = inputIdle;
                    //clearVerbfunction();
                  }
                  else if (actionRuning != actionNone)
                  {
                    setLamp(white, lampProgCond);
                    action_valid = true;
                    inputmode = inputIdle;
                    printVerbNounProg();
                    //action_found = true;
                    //clearVerbfunction();
                  }
                  break;
              }
              //setLamp(blue, lampVerb);
          }
          idx++;
        }
        //if (   ((noun_valid == false) && (prog_found != true))  ||  ((noun_valid == false) && (action_found != true))  )
        if (noun_valid == false)
        { // we don't have a valid verb, sorry. Turn on the error lamp and clear verb_ten - noun_one variables
          if (prog_found != true)
          {
            prog_found = false;
            setLamp(white, lampOprErr);
            noun_error = true;
            action_found = false;
          }
          else if (action_found != true)
          {
            prog_found = false;
            setLamp(white, lampOprErr);
            noun_error = true;
            action_found = false;
          }
        }
        if (prog_valid == true)
        {
          clearVerbfunction();
        }
  }
  else if ((noun_valid != true) && (noun_error !=true)) // we don't have a valid noun yet
  {
    lightNounlamp(yellow);
    switch(current_key)
    {
      case keyVerb:
        clearNounfunction();
        break;
      case keyNoun: // if we are in Noun input mode, why press the noun button?
        break;
      case keyRelease:  // we changed our mind and don't want to input a noun, back to idle mode
        if ((noun_ten <= 0) && (noun_one <= 0) && (noun_valid != true) && (noun_error !=true))
        {
          actionRuning = actionNone;
          clearNounfunction();
          lightNounlamp(green);
        }
        else if ((noun_valid != true) && (noun_error !=true))
        {
          actionRuning = actionNone;
          clearNounfunction();
          printVerbNounProg();
          lightNounlamp(green);
        }
        break;
      case keyClear:
        if ((noun_ten >= 0) && (noun_one <= 0) && (noun_valid != true) && (noun_error !=true))
        {
          noun_ten = -1;
          printVerbNounProg();
        }
        else if ((noun_ten >= 0) && (noun_one >= 0) && (noun_valid != true) && (noun_error !=true))
        {
          noun_one = -1;
          printVerbNounProg();
        }
        break;
      // Now we are entering the numbers for the noun!
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
        if (noun_valid == false)
        { // we don't have a valid noun yet, but we have entered a number, lets assess it to the proper place (first or second Digit)
          //setLamp(yellow, lampGimbalLock);
          if (noun_ten < 0)
          { // First Noun Digit has been entered
            noun_ten = current_key_int;
            printVerbNounProg();
            //setLamp(yellow, lampTemp);
          }
          else if ((noun_ten >= 0) && (noun_one < 0))
          { // Second Noun Digit has been entered
            noun_one = current_key_int;
            //setLamp(green, lampTemp);
            printVerbNounProg();
          }
        }
        //setLamp(red, lampGimbalLock);
        break;
    }

  }
  else if ((noun_valid != true) && (noun_error ==true)) // we do not have a valid noun yet, a wrong noun has been entered
  {
    lightNounlamp(red);
    switch(current_key)
    {
      case keyClear:
        noun_ten = -1;
        noun_one = -1;
        noun = nounNone;
        printVerbNounProg();
        setLamp(off, lampOprErr);
        noun_error = false;
        lightNounlamp(yellow);  // we cleared the wrong noun_ten and noun_one, but are still in verbinputmode
        break;
    }
  }
  else if ((noun_valid == true) && (noun_error !=true)) // we have a valid noun 
  {
    if (prog != progNotUsed)
    {
      prog_valid = true;
      inputmode = inputIdle;
      printVerbNounProg();
      actionRuning = actionNone;
      setLamp(blue, lampProgCond);
    }
    else if (actionRuning != actionNone)
    {
      setLamp(red, lampProgCond);
      action_valid = true;
      inputmode = inputIdle;
      printVerbNounProg();
      setLamp(off, lampProgCond);
      //action_found = true;
      //clearVerbfunction();
    }
  }
}