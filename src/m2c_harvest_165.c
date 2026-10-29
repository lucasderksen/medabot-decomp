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

struct ContinuedFrame9Setup {
    u8 prefix[0x240]; u16 flags; s16 x,y; u16 group;
    u8 scaleX,scaleY,palette,priority; u8 gap24C[0xC]; u16 angle;
    u8 gap25A[2]; u8 selector25C; u8 gap25D[7]; u8 increment264; u8 gap265[0xB]; u16 savedX; s16 savedY;
};
struct ContinuedFrame33AnimationRoot {
    u8 pad00[0x840]; u16 flags840; u8 pad842[4]; u16 frame846;
    u8 scaleX848; u8 scaleY849; u8 pad84A[0xE]; u16 angle858;
    u8 pad85A[0xA]; u8 increment864; u8 pad865[0xB]; s16 x870; s16 y872;
    u8 pad874[0x2000-0x874];
};
struct ContinuedFrame33CommandRoot {
    u8 pad00[0x840]; u16 flags840; u8 pad842[4]; u16 frame846;
    u8 scaleX848; u8 scaleY849; u8 palette84A; u8 pad84B[0xD]; u16 angle858;
    u8 pad85A[9]; u8 reset863; u8 increment864; u8 pad865[0xB]; s16 x870; s16 y872;
    u8 pad874[0x2000-0x874];
};
struct ContinuedFramePairNext {u8 prefix[0x840];struct FrameObject first,second;};
struct ContinuedFrame34Setup {
    u8 prefix[0x858]; u16 angle33; u8 gap85A[0x26]; u16 flags34;
    s16 x34,y34; u16 group34; u8 scaleX34,scaleY34,palette34,priority34;
    u8 gap88C[0x10]; u8 selector34;
};
struct ContinuedRotatingFrame33Root { u8 pad00[0x842]; s16 x842; u8 pad844[0x14]; u16 angle858; u8 pad85A[0xD]; u8 counter867; };
struct ContinuedTransferPhaseAA { u8 pad00[0xAA]; u8 phaseAA; };

extern const u16 gUnknown_0850FDF8[16];
extern const u16 gUnknown_0850FED8[32];
extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_084D7ABC[];
extern const u8 gUnknown_084D8528[];
extern const u8 gUnknown_084D8778[];
extern const u8 gUnknown_084DFBC8[];
extern const u8 gUnknown_084E4658[32];
extern const u8 gUnknown_0850FF18[32];
extern const u8 gUnknown_085102D8[32];
extern struct ContinuedRotatingFrame33Root gUnknown_03002C30;
extern struct ContinuedTransferPhaseAA gUnknown_03001800;
extern u32 sub_080353CC(u32);
extern void sub_08040CD0(u8,u8);

void sub_0801D45C(void);
void sub_08024A30(void);
void sub_08025B9C(void);
void sub_08026184(void);
void sub_08027BEC(void);
void sub_0802A110(void);
void sub_0802F13C(void);
void sub_08030494(void);

void sub_0801D45C(void) {
    struct ContinuedFrame9Setup *frames;
    u8 *work;
    sub_08040CD0(9u,1u);
    frames = (struct ContinuedFrame9Setup *)gFrameObjects;
    frames->flags = 0xC404;
    frames->selector25C = 0;
    work = gState0TransferWork.bytes;
    frames->y = (u16)gFrameObjects[work[0x87]*4+0x5D].screenY - 4;
    frames->x = (u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
    frames->palette = 6;
    frames->priority = 0xF0;
    frames->savedX = (u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->savedY = (u16)gFrameObjects[work[0x88]*4+0x5D].screenY - 4;
    frames->increment264 = 6;
    sub_08040B90(gState0NextCommands_083B6100[0x1B],9u);
    work[0xAA] += 1;
}

void sub_08024A30(void) {
    struct ContinuedFrame33AnimationRoot *frames;
    u8 *work;
    u16 zero;
    u32 flags;
    LeDecompress(gUnknown_084D7ABC,(void *)0x06014800);
    CpuFastSet(gUnknown_0850FDF8,(void *)0x050002E0,8u);
    frames = (struct ContinuedFrame33AnimationRoot *)gFrameObjects;
    frames->flags840 |= 0x220u;
    frames->scaleX848 = (zero=0,0x40);
    frames->scaleY849 = 0x40;
    frames->angle858 = zero;
    frames->frame846 = 0x4E00;
    work = gState0TransferWork.bytes;
    frames->x870 = (u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->y872 = (u16)gFrameObjects[work[0x88]*4+0x5D].screenY - 4;
    frames->increment864 = 6;
    gState0TypedWork.widths.word86 = 0x3C;
    work[0xAA] += 1;
}

void sub_08025B9C(void) {
    struct ContinuedFrame33CommandRoot *frames;
    u8 *work;
    u32 zero;
    u8 command;
    u16 zeroHalf;
    u32 flags;
    LeDecompress(gUnknown_084D8528,(void *)0x06014800);
    CpuFastSet(gUnknown_0850FED8,(void *)0x050002E0,0x10u);
    frames = (struct ContinuedFrame33CommandRoot *)gFrameObjects;
    frames->flags840 |= 0x220u;
    frames->scaleX848 = (zero=0,zeroHalf=0,0x40);
    frames->scaleY849 = 0x40;
    frames->angle858 = zeroHalf;
    frames->palette84A = 7;
    work = gState0TransferWork.bytes;
    frames->x870 = (u16)gFrameObjects[work[0x88]*4+0x5D].screenX;
    frames->y872 = (u16)gFrameObjects[work[0x88]*4+0x5D].screenY - 4;
    frames->increment864 = 6;
    frames->reset863 = zero;
    gState0TypedWork.bytes[0x84] = 0x48;
    command = gState0TypedWork.bytes[0x84];
    sub_08040B90(gState0NextCommands_083B6100[command],0x21u);
    gState0TypedWork.widths.word86 = 0x3C;
    work[0xAA] += 1;
}

void sub_08026184(void) {
    struct ContinuedFramePairNext *frames;u8 *work;u8 *selection;
    LeDecompress(gUnknown_084D8778, (void *)0x06014800);
    CpuFastSet(gUnknown_0850FF18, (void *)0x050002E0, 8U);
    frames=(struct ContinuedFramePairNext *)gFrameObjects;
    frames->first.flags = 0xC624;
    work=gState0TransferWork.bytes;
    if (1 & work[0xF8]) {
        frames->first.flags |= 0x1000;
    }
    frames->first.tableSelector = 0;
    selection=work+0x87;
    frames->first.screenX = (s16) (u16)gFrameObjects[*selection*4+0x5D].screenX;
    frames->first.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 6;
    frames->first.angle = 0;
    frames->first.scaleX = 0x40;
    frames->first.scaleY = 0x40;
    frames->first.palette = 7;
    frames->first.priority = 0xF0;
    frames->first.frameAndGroup = 0x616;
    frames->first.unknown23[0] = 0;
    sub_08040B90(gState0NextCommands_083B6100[0x4A], 0x21U);
    work[0xAA] = (u8) (work[0xAA] + 1);
}

void sub_08027BEC(void) {
    struct ContinuedFrame34Setup *frames;
    u8 *work;
    u32 zero;
    gState0TypedWork.widths.word86 += 1;
    zero = 0;
    frames = (struct ContinuedFrame34Setup *)gFrameObjects;
    frames->angle33 = (frames->angle33 + 0x40u) & 0x3FFu;
    frames->flags34 = 0xC624;
    frames->selector34 = zero;
    work = gState0TransferWork.bytes;
    frames->x34 = (u16)gFrameObjects[work[0x87]*4+0x5D].screenX;
    frames->y34 = (u16)gFrameObjects[work[0x87]*4+0x5D].screenY - 4;
    frames->scaleX34 = 0x80;
    frames->scaleY34 = 0x80;
    frames->palette34 = 7;
    frames->priority34 = 0xF1;
    frames->group34 = 0x6700;
    work[0xAA] += 1;
}

void sub_0802A110(void) {
    struct ContinuedFramePairNext *frames;u8 *work;u8 *selection;
    LeDecompress(gUnknown_084DFBC8, (void *)0x06014800);
    CpuFastSet(gUnknown_085102D8, (void *)0x050002E0, 8U);
    CpuFastSet(gUnknown_084E4658, (void *)0x050002C0, 8U);
    frames=(struct ContinuedFramePairNext *)gFrameObjects;
    frames->first.flags = 0xC604;
    frames->first.tableSelector = 0;
    frames->first.screenX = 0x78;
    work=gState0TransferWork.bytes;selection=work+0x87;
    frames->first.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 4;
    frames->first.palette = 7;
    frames->first.priority = 0xF0;
    frames->first.scaleX = 4;
    frames->first.scaleY = 4;
    frames->first.angle = 0;
    sub_08040B90(gState0NextCommands_083B6100[0x61], 0x21U);
    frames->second.flags = 0xC604;
    frames->second.tableSelector = 0;
    frames->second.screenX = 0x78;
    frames->second.screenY = (u16)gFrameObjects[*selection*4+0x5D].screenY - 4;
    frames->second.palette = 6;
    frames->second.priority = 0xE0;
    frames->second.scaleX = 4;
    frames->second.scaleY = 4;
    frames->second.angle = 0;
    frames->second.frameAndGroup = 0x7604;
    sub_08074DE0(0x67U);
    work[0xAA] = (u8) (work[0xAA] + 1);
}

void sub_0802F13C(void) {
    struct ContinuedRotatingFrame33Root *firstFrames;
    sub_080353CC(0x21u);
    firstFrames = &gUnknown_03002C30;
    if (firstFrames->counter867 == 0x20) {
        firstFrames->angle858 = 0;
        gState0TypedWork.bytes[0x84] = 1;
        gUnknown_03001800.phaseAA += 1;
    } else {
        u8 *firstWork = gState0TransferWork.bytes;
        u32 direction = firstWork[0xF8];
        u32 directionBit = (direction & 1u) & direction;
        u8 *retainedWork = firstWork;
        if (!directionBit) {
            firstFrames->angle858 = (firstFrames->angle858 + 0x20u) & 0x3FFu;
        } else {
            firstFrames->angle858 = (firstFrames->angle858 - 0x20u) & 0x3FFu;
        }
        {
            struct ContinuedRotatingFrame33Root *laterFrames = &gUnknown_03002C30;
            if (!(laterFrames->counter867 & 1u)) {
                if (!(retainedWork[0xF8] & 1u)) {
                    laterFrames->x842 += 1;
                } else {
                    laterFrames->x842 -= 1;
                }
            }
            laterFrames->counter867 += 1;
        }
    }
}

void sub_08030494(void) {

    if (gState0TypedWork.widths.word86 == 0x20) {
        sub_08040CD0(0x21U, 4U);
        gState0TypedWork.widths.word86 = 0;
        gState0TransferWork.bytes[0xAA] = (u8) (gState0TransferWork.bytes[0xAA] + 1);
        return;
    }
    if (!(3 & gState0TypedWork.widths.word86)) {
        gFrameObjects[0x21].screenY = ((u16)gFrameObjects[0x21].screenY - 1)&0xFF;
        gFrameObjects[0x22].screenY = ((u16)gFrameObjects[0x22].screenY + 1)&0xFF;
        gFrameObjects[0x23].screenY = ((u16)gFrameObjects[0x23].screenY - 1)&0xFF;
        gFrameObjects[0x24].screenY = ((u16)gFrameObjects[0x24].screenY + 1)&0xFF;
    }
    if (1 & gState0TypedWork.widths.word86) {
        gFrameObjects[0x21].flags |= 0x8000;
        gFrameObjects[0x22].flags |= 0x8000;
        gFrameObjects[0x23].flags |= 0x8000;
        gFrameObjects[0x24].flags|=0x8000;
    } else {
        gFrameObjects[0x21].flags &= 0x7FFF;
        gFrameObjects[0x22].flags &= 0x7FFF;
        gFrameObjects[0x23].flags &= 0x7FFF;
        gFrameObjects[0x24].flags&=0x7FFF;
    }
    gState0TypedWork.widths.word86 += 1;
}
