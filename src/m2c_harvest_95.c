/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bg_scroll.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "eeprom.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "render_work.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct FinalFrameBacking {
 u8 padding[0x280];
 u16 flags;
 s16 x,y;
 u16 frame;
 u8 scales[2],palette,priority;
 u8 gap[0x10];
 u8 table;
};

extern s32 gState0NextCommands_083B6100;
extern s32 gUnknown_0850F9D8;
extern s32 gUnknown_0850F9F8;
extern u8 gUnknown_084D178C;
extern u8 gUnknown_084D1CDC;

void sub_0802036C(void);
void sub_08020474(void);

void sub_0802036C(void) {
 u32 work;
 struct FinalFrameBacking *objects;
 s32 offset;u32 zero;
 s16 x,y;
 LeDecompress(&gUnknown_084D178C,(void*)0x06010800);
 CpuFastSet(&gUnknown_0850F9D8,(void*)0x050003C0,8);
 work=(u32)&gState0TransferWork;
 if((*(u8*)(work+0xF8)&2)==0){offset=0xAC;offset<<=1;}else{offset=0xAA;offset<<=1;}
 x=*(s16*)(work+offset);offset+=2;
 y=*(s16*)(work+offset);
 objects=(struct FinalFrameBacking*)gFrameObjects;
 objects->flags=(zero=0,0xC404);
 objects->table=zero;
 objects->x=x;objects->y=y;
 objects->palette=0xE;objects->priority=0x80;
 {u32 commands=(u32)&gState0NextCommands_083B6100;sub_08040B90(*(u8**)(commands+0x94),0xA);}
 sub_08074DE0(0x37);
 gState0TransferWork.bytes[0xAA]++;
}

void sub_08020474(void) {
 u32 work;
 struct FinalFrameBacking *objects;
 s32 offset;u32 zero;
 s16 x,y;
 LeDecompress(&gUnknown_084D1CDC,(void*)0x06010800);
 CpuFastSet(&gUnknown_0850F9F8,(void*)0x050003C0,8);
 work=(u32)&gState0TransferWork;
 if((*(u8*)(work+0xF8)&2)==0){offset=0xAC;offset<<=1;}else{offset=0xAA;offset<<=1;}
 x=*(s16*)(work+offset);offset+=2;
 y=*(s16*)(work+offset);
 objects=(struct FinalFrameBacking*)gFrameObjects;
 objects->flags=(zero=0,0xC404);
 objects->table=zero;
 objects->x=x;objects->y=y;
 objects->palette=0xE;objects->priority=0x80;
 {u32 commands=(u32)&gState0NextCommands_083B6100;sub_08040B90(*(u8**)(commands+0x98),0xA);}
 sub_08074DE0(0x2B);
 gState0TransferWork.bytes[0xAA]++;
}
