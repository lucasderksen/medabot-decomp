/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "later_graphics.h"
#include "later_helpers.h"
#include "main.h"
#include "main_callbacks.h"
#include "serial.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct ContinuedAngleBacking {u8 prefix[0x858];u16 angle;u8 gap85A[0x14];u8 speed;};
struct ContinuedResetWork { u8 pad[0xC88]; u8 first; u8 second; u8 tail[0x36]; };
struct LaterDispatchBuffer { u8 pad[12]; u8 kind; };

extern const u8 gUnknown_083AE950[];
extern struct ContinuedResetWork gContinuedWork_030057E0;
extern struct LaterDispatchBuffer gLaterBuffer_03006D20;

void sub_0802BE44(void);
void sub_080476E8(u32 mode);

void sub_0802BE44(void) {
 u8 *work=gState0TypedWork.bytes;
 u8 *phase=work+0x84;
 u16 *timer;
 u32 next;u16 angle;
 const u8 *table;
 struct ContinuedAngleBacking *frames;
 if(*phase<=2u) {
   timer=(u16 *)(work+0x86);
   if(*timer==0) {*phase+=1;sub_08074DE0(0x4C);}
   next=*timer+1;
   *timer=next;
   table=gUnknown_083AE950;
   {u32 offset=*phase-1; const u8 *limit=(const u8 *)((u32)table+offset); if((u16)next==*limit) *timer=0;}
 }
 frames=(struct ContinuedAngleBacking *)gFrameObjects;
 if(frames->angle==0) frames->speed+=1;
 angle=((frames->speed<<4)+frames->angle)&0x3FF;
 frames->angle=angle;
 if(frames->speed==5 && angle==0) {
  sub_08040CD0(0x21,1);
  gState0TransferWork.bytes[0xAA]++;
 }
}

void sub_080476E8(u32 mode) {
    switch(mode) {
    case 4:
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 16;
        break;
    case 5:
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 32;
        break;
    case 6:
        gMainState = 1;
        gMainSubstate = 2;
        gUnknown_0300137C = 8;
        break;
    case 7:
        gLaterBuffer_03006D20.kind = 7;
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 5;
        break;
    case 8:
        gLaterBuffer_03006D20.kind = 8;
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 5;
        break;
    case 10:
        sub_08047574();
        sub_08049714(&gContinuedWork_030057E0,0xCC0);
        gUnknown_03000588 = 1;
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 0;
        break;
    case 11: {
        sub_08047574();
        gContinuedWork_030057E0.first = 0;
        gContinuedWork_030057E0.second = 0;
        gUnknown_03000588=1;
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 10;
        break;
    }
    case 9:
        gUnknown_03000588=1;
    case 0: case 1: case 2: case 3: case 12:
        gMainState = 1;
        gMainSubstate = 1;
        gUnknown_0300137C = 5;
        break;
    }
}
