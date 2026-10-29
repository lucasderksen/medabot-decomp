/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_scene_data.h"
#include "continued_scene_records.h"
#include "frame.h"

extern const s16 *const gUnknown_083CE164[];
extern const u8 gUnknown_083CE374[];
extern u8 gUnknown_03001800[];

void sub_0803D4AC(void);

void sub_0803D4AC(void) {

 const s16 *const *tables=gUnknown_083CE164;
 u8 *work=gUnknown_03001800;
 const s16 *table=tables[work[0xF9]];
 const u8 *lengths=gUnknown_083CE374;
 u16 *cursor=(u16*)(work+0x100);
 u32 index=*cursor;
 s32 opcode=table[index++];
 const u8 *length=(const u8*)((u32)lengths+opcode);
 *cursor=index+*length;
}
