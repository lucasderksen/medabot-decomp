/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"

struct ContinueFrameSetup { u8 pad[0x102];s16 slot;u16 counter;u16 command;u16 frame;u16 xscale;u16 yscale;};

extern const u8 *const gState0NextCommands_083B6100[];
extern struct ContinueFrameSetup gUnknown_03001800;
extern void LoadActionHalfwordScriptParams(void);
extern void AdvanceActionHalfwordScript(void);

void sub_0803B428(void);

void sub_0803B428(void) {
    struct FrameObject *frames;
    struct FrameObject *temp_r1;

    LoadActionHalfwordScriptParams();
    frames=gFrameObjects;
    temp_r1 = &frames[gUnknown_03001800.slot];
    temp_r1->flags |= 0x200;
    frames[gUnknown_03001800.slot].scaleX = (u8) gUnknown_03001800.xscale;
    frames[gUnknown_03001800.slot].scaleY = (u8) gUnknown_03001800.yscale;
    frames[gUnknown_03001800.slot].angle = 0;
    frames[gUnknown_03001800.slot].unknown23[3] = (u8) gUnknown_03001800.frame;
    frames[gUnknown_03001800.slot].unknown2C[1] = (u8) gUnknown_03001800.command;
    frames[gUnknown_03001800.slot].unknown23[0] = (u8) gUnknown_03001800.counter;
    frames[gUnknown_03001800.slot].unknown23[6] = 0x34;
    InitFrameObjectCommands(gState0NextCommands_083B6100[frames[gUnknown_03001800.slot].unknown2C[1]], (u8) gUnknown_03001800.slot);
    AdvanceActionHalfwordScript();
}
