#ifndef NEOPIXEL_H
#define NEOPIXEL_H

// give all the Neopixel Lamps a Name
//const short     lampNoun            = 26;
//const short     lampProg            = 25;
//const short     lampVerb            = 24;
//const short     lampCompActy        = 23;
const short     lampTemp            = 6;
const short     lampGimbalLock      = 5;
const short     lampProgCond        = 4;
const short     lampRestart         = 3;
const short     lampTracker         = 2;
const short     lampAlt             = 1;
const short     lampVel             = 0;
const short     lampClk             = 7;
const short     lampPosition        = 8;
const short     lampOprErr          = 9;
const short     lampKeyRelease      = 10;
const short     lampSTBY            = 11;
const short     lampNoAtt           = 12;
const short     lampUplinkActy      = 13;


// provide the color and the lamp
extern void setLamp(int color, int lampNumber);
extern void NeoPixelSetup(void);
extern void testLamp(void);

#endif