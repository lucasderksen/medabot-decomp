#ifndef GUARD_INTERRUPTS_H
#define GUARD_INTERRUPTS_H

#include "gba.h"

void VBlankHandler(void);
void RunVBlankWork(void);
void HBlankHandler(void);
void DummyInterruptHandler(void);

extern IntrFunc gUnknownCallback_03000B98;
extern IntrFunc gUnknownCallback_030017F0;
extern IntrFunc gUnknownCallback_03002C20;

#endif
