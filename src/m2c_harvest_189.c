/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "main_callbacks.h"

extern const u16 gTable08483868[];
extern const u16 gTable08483878[];
extern const u16 gTable08483888[];
extern const u8 gTable08483854[];

void sub_080605A0(void);

void sub_080605A0(void) {
 u32 timer;
 u32 choice;
 u32 coordinate;
 s32 offset;
 const u16 *xTable;
 const u8 *coordinates;
 u8 *work;
 choice=((u8 *)gMainContextPointer_03006F74)[0x18];
 timer=gFrameObjects[0].unknown1A+1;
 gFrameObjects[0].unknown1A=timer;
 if((u16)timer>0x60)gFrameObjects[0].unknown1A=0;
 coordinates=gTable08483854;
 work=(u8 *)gMainContextPointer_03006F74;
 coordinate=coordinates[work[0x17]*2];
 xTable=gTable08483868;
 offset=(((gFrameObjects[0].unknown1A>>3)&3)*2)+(choice*8);
 gFrameObjects[0].screenX=coordinate*8+*(const u16 *)((u8 *)xTable+offset);
 gFrameObjects[0].screenY=gTable08483854[work[0x17]*2+1]*8+*(const u16 *)((u8 *)gTable08483878+offset);
 gFrameObjects[0].frameAndGroup=*(const u16 *)((u8 *)gTable08483888+offset);
}
