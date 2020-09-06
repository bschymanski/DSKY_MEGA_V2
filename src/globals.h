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

extern int noun;
extern int noun_ten;
extern int noun_one;

extern int prog;
extern int prog_ten;
extern int prog_one;

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

#endif