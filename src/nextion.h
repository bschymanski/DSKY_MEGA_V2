#ifndef NEXTION_H
#define NEXTION_H

extern void lightVerblamp(int color);
extern void lightNounlamp(int color);
extern void lightCompActy(int color);
extern void lightProglamp(int color);

extern void printVerbNounProg(void);
extern void printRegister(int dregister, long number, bool leadzero, bool blink, bool alarm, bool signoff);
extern void printRegisterOFF(int dregister);
extern void print_REG_NUM(int dregister, int place, int number);
extern void print_REG_PLUS(int dregister);
extern void print_REG_MINUS(int dregister);
extern void print_REG_SIGNOFF(int dregister);
extern void print_REG_OFF(int dregister, int place);
extern void ELtestlamp(void);
#endif