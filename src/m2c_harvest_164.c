/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "compression.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"

struct ContinuedPartnerFrame {s16 flags,screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;u8 gapC[0x10];u8 tableSelector;u8 gap1D[0xE];u8 byte2B;u8 unknown2C[0x14];};
struct ContinuedPartnerFrames {u8 prefix[0x840];struct ContinuedPartnerFrame first,second;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084E05C4[];
extern const u8 gUnknown_08510318[32];

void sub_0802AAF8(void);

void sub_0802AAF8(void) {
    struct ContinuedPartnerFrames *frames;u8 *work;u8 *selection;const u8 *const *commands;

    LeDecompress(gUnknown_084E05C4,(void *)0x06014800);
    CpuFastSet(gUnknown_08510318,(void *)0x050002E0,8);
    frames=(struct ContinuedPartnerFrames *)gFrameObjects;
    frames->first.flags = -0x39DC;
    frames->first.tableSelector = 0;
    work=gState0TransferWork.bytes;selection=work+0x87;
    frames->first.screenX = (u16)gFrameObjects[*selection*4+0x5D].screenX - 0x20;
    frames->first.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 4;
    frames->first.palette = 7;
    frames->first.priority = (u8)-0x10;
    frames->first.scaleX = 0x80;
    frames->first.scaleY = 0x80;
    frames->first.byte2B = 0x1C;
    frames->first.unknown2C[0] = 0;
    frames->first.unknown2C[1] = 0;
    commands=gState0NextCommands_083B6100;sub_08040B90(commands[0x1C],0x21);
    frames->second.flags = -0x39DC;
    frames->second.tableSelector = 0;
    frames->second.screenX = (u16)gFrameObjects[*selection*4+0x5D].screenX + 0x20;
    frames->second.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 4;
    frames->second.palette = 7;
    frames->second.priority = (u8)-0x10;
    frames->second.scaleX = 0x80;
    frames->second.scaleY = 0x80;
    frames->second.byte2B = 0x1C;
    frames->second.unknown2C[0] = 0x80;
    frames->second.unknown2C[1] = 0;
    sub_08040B90(commands[0x1C],0x22);
    sub_08074DE0(0x33U);
    work[0xAA]++;
}
