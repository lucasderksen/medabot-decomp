#ifndef GUARD_INITIALIZATION_H
#define GUARD_INITIALIZATION_H

#include "gba.h"

void InitInterrupts(void);
void ResetMemory(void);
void ResetSpritesAndVram(void);

extern struct OamEntry gOamShadow[128];
extern IntrFunc gIntrTable[14];
extern u32 gIntrMainBuffer[0x200];

u16 Unknown_0805DEB0(void);
#endif
