#ifndef GLOBALS_H
#define GLOBALS_H

// define Colors
const int     green               = 1;
const int     white               = 2;
const int     yellow              = 3;
const int     orange              = 4;
const int     blue                = 5;
const int     red                 = 6;
const int     off                 = 7;

// Toggle variables
extern bool toggle1000;
extern bool toggle500;
extern bool toggle250;
extern bool global_state_1000;
extern bool global_state_500;
extern bool global_state_250;

extern bool toggle_timer_1000(void *);
extern bool toggle_timer_500(void *);
extern bool toggle_timer_250(void *);

extern bool blinkverb;
extern bool blinknoun;
extern bool blinkprog;

extern int verb;
extern int verb_ten;
extern int verb_one;
extern int old1_verb;
extern int old1_verb_ten;
extern int old1_verb_one;
extern int old2_verb;
extern int old2_verb_ten;
extern int old2_verb_one;
extern bool verb_valid;
extern bool verb_error;

extern int noun;
extern int noun_ten;
extern int noun_one;
extern int old1_noun;
extern int old1_noun_ten;
extern int old1_noun_one;
extern int old2_noun;
extern int old2_noun_ten;
extern int old2_noun_one;
extern bool noun_valid;
extern bool noun_error;

extern int prog;
extern int prog_ten;
extern int prog_one;
extern int old1_prog;
extern int old1_prog_ten;
extern int old1_prog_one;
extern int old2_prog;
extern int old2_prog_ten;
extern int old2_prog_one;
// valid Verbs

const int     verbNone                    = -1;
const int     verbLampTest                = 35;
const int     verbInputProg               = 37;
const int     verbDisplayDecimal          = 16;
const int     verbInputNumber             = 21;

// valid Nouns
const int     nounNone                    = -1;
const int     nounIMUAttitude             = 17;
const int     nounIMUgyro                 = 18;
const int     nounClockTime               = 36;
const int     nounDate                    = 37;
const int     nounGPSTime                 = 38;
const int     nounLatLongAltitude         = 43;
const int     nounRangeTgoVelocity        = 68;
const int     nounSelectAudioclip         = 98;
const int     nounNotUsed                 = 100;

// actions to perform when Verb / Noun is correct
const int     actionNone                         = -1;
const int     actionDisplayIMUAttitude           = 1;
const int     actionDisplayRealTimeClock         = 2;
const int     actionDisplayGPS                   = 3;
const int     actionDisplayRangeWith1202Error    = 4;
const int     actionSetTime                      = 5;
const int     actionSetDate                      = 6;
const int     actionPlayAudioclip                = 7;
const int     actionSelectAudioclip              = 8;
const int     actionDisplayIMUGyro               = 9;
const int     actionLampTest                     = 10;
const int     actionDisplayGPSTime               = 11;
const int     actionSetGPSTime                   = 12;

// possible Programs
const int     progNone                 = -1;
const int     progDispTimeDate         = 20;
const int     progSetDateMan           = 21;
const int     progSetTimeGPS           = 22;
const int     progSetDateGPS           = 23;
const int     progSetDebugEEPROM       = 24;
const int     progSetColormodeEEPROM   = 25;
const int     progJFKAudio             = 62;
const int     progApollo11Audio        = 69;
const int     progApollo13Audio        = 70;
const int     progNotUsed              = 100;

// inputmodes
const int     inputIdle                = -1;
const int     inputVerb                = 1;
const int     inputNoun                = 2;


extern int progRunning;
extern int actionRuning;
extern int inputmode;

// Register Values
extern long register_num_1;
extern long register_num_2;
extern long register_num_3;

// keyboard variables
volatile extern int current_key;
volatile extern int current_key_int;
volatile extern bool gotInterrupt;
volatile extern bool keypressed;
extern int old_key;

typedef struct PROGRAM_STRUCT
{
	int VerbNumber;
	int NounNumber;
  int action;
	int ProgramNumber;
}ProgramStruct;

extern ProgramStruct ProgramTable[];

extern short NUM_PROG_TABLE_ENTRIES;

#endif