#include "continued_commands.h"
#include "frame.h"
#include "fresh_helpers.h"
#include "continued_graphics.h"
#include "later_graphics.h"

void sub_08052204(void);
void sub_0804B1B0(void);
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03005310[];
extern u8 gLaterBuffer_03006D40[];
extern u32 gUnknown_0300137C;
extern void (*const gFrameCallbacks_083D212C[])(void);
struct ContinuedSettings { u32 unknown00, counter; };
extern struct ContinuedSettings gContinuedSettings_03005310;

void sub_0804A220(void)
{
    u32 address;
    u32 offset;
    s32 index;
    const s16 *matrix;
    struct OamEntry *oam;
    gContinuedSettings_03005310.counter++;
    address = (u32)gUnknown_030057E0;
    offset = 0xC88;
    if (*(u8 *)(address + offset))
    {
        offset++;
        if (*(u8 *)(address + offset))
            sub_0804DC0C();
        else
            sub_0804B6F4();
        {
            u32 nextAddress = (u32)gUnknown_030057E0;
            u32 nextOffset = 0xC5F;
            if (*(u8 *)(nextAddress + nextOffset))
                gFrameCallbacks_083D212C[gUnknown_0300137C]();
        }
    }
    else
        gFrameCallbacks_083D212C[gUnknown_0300137C]();
    sub_08052784();
    sub_08052204();
    sub_08048174();
    for (index = 0; index < 32; index++)
        sub_08049374((u8)index);
    sub_0804B1B0();
    {
    u32 matrixAddress = (u32)gLaterBuffer_03006D40;
    s32 remaining;
    matrixAddress += 6;
    matrix = (const s16 *)matrixAddress;
    oam = gOamShadow;
    for (remaining = 31; remaining >= 0; remaining--)
    {
        oam[0].affine = matrix[0];
        oam[1].affine = matrix[1];
        oam[2].affine = matrix[2];
        oam[3].affine = matrix[3];
        matrix += 8;
        oam += 4;
    }
    }
}
