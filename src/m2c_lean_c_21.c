/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "main.h"
#include "main_callbacks.h"
#include "object_numeric_helpers.h"
#include "record_helpers.h"
#include "serial.h"
#include "sound_voice.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct DmaRegs68460 { u32 source, destination, control; };
struct DmaRegs68684 { u32 source, destination, control; };
struct BattleView6C3A0 { u8 pad00[0xE]; u8 byte0E; u8 pad0F[0x32]; s8 value41; };

extern const s8 gUnknown_08485924[];
extern const u8 gRandomBytes_083F7D80[];
extern s16 gUnknown_03003474;
extern s32 gTransferStep03000000;
extern s32 sub_08068CC8(void);
extern s32 sub_0807CDF8(s32, s32);
extern struct BattleView6C3A0 gBattleView6C3A0 asm("gCounter6ED08_03001800");
extern struct FrameObject gFrameObjectsB[] asm("gFrameObjects");
extern u16 *gUnknown_0300002C;
extern u16 gCopy6280C0202F800[];
extern u16 gTransferOffsets03000008[];
extern u16 gUnknown_03000028;
extern u8 gTransferDivisor03000005;
extern u8 gUnknown_03000004;
extern void sub_0806B718(u8);

void sub_08068460(u8 mode, u8 divisor, u16 color);
void sub_08068684(u8 mode, u8 divisor, u16 color);
void sub_0806C3A0(void);

void sub_08068460(u8 mode, u8 divisor, u16 color) {

    u8 tiles[0x80];
    u16 map[0x280];
    u16 palette[0x200];
    s32 i;
    s32 k;
    u32 *frame;
    u16 *p;
    u32 a, b, c, d;

    gTransferStep03000000 = 0;
    gUnknown_03000028 = color;
    gUnknown_03000004 = mode;
    gTransferDivisor03000005 = divisor;
    if (divisor == 0)
        gTransferDivisor03000005 = 1;
    switch (mode) {
    case 1:
        *(volatile u16 *)0x04000050 = 0xBF;
        *(volatile u16 *)0x04000054 = 0x10;
        break;
    case 2:
        *(volatile u16 *)0x04000050 = 0xFF;
        *(volatile u16 *)0x04000054 = 0x10;
        break;
    case 3:
        for (i = 0; i <= 0x7F; i++)
            tiles[i] = 0x11;
        {
            volatile struct DmaRegs68460 *dma = (void *)0x040000D4;
            dma->source = (u32)tiles;
            dma->destination = 0x0600FF80;
            dma->control = 0x80000040;
            (void)dma->control;
        }
        for (i = 0; i <= 0x27F; i++) {
            u16 m;
            map[i] = m = gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF];
            map[i] = (m & 3) + 0xF1FC;
        }
        {
            volatile struct DmaRegs68460 *dma = (void *)0x040000D4;
            dma->source = (u32)map;
            dma->destination = 0x0600F800;
            dma->control = 0x84000140;
            (void)dma->control;
            dma->source = (u32)&gUnknown_03000028;
            dma->destination = 0x050001E2;
            dma->control = 0x80000001;
            (void)dma->control;
        }
        *(volatile u16 *)0x04000008 = 0x1F0C;
        *(volatile u16 *)0x04000000 |= 0x100;
        *(volatile u16 *)0x04000054 = 0;
        i = 0;
        {
            u16 *q = (u16 *)0x03000008;
            d = 0x3F92;
            c = 0x3F90;
            b = 0x3F82;
            a = 0x3F80;
        offs:
            q[0] = a;
            q[1] = b;
            q[2] = c;
            q[3] = d;
            q += 4;
            d += 0x20;
            c += 0x20;
            b += 0x20;
            a += 0x20;
            i++;
            if (i <= 3)
                goto offs;
        }
        for (i = 0; i <= 14; i++) {
            s32 j;
            u16 t;
            j = gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF] % (0x10 - i) + i;
            p = (u16 *)0x03000008;
            t = p[i];
            p[i] = p[j];
            p[j] = t;
        }
        break;
    case 4:
        gUnknown_0300002C = gCopy6280C0202F800;
        {
            volatile struct DmaRegs68460 *dma = (void *)0x040000D4;
            dma->source = 0x05000000;
            dma->destination = (u32)gCopy6280C0202F800;
            dma->control = 0x80000200;
            (void)dma->control;
        }
        for (i = 0; i < 0x200; i++)
            palette[i] = color;
        {
            volatile struct DmaRegs68460 *dma = (void *)0x040000D4;
            dma->source = (u32)palette;
            dma->destination = 0x05000000;
            dma->control = 0x84000100;
            (void)dma->control;
        }
        break;
    }
}

void sub_08068684(u8 mode, u8 divisor, u16 color) {

    u8 tiles[0x80];
    u16 map[0x280];
    s32 i;
    s32 k;
    u32 *frame;
    u16 *p;
    u32 a, b, c, d;

    gTransferStep03000000 = divisor;
    gUnknown_03000028 = color;
    gUnknown_03000004 = mode;
    gTransferDivisor03000005 = divisor;
    if (divisor == 0)
        gTransferDivisor03000005 = 1;
    switch (mode) {
    case 1:
        *(volatile u16 *)0x04000050 = 0xBF;
        break;
    case 2:
        *(volatile u16 *)0x04000050 = 0xFF;
        break;
    case 3:
        for (i = 0; i <= 0x7F; i++)
            tiles[i] = 0x11;
        {
            volatile struct DmaRegs68684 *dma = (void *)0x040000D4;
            dma->source = (u32)tiles;
            dma->destination = 0x0600FF80;
            dma->control = 0x80000040;
            (void)dma->control;
        }
        for (i = 0; i <= 0x27F; i++) {
            u16 m;
            map[i] = m = gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF];
            map[i] = (m & 3) + 0xF1FC;
        }
        {
            volatile struct DmaRegs68684 *dma = (void *)0x040000D4;
            dma->source = (u32)map;
            dma->destination = 0x0600F800;
            dma->control = 0x84000140;
            (void)dma->control;
            dma->source = (u32)&gUnknown_03000028;
            dma->destination = 0x050001E2;
            dma->control = 0x80000001;
            (void)dma->control;
        }
        *(volatile u16 *)0x04000008 = 0x1F0C;
        *(volatile u16 *)0x04000000 |= 0x100;
        i = 0;
        {
            u16 *q = (u16 *)0x03000008;
            d = 0x3F92;
            c = 0x3F90;
            b = 0x3F82;
            a = 0x3F80;
        offs:
            q[0] = a;
            q[1] = b;
            q[2] = c;
            q[3] = d;
            q += 4;
            d += 0x20;
            c += 0x20;
            b += 0x20;
            a += 0x20;
            i++;
            if (i <= 3)
                goto offs;
        }
        for (i = 0; i <= 14; i++) {
            s32 j;
            u16 t;
            j = gRandomBytes_083F7D80[(gFrameCounter + i) & 0xFF] % (0x10 - i) + i;
            p = (u16 *)0x03000008;
            t = p[i];
            p[i] = p[j];
            p[j] = t;
        }
        break;
    case 4:
        gUnknown_0300002C = gCopy6280C0202F800;
        {
            volatile struct DmaRegs68684 *dma = (void *)0x040000D4;
            dma->source = 0x05000000;
            dma->destination = (u32)gCopy6280C0202F800;
            dma->control = 0x80000200;
            (void)dma->control;
        }
        sub_08068CC8();
        break;
    }
}

void sub_0806C3A0(void) {

    s32 i, j;
    struct FrameObject *obj;
    u32 k;
    u8 delay;
    u8 found;
    s32 phase;
    s32 x;
    struct FrameObject *root;
    struct FrameObject *other;

    for (i = 0, root = gFrameObjects; i <= 7; i++) {
        delay = gFrameObjects[0x28 + i].commandDelay;
        switch (delay) {
        case 1:
        {
            x = (gFrameObjects[0x28 + i].commandOffset - 1) * ((gFrameObjects[0x28 + i].unknown1A >> 2) + 0x18) + 0x78;
            gFrameObjects[0x28 + i].screenX = x;
            gFrameObjects[0x28 + i].screenY = gFrameObjects[0x28 + i].unknown1A * 2 + 0xC;
            other = (struct FrameObject *)(((i + 0x30) << 6) + (u32)root);
            other->screenX = x;
            other->screenY = gFrameObjects[0x28 + i].screenY + 4;
            if (gFrameObjects[0x28 + i].unknown1A <= 0x38)
                goto next;
            if (gFrameObjects[0x28 + i].unknown1A > 0x3F) {
                gFrameObjects[0x28 + i].commandDelay = 3;
                gFrameObjects[0x28 + i].unknown1A = 0;
                gFrameObjects[0x28 + i].screenY = 0x90;
                other->screenY = 0xC8;
                if (gFrameObjects[0x1E].commandOffset == 0) {
                    gFrameObjects[0x1E].commandOffset = delay;
                    gFrameObjects[0x1E].unknown1A = 0;
                    if ((u8)(gBattleView6C3A0.value41 / 5) == 0)
                        gFrameObjects[0x1E].commandStopped = gFrameObjects[0x28 + i].commandOffset != 2;
                    else
                        gFrameObjects[0x1E].commandStopped = gBattleView6C3A0.value41 > 0;
                    gFrameObjects[0x13].commandDelay = 0;
                    gFrameObjects[0x13].commandOffset = 0;
                    gFrameObjects[0x13].screenY = 0xC8;
                    gFrameObjects[0x13].unknown1A = 0;
                    sub_08048864(0x21, 0xCC08, 0x12, 2, 3);
                    gFrameObjects[0x21].screenX = gFrameObjects[0x1E].screenX;
                    gFrameObjects[0x21].screenY = gFrameObjects[0x1E].screenY + 0xC;
                }
                sub_08074DE0(0x3B);
                goto next;
            }
            found = gFrameObjects[0x1E].commandOffset;
            if (found != 0)
                goto next;
            phase = (s8)(gBattleView6C3A0.value41 / 5) + 1;
            if (phase != gFrameObjects[0x28 + i].commandOffset)
                goto next;
            if ((u8)phase == 1)
                gFrameObjects[0x28 + i].commandOffset = 2 & gBattleView6C3A0.byte0E;
            gFrameObjects[0x28 + i].commandDelay = 2;
            sub_08048864(0x38, 0xC400, 0x17, 4, 3);
            gFrameObjects[0x38].screenX = gFrameObjects[0x28 + i].screenX;
            gFrameObjects[0x38].screenY = gFrameObjects[0x28 + i].screenY - gUnknown_08485924[0x3F & gFrameObjects[0x28 + i].unknown1A];
            gFrameObjects[0x38].commandDelay = delay;
            gFrameObjects[0x38].unknown1A = found;
            gFrameObjects[0x13].commandDelay = 0;
            sub_08074DE0(0x68);
            goto next;
        }
        case 2:
            if (gFrameObjects[0x28 + i].commandOffset == 0)
                gFrameObjects[0x28 + i].screenX -= 4;
            else
                gFrameObjects[0x28 + i].screenX += 4;
            gFrameObjects[0x28 + i].screenY = gFrameObjects[0x28 + i].unknown1A * 2 + 0xC;
            gFrameObjects[0x30 + i].screenX = gFrameObjects[0x28 + i].screenX;
            gFrameObjects[0x30 + i].screenY = gFrameObjects[0x28 + i].screenY + 4;
            if (gFrameObjects[0x28 + i].unknown1A <= 0x27) {
                gFrameObjects[0x28 + i].commandOffset = 0;
                gFrameObjects[0x28 + i].commandDelay = 0;
                gFrameObjects[0x28 + i].screenY = 0xC8;
                gFrameObjects[0x30 + i].screenY = 0xC8;
            }
            gFrameObjects[0x28 + i].unknown1A--;
            break;
        case 0:
        default:
            break;
        case 3:
            if (gFrameObjects[0x28 + i].unknown1A == 0)
                sub_08048864(j = i + 0x28, 0xC400, 0x13, 3, delay);
            else if (gFrameObjects[0x28 + i].unknown1A > 0xF)
                sub_0806B718(j = i + 0x28);
        next:
            gFrameObjects[0x28 + i].unknown1A++;
            root = gFrameObjectsB;
            break;
        }
    }
}
