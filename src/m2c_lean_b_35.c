/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "bios_lz77_streams.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_samples.h"
#include "sound_tables.h"
#include "sound_voice.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Dma69910 { u32 source, destination, control; };
struct Timeline6C218
{
    u8 unknown00[8];
    s32 time;
    u8 unknown0C;
    s8 offset;
    s8 count;
    u8 lanes[0x35];
    s32 target;
};
struct Dma6CFEC { u32 source, destination, control; };

extern const s8 gUnknown_08485924[];
extern const u32 gUnknown_087B4CE4[];
extern s32 sub_0807CD2C(s32, s32);
extern struct Timeline6C218 gTimeline6C218 asm("gCounter6ED08_03001800");
extern u32 sub_08074224(const void *record);
extern void sub_0806D398(void);

void sub_08069910(void);
void sub_0806C218(void);
void sub_0806CFEC(void);
void sub_08073524(struct SoundChannelState *channel, s16 *frequency, u16 *control);

void sub_08069910(void) {

    u16 buffer[0x400];
    volatile s32 fill;
    s32 i;

    LZ77UnCompVram(gBiosLz77Stream_087B3EC0, (void *)0x0600C000);
    fill = 0;
    {
        volatile struct Dma69910 *dma = (void *)0x040000D4;
        dma->source = (u32)&fill;
        dma->destination = (u32)buffer;
        dma->control = 0x85000200;
        (void)dma->control;
    }
    LZ77UnCompVram(gBiosLz77Stream_087B4904, buffer);
    for (i = 0; i < 0x280; i++)
        buffer[i] += 0xC000;
    {
        volatile struct Dma69910 *dma = (void *)0x040000D4;
        dma->source = (u32)buffer;
        dma->destination = 0x0600E800;
        dma->control = 0x80000400;
        (void)dma->control;
    }
    LZ77UnCompVram(gBiosLz77Stream_087B4A40, buffer);
    for (i = 0; i < 0x400; i++)
        buffer[i] += 0xC000;
    {
        volatile struct Dma69910 *dma = (void *)0x040000D4;
        dma->source = (u32)buffer;
        dma->destination = 0x0600F800;
        dma->control = 0x80000400;
        (void)dma->control;
    }
    {
        volatile struct Dma69910 *dma = (void *)0x040000D4;
        dma->source = (u32)gUnknown_087B4CE4;
        dma->destination = 0x05000180;
        dma->control = 0x80000020;
        (void)dma->control;
    }
    *(volatile u16 *)0x0400000A = 0x1D0D;
    *(volatile u16 *)0x0400000E = 0x1F0F;
}

void sub_0806C218(void) {

    s32 i;

    if (gTimeline6C218.count != 0) {
        s32 start = gTimeline6C218.target - 0x12;
        if (start < gTimeline6C218.time) {
            s32 end = start + 9;
            if (gTimeline6C218.time < end) {
                gFrameObjects[0x20].commandDelay = end - 1 == gTimeline6C218.time ? 2 : 1;
                gFrameObjects[0x20].commandOffset = gTimeline6C218.lanes[gTimeline6C218.count - 1];
                gFrameObjects[0x20].unknown1A = 0;
            }
        }
    }
    if (gTimeline6C218.target < gTimeline6C218.time) {
        if (gTimeline6C218.count == 0) {
            for (i = 0; i <= 7; i++) {
                if (gFrameObjects[0x28 + i].commandDelay != 0)
                    return;
            }
            sub_08074B88(0);
            sub_08074B88(0xE);
            gUnknown_0300137C = 6;
            return;
        }
        gTimeline6C218.count--;
        sub_0806D398();
        gTimeline6C218.target += sub_0807CD2C(gTimeline6C218.count * gTimeline6C218.count, 0x32) + gTimeline6C218.offset;
        for (i = 0; i <= 7; i++) {
            if (gFrameObjects[0x28 + i].commandDelay == 0) {
                sub_08048864(i + 0x28, 0xC800, 0x10, 2, 3);
                gFrameObjects[0x28 + i].screenX = gFrameObjects[0x20].screenX;
                gFrameObjects[0x28 + i].screenY = 0xC;
                gFrameObjects[0x28 + i].unknown1A = 0;
                gFrameObjects[0x28 + i].commandDelay = 1;
                gFrameObjects[0x28 + i].commandOffset = gTimeline6C218.lanes[gTimeline6C218.count];
                sub_08048864(i + 0x30, 0xCC08, 0x12, 2, 3);
                gFrameObjects[i + 0x30].screenX = gFrameObjects[0x28 + i].screenX;
                gFrameObjects[i + 0x30].screenY = 0x10;
                sub_08074DE0(0x61);
                gFrameObjects[0x1F].screenY = 0xC8;
                break;
            }
        }
    }
    gTimeline6C218.time++;
}

void sub_0806CFEC(void) {

    u16 colors[16];
    u16 timer;

    if (gFrameObjects[0].commandDelay != 1)
        return;
    if (!(7 & (timer = gFrameObjects[0].unknown1A))) {
        if (timer & 0x20) {
            volatile struct Dma6CFEC *dma = (void *)0x040000D4;
            dma->source = 0x05000380;
            dma->destination = (u32)colors;
            dma->control = 0x80000010;
            (void)dma->control;
            dma->source = (u32)&colors[1];
            dma->destination = 0x05000384;
            dma->control = 0x8000000B;
            (void)dma->control;
            dma->source = (u32)&colors[4];
            dma->destination = 0x05000382;
            dma->control = 0x80000001;
            (void)dma->control;
            dma->source = (u32)&colors[8];
            dma->destination = 0x0500038A;
            dma->control = 0x80000001;
            (void)dma->control;
            dma->source = (u32)&colors[12];
            dma->destination = 0x05000392;
            dma->control = 0x80000001;
            (void)dma->control;
        } else {
            volatile struct Dma6CFEC *dma = (void *)0x040000D4;
            dma->source = 0x05000380;
            dma->destination = (u32)colors;
            dma->control = 0x80000010;
            (void)dma->control;
            dma->source = (u32)&colors[2];
            dma->destination = 0x05000382;
            dma->control = 0x8000000B;
            (void)dma->control;
            dma->source = (u32)&colors[1];
            dma->destination = 0x05000388;
            dma->control = 0x80000001;
            (void)dma->control;
            dma->source = (u32)&colors[5];
            dma->destination = 0x05000390;
            dma->control = 0x80000001;
            (void)dma->control;
            dma->source = (u32)&colors[9];
            dma->destination = 0x05000398;
            dma->control = 0x80000001;
            (void)dma->control;
        }
    }
    if (0x10 & gFrameObjects[0].unknown1A)
        gFrameObjects[0x1E].screenY = 0x80 - (gUnknown_08485924[(0xF & gFrameObjects[0].unknown1A) * 4] >> 2);
    gFrameObjects[0x20].frameAndGroup = (8 & gFrameObjects[0].unknown1A) ? 0xE : 0xF;
}

void sub_08073524(struct SoundChannelState *channel, s16 *frequency, u16 *control) {

    u8 note = sub_08074224(channel);

    if (channel->lastNote != note) {
        u8 *type;
        channel->lastNote = note;
        type = &channel->type;
        if (note != 0xFF) {
            s32 sum;
            u16 pitch = sum = sub_080732B8(note) + channel->byte55;
            u8 kind;
            u16 *rate;
            if ((s16)pitch < 0)
                pitch = 0;
            else if ((s16)pitch > 0x7FF)
                pitch = 0x7FF;
            kind = *type;
            rate = &channel->half40;
            if (kind == 2) {
                volatile u16 reset;
                *frequency = gUnknown_083ABBE2[(*rate * 3) >> 12] << 8;
                reset = (4 & *(volatile u16 *)0x04000084) ? 0 : 0x8000;
                *control = pitch | reset;
            } else {
                *frequency = ((*rate * 3) & ~0xFFF) | channel->byte67;
                *control = pitch | 0x8000;
            }
            return;
        }
        if (*type == 2)
            *frequency = 0;
        else
            *frequency = channel->byte67;
        do {
        *control |= 0x8000;
        } while (0);
    }
}
