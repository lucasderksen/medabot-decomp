/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "bios_lz77_streams.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "frame_objects.h"
#include "gba.h"
#include "graphics.h"
#include "link_menu.h"
#include "main_callbacks.h"
#include "native_le_streams.h"
#include "object_helpers.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "state0_callbacks.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Main2MedalContext
{
    u8 unknown00[0x36];
    u16 tileBase36;
    u8 unknown38[2];
    s16 timer3A;
    u8 unknown3C[4];
    u16 saved40[4];
    u8 unknown48[8];
    u8 blend50[0x2A];
    s8 byte7A;
    u8 unknown7B[0x1B5];
    u8 sortCopy230[1];
    u8 medal231;
    u8 unknown232[3];
    u8 value235;
    u8 unknown236[2];
    u8 byte238;
    u8 unknown239;
    u8 text23A[1];
};

extern const u8 *const gDebugMedalMetadata_083B6590[];
extern const u8 gUnknown_084E4438[];
extern const u8 gUnknown_0850F318[];
extern const u8 gUnknown_0879F6CC[];
extern s32 sub_08074CE0(void);
extern s32 sub_0807CD2C(s32, s32);
extern s32 sub_0807CDF8(s32, s32);
extern u8 gObjectSortBytes[] asm("gObjectSortEntries");
extern u8 gUnknown_0202F9A0[];
extern void sub_08062C28(u32, u32);
extern void sub_08062D60(void);

void sub_080639C4(void);

void sub_080639C4(void) {

    u32 zero;
    u32 length;
    u32 medal;
    u32 tileBase;
    u32 i;
    s32 k;
    u8 *dst;
    u8 *src;
    volatile u16 *bg1;
    struct Main2MedalContext *ctx;
    s32 value;
    u32 tile;
    u32 cell;
    u32 cell2;
    u32 shifted;
    u32 offset;

    src = gObjectSortBytes;
    dst = ((struct Main2MedalContext *)gMainContextPointer_03006F74)->sortCopy230;
    for (i = 0; i <= 0x3F; i++)
        *dst++ = *src++;
    if (sub_08074CE0() != 0x18)
        sub_08074B88(0x18);
    zero = 0;
    CpuFastSet(&zero, (void *)0x06000000, 0x01006000);
    sub_080415BC();
    sub_08040CD0(0, 0x80);
    *(volatile u16 *)0x04000000 = 0x60;
    *(volatile u16 *)0x04000050 = 0x2FF;
    *(volatile u16 *)0x04000054 = 0x10;
    bg1 = (volatile u16 *)0x0400000A;
    *bg1 = 0x1E05;
    *(volatile u16 *)0x0400000C = 0x1B06;
    *(volatile u16 *)0x0400000E = 0x3C07;
    sub_0805BA34(gBiosLz77Stream_087A0FB4, *bg1);
    sub_0805BA34(gBiosLz77Stream_087A0D04, *(volatile u16 *)0x0400000C);
    sub_0805BA34(gBiosLz77Stream_087A1244, *(volatile u16 *)0x0400000E);
    *(volatile u16 *)0x0400000C = 0x1D06;
    sub_0805BA34(gBiosLz77Stream_087A10F0, *(volatile u16 *)0x0400000C);
    length = sub_08044D0C(gBiosLz77Stream_0879F80C, (void *)0x02030000);
    CpuSet((void *)0x02030000, (void *)0x06004000, (length << 10) >> 11);
    LeDecompress(gNativeLeStream_08785EC0, (void *)(length + 0x06004000));
    ((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 = (length >> 5) + 4;
    LeDecompress(gNativeLeStream_084C3A24, (void *)(length + 0x06004080));
    CpuFastSet(gUnknown_0879F6CC, (void *)0x05000000, 0x50);
    CpuFastSet(gUnknown_0850F318, (void *)0x050003A0, 8);
    CpuFastSet(gUnknown_0850F318, gUnknown_0202F9A0, 8);
    CpuFastSet(gUnknown_084E4438, (void *)0x05000200, 8);
    CpuFastSet(gUnknown_0850F318 - 0x20, (void *)0x05000220, 8);
    CpuFastSet(gUnknown_0850F318 - 0x60, (void *)0x05000240, 8);
    LeDecompress(gNativeLeStream_084C8034, (void *)0x06017400);
    ctx = ((struct Main2MedalContext *)gMainContextPointer_03006F74);
    ctx->timer3A = 0x280;
    if (ctx->byte7A == 0)
    {
        cell2 = 0x06000246;
        medal = ctx->medal231;
        sub_08062C28(medal, ctx->byte238);
        sub_08040DB8(((struct Main2MedalContext *)gMainContextPointer_03006F74)->text23A, 0x20, 4, 4, 10, 2, 0, 1);
        for (k = 0; k <= 9; k++)
        {
            tileBase = length >> 5;
            gDebugMenuTextBuffer[k] = gDebugMedalMetadata_083B6590[medal][k];
        }
        sub_08040DB8(gDebugMenuTextBuffer, 0x10, 5, 8, 10, 1, 1, 1);
        value = ((struct Main2MedalContext *)gMainContextPointer_03006F74)->value235;
        if (value == 100)
        {
            *(u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x0600021A) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + 0x14) | 0x7000;
            *(u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x0600025A) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + 0x15) | 0x7000;
            *(u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x0600021C) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + 0x16) | 0x7000;
            *(u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x0600025C) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + 0x17) | 0x7000;
        }
        else
        {
            volatile u16 *reg = (volatile u16 *)0x0400000A;
            *(u16 *)((((*reg >> 8) & 0x1F) << 11) + 0x0600021A) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + value / 10 * 2) | 0x7000;
            *(u16 *)((((*reg >> 8) & 0x1F) << 11) + 0x0600025A) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + value / 10 * 2 + 1) | 0x7000;
            *(u16 *)((((*reg >> 8) & 0x1F) << 11) + 0x0600021C) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + value % 10 * 2) | 0x7000;
            *(u16 *)((((*reg >> 8) & 0x1F) << 11) + 0x0600025C) = (((struct Main2MedalContext *)gMainContextPointer_03006F74)->tileBase36 + value % 10 * 2 + 1) | 0x7000;
        }
        CpuSet(gUnknownBytes_084C29D8 + (medal << 7), (void *)(length + 0x06004000), 0x40);
        shifted = tileBase << 16;
        tile = 0x60000000;
        tile |= shifted;
        tile >>= 16;
        offset = ((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11;
        cell = 0x06000206;
        {
        u16 *d;
        d = (u16 *)(offset + cell); *d = tile;
        d = (u16 *)(offset + (cell + 2)); *d = tile + 1;
        d = (u16 *)(offset + cell2); *d = tile + 2;
        d = (u16 *)(offset + 0x06000248); *d = tile + 3;
        }
    }
    else
    {
        ctx->saved40[0] = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000218);
        ctx->saved40[1] = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x0600021A);
        ctx->saved40[2] = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000258);
        ctx->saved40[3] = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x0600025A);
        *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000218) = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000216);
        *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x0600021A) = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000216);
        *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000258) = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000256);
        *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x0600025A) = *(u16 *)((((*(volatile u16 *)0x0400000C >> 8) & 0x1F) << 11) + 0x06000256);
    }
    sub_08062D60();
    sub_080656DC(((struct Main2MedalContext *)gMainContextPointer_03006F74)->blend50, 0x10, 0, -1, 0xC0);
    *(volatile u16 *)0x04000000 |= 0x200;
    *(volatile u16 *)0x04000000 |= 0x400;
    *(volatile u16 *)0x04000000 |= 0x800;
    *(volatile u16 *)0x04000000 |= 0x1000;
    gUnknown_0300137C++;
}
