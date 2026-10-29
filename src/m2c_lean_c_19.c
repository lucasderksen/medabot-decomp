/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "encounter_parts.h"
#include "fresh_helpers.h"
#include "gba.h"
#include "input.h"
#include "post_dispatch.h"
#include "record_helpers.h"
#include "render_work.h"
#include "sound_samples.h"
#include "sound_voice.h"
#include "sprite_layouts.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct DebugWork830C
{
    u8 byte00;
    u8 unknown01[0xF];
    s8 byte10;
    u8 unknown11;
    u8 byte12;
    u8 unknown13;
    u8 selector;
    u8 counter15;
    s8 values[8];
    u16 half1E;
    u8 unknown20[4];
    u16 half24;
    u8 unknown26[8];
    u16 half2E;
    u16 half30;
    u8 byte32;
    s8 byte33;
    s8 byte34;
};
struct Dma830C { const void *source; u32 destination; u32 control; };
struct ContinuedWork830C
{
    u8 unknown000[0xC28];
    u8 byteC28;
    u8 unknownC29[0xC52 - 0xC29];
    u16 halfC52;
    u16 halfC54;
    s8 byteC56;
    s8 byteC57;
    u8 unknownC58[4];
    u8 byteC5C;
};

extern struct ContinuedWork830C gContinuedWork_030057E0;
extern u8 gBlendSetupWork_03006F40[];
extern u8 gFamilyKeyBytes49558_0300058C;

void sub_0805830C(u32 mode);

void sub_0805830C(u32 mode) {

    s32 count;
    const void *const *scripts;

    ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->counter15++;
    switch (mode)
    {
    case 0:
        sub_080589A4(6);
        switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector])
        {
        case 0:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0xC0);
            break;
        case 1:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0x10);
            break;
        case 3:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 4);
            break;
        case 4:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 10);
            break;
        case 2:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 2);
            break;
        case 5:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 2);
            break;
        }
        break;
    case 1:
        sub_080589A4(3);
        switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector])
        {
        case 0:
            sub_08058A10(0, 3000);
            break;
        case 1:
            sub_08058A10(1, 2);
            break;
        case 2:
            sub_08058A10(2, 8);
            break;
        }
        break;
    case 2:
        if (0x40 & *(u8 *)&gRepeatedKeys)
            gContinuedWork_030057E0.halfC54 -= 0x10;
        if (0x80 & *(u8 *)&gRepeatedKeys)
            gContinuedWork_030057E0.halfC54 += 0x10;
        if (0x20 & *(u8 *)&gRepeatedKeys)
            gContinuedWork_030057E0.halfC52 -= 0x10;
        if (0x10 & *(u8 *)&gRepeatedKeys)
            gContinuedWork_030057E0.halfC52 += 0x10;
        gContinuedWork_030057E0.byteC56 = sub_0805273C(gContinuedWork_030057E0.halfC52);
        gContinuedWork_030057E0.byteC57 = sub_08052760(gContinuedWork_030057E0.halfC54);
        sub_08052AA4();
        break;
    case 3:
        if (0x20 & (u8)gRepeatedKeys)
        {
            if (--((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 == 0xFF)
                ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 = 0x1F;
        }
        if (0x10 & (u8)gRepeatedKeys)
        {
            if (++((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 > 0x1F)
                ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 = 0;
        }
        break;
    case 4:
        sub_080589A4(6);
        switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector])
        {
        case 1:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 3);
            break;
        case 2:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 4);
            break;
        case 0:
        case 3:
        case 4:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 2);
            break;
        case 5:
            sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 3);
            break;
        }
        *(volatile u16 *)0x04000052 = ((0x3F & gBlendSetupWork_03006F40[4]) << 8) | (0x3F & gBlendSetupWork_03006F40[3]);
        *(volatile u16 *)0x04000054 = 0x3F & gBlendSetupWork_03006F40[5];
        break;
    case 5:
        sub_08058B90(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0xB0);
        ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte32 = 1;
        break;
    case 6:
        if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte32 != 0)
            break;
        sub_080589A4(3);
        switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector])
        {
        case 0:
            sub_08058AB8(0, 0x11);
            break;
        case 1:
            sub_08058AB8(1, ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half1E);
            break;
        case 2:
            sub_08058AB8(2, 2);
            break;
        }
        if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half2E == 0x10)
            scripts = gContinuedScripts_08411AE0;
        else
            scripts = gStateScriptTables_0847DF24[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half2E];
        count = 0;
        if (*scripts != NULL)
        {
            do
            {
                scripts++;
                count++;
                if (count > 0xFFF)
                    break;
            } while (*scripts != NULL);
        }
        ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half1E = count;
        if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half30 >= (u16)count)
            ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half30 = count - 1;
        break;
    case 7:
        sub_080589A4(5);
        switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector])
        {
        case 0:
            sub_08058B28(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0x20);
            break;
        case 1:
            sub_08058B28(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0x20);
            break;
        case 2:
            sub_08058B28(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0x80);
            break;
        case 3:
            sub_08058B28(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0xA0);
            break;
        case 4:
            sub_08058B28(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector], 0x100);
            break;
        }
        switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->values[((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector])
        {
        case 2:
            if (1 & (u8)gRepeatedKeys)
                sub_08047BB4(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte33);
            break;
        case 1:
            break;
        case 3:
            if (1 & (u8)gRepeatedKeys)
                sub_08047BA8(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte34);
            break;
        }
        break;
    }
    if (4 & gFamilyKeyBytes49558_0300058C)
    {
        if (++((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector > 7)
            ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector = 0;
        sub_08059560();
        sub_0805821C(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector);
    }
    if (2 & (u8)gRepeatedKeys)
        sub_08059578();
    if (!(1 & (u8)gRepeatedKeys))
        return;
    switch (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector)
    {
    case 3:
        ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte10 = 0;
        sub_08059560();
        sub_080533E4(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12, gContinuedWork_030057E0.halfC52, gContinuedWork_030057E0.halfC54, 0);
        if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 == 0xE)
            gContinuedWork_030057E0.byteC5C = 0xC;
        else if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 == 0x12)
            gContinuedWork_030057E0.byteC5C = 0xB;
        if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 == 0xE || ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte12 == 0x12)
        {
            sub_08048288();
            ((volatile struct Dma830C *)0x040000D4)->source = gPaletteSourcePointers_083F83C0[gFreshBytes_083D2B26[gContinuedWork_030057E0.byteC5C]];
            ((volatile struct Dma830C *)0x040000D4)->destination = 0x05000200;
            ((volatile struct Dma830C *)0x040000D4)->control = 0x84000008;
            ((volatile struct Dma830C *)0x040000D4)->control;
            gContinuedWork_030057E0.byteC28 = gContinuedWork_030057E0.byteC5C;
            sub_0805330C();
        }
        gUnknown_0300137C++;
        break;
    case 4:
        sub_08074DE0(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte00);
        break;
    case 6:
        if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte32 == 0)
        {
            if (((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half24 != 0)
            {
                s32 next = ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half30 + 1;
                ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half30 = next;
                if ((u16)next >= ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half1E)
                {
                    ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half30 = 0;
                    if (++((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half2E > 0x10)
                        ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->half2E = 0;
                }
            }
            ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->counter15 = 0;
            sub_08058C0C(((struct DebugWork830C *)gContinuedOtherWork_030057A0)->selector);
            sub_08047C00();
            ((struct DebugWork830C *)gContinuedOtherWork_030057A0)->byte32++;
        }
        break;
    case 0:
    case 1:
    case 2:
    case 5:
        break;
    }
}
