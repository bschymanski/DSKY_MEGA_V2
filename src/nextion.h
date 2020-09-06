#ifndef NEXTION_H
#define NEXTION_H

extern void lightVerblamp(int color);
extern void lightNounlamp(int color);
extern void lightCompActy(int color);
extern void lightProglamp(int color);

extern void printVerbNounProg(void);
extern void printRegister(int dregister, long number, bool leadzero, bool blink, bool alarm, bool signoff);
extern void printRegisterOFF(int dregister);
extern void ELtestlamp(void);
#endif