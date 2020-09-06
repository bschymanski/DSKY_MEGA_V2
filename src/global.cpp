#include <Arduino.h>
#include <main.h>
#include <globals.h>
#include <arduino-timer.h>


bool toggle1000 = false;
bool toggle500 = false;
bool toggle250 = false;
bool global_state_1000 = false;
bool global_state_500 = false;
bool global_state_250 = false;

int verb = verbNone;
int verb_ten = -1;
int verb_one = -1;
bool blinkverb = false;

int noun = nounNone;
int noun_ten = -1;
int noun_one = -1;
bool blinknoun = false;

int prog = progNone;
int prog_ten = -1;
int prog_one = -1;
bool blinkprog = false;

// 1sec toogle
bool toggle_timer_1000(void *)
{
  if(global_state_1000==false){
    global_state_1000=true;
    toggle1000 = true;
  }
  else
  {
    global_state_1000=false;
    toggle1000 = false;
  }
  return true; // repeat? true
}

// 500msec toggle
bool toggle_timer_500(void *)
{
  if(global_state_500==false){
    global_state_500=true;
    toggle500 = true;
  }
  else
  {
    global_state_500=false;
    toggle500 = false;
  }
  return true; // repeat? true
}

bool toggle_timer_250(void *)
{
  if(global_state_250==false){
    global_state_250=true;
    toggle250 = true;
  }
  else if (global_state_250==true)
  {
    global_state_250=false;
    toggle250 = false;
  }
  return true; // repeat? true
}
