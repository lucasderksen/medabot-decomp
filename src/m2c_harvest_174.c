/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct ContinuedF4D0Frame33 { u8 pad00[0x840]; struct FrameObject frame; };

extern const u8 *const gState0NextCommands_083B6100[0x69];
extern const u8 gUnknown_084E11B8[];
extern const u8 gUnknown_085103D8[0x40];

void sub_0802F4D0(void);

void sub_0802F4D0(void) {
 struct ContinuedF4D0Frame33 *frames;
 u8 *work;
 u8 *bank;
 u32 zero;
 LeDecompress(gUnknown_084E11B8, (void *)0x06014800);
 CpuFastSet(gUnknown_085103D8, (void *)0x050002E0, 0x10u);
 frames = (struct ContinuedF4D0Frame33 *)&gFrameObjects;
 frames->frame.flags = (zero = 0, 0xCC04);
 frames->frame.tableSelector = zero;
 work = gState0TransferWork.bytes;
 bank = work + 0x87;
 frames->frame.screenX = (u16)gFrameObjects[*bank * 4 + 0x5D].screenX;
 frames->frame.screenY = (u16)gFrameObjects[*bank * 4 + 0x5D].screenY - 4;
 frames->frame.palette = 7;
 frames->frame.priority = zero;
 sub_08040B90(gState0NextCommands_083B6100[0x68], 0x21);
 sub_08074DE0(0x2C);
 work[0xAA]++;
}
