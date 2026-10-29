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
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "tile_text.h"

struct ContinuedScaleFrames {struct FrameObject preceding[0x21];struct FrameObject frames[3];};
struct ContinuedPartnerFrame {s16 flags,screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;u8 gapC[0x10];u8 tableSelector;u8 gap1D[0xE];u8 byte2B;u8 unknown2C[0x14];};
struct ContinuedPartnerFrames {u8 prefix[0x840];struct ContinuedPartnerFrame first,second;};
struct ContinuedFramePositionWork {u8 pad00[0xF8];u8 directions;u8 padF9[9];s16 frameIndex;u16 x;u16 y;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gActionPartnerPalette_0850F698[32];
extern const u8 gActionPartnerPalette_0850F6B8[32];
extern const u8 gActionPartnerPalette_0850F6D8[32];
extern struct ContinuedFramePositionWork gGraphicsTransferCounter;
extern void sub_0803D450(void);
extern void sub_0803D4AC(void);

void sub_080217D8(void);
void sub_08022480(void);
void sub_0802FB74(void);
void sub_0803AA00(void);

void sub_080217D8(void) {
    if (gFrameObjects[33].unknown23[4]==0x10) {
        sub_08074DE0(0x3E);
        gState0TransferWork.bytes[0xAA]++;
    } else {
        if (gFrameObjects[33].unknown23[4]<=7) {
            gFrameObjects[33].scaleX+=8;
            gFrameObjects[34].scaleX+=8;
            gFrameObjects[35].scaleX+=8;
        } else {
            gFrameObjects[33].scaleX-=8;
            gFrameObjects[34].scaleX-=8;
            gFrameObjects[35].scaleX-=8;
        }
        gFrameObjects[33].unknown23[4]++;
    }
}

void sub_08022480(void) {
    const u8 *palette;struct ContinuedPartnerFrames *frames;u8 *work;u8 *selection;const u8 *const *commands;

    switch(gState0TransferWork.bytes[0x51]) {
    case 0:LeDecompress(gActionPartnerAsset_084CAE20,(void *)0x06014800);palette=gActionPartnerPalette_0850F698;break;
    case 1:LeDecompress(gActionPartnerAsset_084CB128,(void *)0x06014800);palette=gActionPartnerPalette_0850F6B8;break;
    default:LeDecompress(gActionPartnerAsset_084CB43C,(void *)0x06014800);palette=gActionPartnerPalette_0850F6D8;break;
    }
    CpuFastSet(palette, (void *)0x050002E0, 8U);
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

void sub_0802FB74(void) {
    if (gState0TypedWork.widths.word86 == 0x18) {
        gState0TypedWork.widths.word86=0;
        gState0TransferWork.bytes[0xAA]++;
        return;
    }
    gState0TypedWork.widths.word86++;
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        gFrameObjects[0x21].screenX++;
        gFrameObjects[0x22].screenX--;
    } else {
        gFrameObjects[0x21].screenX--;
        gFrameObjects[0x22].screenX++;
    }
}

void sub_0803AA00(void) {
    sub_0803D450();
    if (!(2 & gGraphicsTransferCounter.directions)) {
        gFrameObjects[gGraphicsTransferCounter.frameIndex].unknown23[2]=(u8)gGraphicsTransferCounter.x;
    } else {
        gFrameObjects[gGraphicsTransferCounter.frameIndex].unknown23[2]=(0x20-(u8)gGraphicsTransferCounter.x)&0x1F;
    }
    gFrameObjects[gGraphicsTransferCounter.frameIndex].unknown23[1]=(u8)gGraphicsTransferCounter.y;
    sub_0803D4AC();
}
