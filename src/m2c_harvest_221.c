/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "frame.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "serial.h"

struct ContinueFrameTail {u8 pad[0x102];s16 mode;u16 timer,action,status,phase;};

extern struct ContinueFrameTail gUnknown_03001800;
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_0803AB00(void);

void sub_0803AB00(void) {
 s32 mode;struct FrameObject *frames;
 sub_0803D450();mode=gUnknown_03001800.mode;
 if(mode==0){SnapshotPalettes();gFrameObjects[0x27].unknown2C[3]=mode;gFrameObjects[0x27].unknown23[6]=0x28;}else{gFrameObjects[0x27].unknown23[6]=0x29;}
 frames=gFrameObjects;
 frames[0x27].byte2B=gUnknown_03001800.timer;
 frames[0x27].unknown2C[0]=gUnknown_03001800.action;
 frames[0x27].unknown2C[1]=gUnknown_03001800.status;
 frames[0x27].unknown2C[2]=gUnknown_03001800.phase;
 sub_0803D4AC();
}
