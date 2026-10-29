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
#include "equipment_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "interrupts.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"
#include "utility_helpers.h"

struct ContinuedFrame21 {u8 prefix[0x840];struct FrameObject frame;};
struct ContinuedPartnerFrame {s16 flags,screenX,screenY;u16 frameAndGroup;u8 scaleX,scaleY,palette,priority;u8 gapC[0x10];u8 tableSelector;u8 gap1D[0xE];u8 byte2B;u8 unknown2C[0x14];};
struct ContinuedPartnerFrames {u8 prefix[0x840];struct ContinuedPartnerFrame first,second;};
struct ContinuedAssetSelectionWork {u8 pad00[0x38];u8 selection;};

extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084DD484[];
extern const u8 gUnknown_084DD6A0[];
extern const u8 gUnknown_084DDAE4[];
extern const u8 gUnknown_084DDD70[];
extern const u8 gUnknown_084E09A0[];
extern const u8 gUnknown_08510178[32];
extern const u8 gUnknown_08510198[32];
extern const u8 gUnknown_085101B8[32];
extern const u8 gUnknown_085101D8[32];
extern const u8 gUnknown_08510338[32];
extern const u8 gUnknown_087C60B0[];
extern const u8 gUnknown_087C613C[];
extern const u8 gUnknown_087C61D0[];
extern const u8 gUnknown_087C63B4[];
extern const u8 gUnknown_087C643C[32];
extern const u8 gUnknown_087C645C[32];
extern const u8 gUnknown_087C647C[32];
extern const u8 gUnknown_087C649C[32];
extern s8 gUnknown_03006F90;
extern struct ContinuedAssetSelectionWork gGraphicsTransferCounter;
extern u8 gUnknown_03006F84;
extern void sub_080697B4(u8,u8,u8);

void sub_08028CC8(void);
void sub_0802ACF4(void);
void sub_08069530(void);

void sub_08028CC8(void) {
    struct ContinuedFrame21 *frames;
    switch(gState0TransferWork.bytes[0x51]) {
    case 0:
        LeDecompress(gUnknown_084DD484,(void *)0x06014800);
        CpuFastSet(gUnknown_08510178,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown2C[2]=91;
        break;
    case 1:
        LeDecompress(gUnknown_084DD6A0,(void *)0x06014800);
        CpuFastSet(gUnknown_08510198,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown2C[2]=91;
        break;
    case 2:
        LeDecompress(gUnknown_084DDAE4,(void *)0x06014800);
        CpuFastSet(gUnknown_085101B8,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown2C[2]=91;
        break;
    case 3:
        LeDecompress(gUnknown_084DDD70,(void *)0x06014800);
        CpuFastSet(gUnknown_085101D8,(void *)0x050002E0,8);
        gFrameObjects[0x21].unknown2C[2]=92;
        break;
    }
    frames=(struct ContinuedFrame21 *)gFrameObjects;
    frames->frame.flags=0xC604;
    frames->frame.tableSelector=0;
    frames->frame.screenY=0xE0;
    frames->frame.palette=7;
    frames->frame.scaleX=0x40;
    frames->frame.scaleY=0x40;
    frames->frame.angle=0;
    frames->frame.priority=0xF0;
    sub_08040B90(gState0NextCommands_083B6100[frames->frame.unknown2C[2]],0x21);
    if(1&gState0TransferWork.bytes[0xF8])frames->frame.screenX=0xB8;
    else {
        frames->frame.flags|=0x1000;
        frames->frame.screenX=0x38;
    }
    sub_08074DE0(0x61);
    gState0TransferWork.bytes[0xAA]++;
}

void sub_0802ACF4(void) {
    struct ContinuedPartnerFrames *frames;u8 *work;u8 *selection;const u8 *const *commands;

    LeDecompress(gUnknown_084E09A0,(void *)0x06014800);
    CpuFastSet(gUnknown_08510338,(void *)0x050002E0,8);
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
    commands=gState0NextCommands_083B6100;sub_08040B90(commands[0x64],0x21);
    frames->second.flags = -0x39DC;
    frames->second.tableSelector = 0;
    frames->second.screenX = (u16)gFrameObjects[*selection*4+0x5D].screenX + 0x20;
    frames->second.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 4;
    frames->second.palette = 7;
    frames->second.priority = (u8)-0x10;
    frames->second.scaleX = 0x80;
    frames->second.scaleY = 0x80;
    frames->second.frameAndGroup=0x7901;
    frames->second.byte2B = 0x1C;
    frames->second.unknown2C[0] = 0x80;
    frames->second.unknown2C[1] = 0;
    sub_08074DE0(0x33U);
    work[0xAA]++;
}

void sub_08069530(void) {
    struct ContinuedAssetSelectionWork *work;
    u32 zero;
    volatile u32 *dma;
    gUnknown_03006F90 = 1;
    *(volatile u16 *)0x0400000C=0x1E0A;
    *(volatile u16 *)0x0400000E=0x1F0B;
    work=&gGraphicsTransferCounter;
    work->selection = gUnknown_03006F84;
    zero=0;
    sub_08043C08((u32) work->selection, 0U);
    sub_08043E54();
    sub_08043F9C();
    sub_080441A8(gEquipmentAssets_083B2628[(work->selection * 5) + 1]);
    LZ77UnCompVram(gUnknown_087C60B0, (void *)0x0600C800);
    LZ77UnCompVram(gUnknown_087C613C, (void *)0x0600C880);
    LZ77UnCompVram(gUnknown_087C61D0, (void *)0x0600C9C0);
    LZ77UnCompVram(gUnknown_087C63B4, (void *)0x0600CC40);
    dma=(volatile u32 *)0x040000D4;
    dma[0] = (u32)gUnknown_087C643C;
    dma[1] = 0x05000100;
    dma[2] = 0x84000008;
    (void)dma[2];
    dma[0] = (u32)gUnknown_087C645C;
    dma[1] = 0x05000120;
    dma[2] = 0x84000008;
    (void)dma[2];
    dma[0] = (u32)gUnknown_087C647C;
    dma[1] = 0x05000140;
    dma[2] = 0x84000008;
    (void)dma[2];
    dma[0] = (u32)gUnknown_087C649C;
    dma[1] = 0x05000160;
    dma[2] = 0x84000008;
    (void)dma[2];
    sub_080697B4(0, 2, 4);
    sub_080697B4(0, 2, 7);
    sub_080697B4(0, 2, 0xA);
    sub_080697B4(1, 6, 3);
    sub_080697B4(2, 0xE, 3);
    sub_080697B4(3, 0x1A, 4);
    sub_080697B4(3, 0x1A, 7);
    sub_080697B4(3, 0x1A, 0xA);
    gBgScroll2.x = zero;
    gBgScroll2.y = zero;
    gBgScroll3.x = zero;
    gBgScroll3.y = zero;
    gUnknownCallback_030017F0 = sub_08044100;
}
