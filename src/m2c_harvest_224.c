/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "display_helpers.h"
#include "equipment_helpers.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct ContinueResetRow {u8 pad[0x40];u8 first;u8 gap[0x18];u8 second;u8 gap2[0x5F];u8 third,status;u8 unknown;u8 clear,flags;u8 tail[0x42];};
struct ContinuePaletteWork {u8 pad[0x102];s16 mode,index;};

extern struct ContinuePaletteWork gUnknown_03001800;
extern struct ContinueResetRow gUnknown_03000590[];
extern u8 gUnknown_0202F800[];
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_08036FA0(u32 bank);
void sub_0803AC4C(void);

void sub_08036FA0(u32 bank) {

 u8 *setup=(u8 *)gUnknown_03000590;u32 shift=bank<<8;struct ContinueResetRow *root=(struct ContinueResetRow *)(shift+(u32)setup);
 u8 *out=(u8 *)root+0x40;u32 zero=0;u8 *flags,*clear,*first;
 *out=zero;out+=0x19;*out=zero;out+=0x60;*out=zero;
 root->status=2;flags=(u8 *)root+0xBA;clear=&root->clear;*clear=zero;flags+=3;*flags=0xE4u&*flags;*clear=zero;
 first=setup+0xC4;sub_0803F624((u8 *)(shift+(u32)first),0xC,zero);
 setup+=0xDC;sub_0803F624((u8 *)(shift+(u32)setup),8,0);
}

void sub_0803AC4C(void) {

 sub_0803D450();
 if(gUnknown_03001800.mode==0){u32 offset=(u32)(s32)gUnknown_03001800.index<<5;CpuFastSet((void *)(offset+0x05000000),(void *)(offset+(u32)gEquipmentPaletteShadow),8);}
 else{u32 offset=(u32)(s32)gUnknown_03001800.index<<5;CpuFastSet((void *)(offset+0x05000200),(void *)(offset+(u32)gUnknown_0202F800),8);}
 sub_0803D4AC();
}
