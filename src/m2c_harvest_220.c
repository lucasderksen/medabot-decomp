/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"

struct ContinueCounterMode {u8 pad[0x102];s16 mode;};
struct ContinueFrameCounter {u8 pad[0x2A];u8 action;u8 gap[5];u16 counter;u8 tail[0xE];};

extern struct ContinueCounterMode gUnknown_03001800;
extern struct ContinueFrameCounter gUnknown_03002C30[128];
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_080399EC(void);

void sub_080399EC(void) {
 u16 current;
 sub_0803D450();current=gUnknown_03002C30[0].counter;
 if(current!=gUnknown_03001800.mode)gUnknown_03002C30[0].counter=current+1;
 else{gUnknown_03002C30[0].counter=0;sub_0803D4AC();}
 gUnknown_03002C30[0].action=1;
}
