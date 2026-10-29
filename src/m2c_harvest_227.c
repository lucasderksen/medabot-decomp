/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "record_helpers.h"

struct ContinueGraphicsPair {u8 pad[0x102];s16 index,tile;};

extern const u8 *const gUnknown_083AFA0C[];
extern struct ContinueGraphicsPair gUnknown_03001800;
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_0803B3C8(void);

void sub_0803B3C8(void) {
const u8 *const *table;struct ContinueGraphicsPair *work;
 sub_0803D450();table=gUnknown_083AFA0C;work=&gUnknown_03001800;
 LeDecompress(table[work->index*2],(void *)(((u32)(s32)work->tile<<5)+0x06010000u));
 CpuFastSet(*(const u8 *const *)((((u32)((s32)work->index*2)+1)<<2)+(u32)table),(void *)0x050003C0,8);sub_0803D4AC();}
