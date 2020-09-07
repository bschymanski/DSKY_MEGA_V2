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
int old1_verb = -1;
int old1_verb_ten = -1;
int old1_verb_one = -1;
int old2_verb = -1;
int old2_verb_ten = -1;
int old2_verb_one = -1;
bool verb_valid = false;
bool verb_error = false;
bool blinkverb = false;

int noun = nounNone;
int noun_ten = -1;
int noun_one = -1;
int old1_noun = -1;
int old1_noun_ten = -1;
int old1_noun_one = -1;
int old2_noun = -1;
int old2_noun_ten = -1;
int old2_noun_one = -1;
bool noun_valid = false;
bool noun_error = false;
bool blinknoun = false;

int prog = progNone;
int prog_ten = -1;
int prog_one = -1;
int old1_prog = -1;
int old1_prog_ten = -1;
int old1_prog_one = -1;
int old2_prog = -1;
int old2_prog_ten = -1;
int old2_prog_one = -1;
bool blinkprog = false;

long register_num_1 = 999999;
long register_num_2 = 999999;
long register_num_3 = 999999;

// keyboard variables
volatile int current_key = 0;
volatile int current_key_int = 0;
volatile bool gotInterrupt = false;
volatile bool keypressed = false;
int old_key = 0;

int progRunning = progNone;
int actionRuning = actionNone;
int inputmode = inputIdle;

ProgramStruct ProgramTable[] =
{
	/*VerbNumber            NounNumber            action                        ProgramNumber                     Description */
	{ verbLampTest,         nounNotUsed,          actionLampTest,              progNotUsed                },  /* V35E N--     - Bulb test */
	{ verbDisplayDecimal,   nounIMUAttitude,      actionDisplayIMUAttitude,    progNotUsed                },  /* V16  N17 E  - Action: IMUAttitude */
  { verbDisplayDecimal,   nounClockTime,        actionDisplayRealTimeClock,  progNotUsed                },  /* V16  N36 E  - Action: Display Time : actionReadTime()*/
  { verbDisplayDecimal,   nounLatLongAltitude,  actionDisplayGPS,            progNotUsed                },  /* V16  N43 E  - Action: Display Lattitude / Longitude / Altidue : actionReadGPS() */
  { verbDisplayDecimal,   nounGPSTime,          actionDisplayGPSTime,        progNotUsed                },  /* V16  N38 E  - Action: Display GPS Time : actionReadGPSTime() */
  { verbDisplayDecimal,   nounIMUgyro,          actionDisplayIMUGyro,        progNotUsed                },  /* V16  N18 E  - Action: IMUGyro */
  { verbDisplayDecimal,   nounSelectAudioclip,  actionPlayAudioclip,         progNotUsed                },  /* V16  N98 E   -  Action: Play Selected AudioClip : actionPlaySelectedAudioclip(int clipnum)*/
  { verbInputProg,        nounClockTime,        actionNone,                  progDispTimeDate           },  /* V37E  36 E    - Program: Display Date / Month / Time : progDispTimeDate()*/ 
  { verbInputProg,        nounNotUsed,          actionNone,                  progSetDateMan             },  /* V37E  21E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progSetTimeGPS             },  /* V37E  22E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progSetDateGPS             },  /* V37E  23E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progSetDebugEEPROM         },  /* V37E  24E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progSetColormodeEEPROM     },  /* V37E  24E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progJFKAudio               },  /* V37E  62E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progApollo11Audio          },  /* V37E  69E*/
  { verbInputProg,        nounNotUsed,          actionNone,                  progApollo13Audio          },  /* V37E  70E*/
  { verbInputNumber,      nounClockTime,        actionSetTime,               progNotUsed                },  /* V21  36E   - Action: Set Time : actionSetTime() */
  { verbInputNumber,      nounGPSTime,          actionSetGPSTime,            progNotUsed                },  /* V21  38E   - Action: Set GPS Time : actionSetGPSTime() */
  { verbInputNumber,      nounSelectAudioclip,  actionSelectAudioclip,       progNotUsed                },  /* V21  98E   - Action: Select AudioClip : aactionSelectAudioclip() actionPlaySelectedAudioclip(int clipnum)*/
  { verbDisplayDecimal,   nounIMUgyro,          actionDisplayIMUGyro,        progNotUsed                }   /* V16E  N18 E - Display IMUGyro */
};

short NUM_PROG_TABLE_ENTRIES = (sizeof(ProgramTable)/sizeof(ProgramStruct));

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
