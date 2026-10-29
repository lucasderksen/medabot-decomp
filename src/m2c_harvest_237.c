/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "utility_helpers.h"

struct ContinueAssetWork {u8 pad[0x102];s16 index;};

extern struct ContinueAssetWork gUnknown_03001800;extern const u8 *const gUnknown_083AFADC[];
extern void sub_0803D450(void);extern void sub_0803D4AC(void);

void sub_0803B19C(void);

void sub_0803B19C(void) {
const u8 *const *table;struct ContinueAssetWork *work;sub_0803D450();table=gUnknown_083AFADC;work=&gUnknown_03001800;sub_08044B28(table[work->index*2],(void *)0x02000000);CpuFastSet(*(const u8 *const *)((((u32)((s32)work->index*2)+1)<<2)+(u32)table),(void *)0x050003C0,8);sub_0803D4AC();}
