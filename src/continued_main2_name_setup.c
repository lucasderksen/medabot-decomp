#include "global.h"
#include "gba.h"
#include "frame.h"
#include "frame_objects.h"
#include "object_helpers.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_inventory.h"
#include "state0_display.h"
#include "continued_commands.h"


/* Observed fields and physical backing only; original/full layouts unknown. */
struct NameContext
{
    u8 unknown00[0xF];
    u8 byte0F;
    u8 unknown10[0x48];
    u8 bytes58[16];
    u8 bytes68[16];
};
struct NamePhase { u8 unknown00[0x84]; u8 byte84; };
#define NAME_CONTEXT ((struct NameContext *)gMainContextPointer_03006F74)
#define NAME_PHASE ((struct NamePhase *)gUnknown_03000440)
#define DISPLAY_CONTROL (*(volatile u16 *)0x04000000)

void sub_0805E718(void)
{
    s8 index;
    s32 x;
    DISPLAY_CONTROL |= 0x200;
    DISPLAY_CONTROL |= 0x400;
    DISPLAY_CONTROL |= 0x800;
    DISPLAY_CONTROL |= 0x1000;
    for (index = 0; index <= 15; index++)
        NAME_CONTEXT->bytes58[index] = 0xFE;
    sub_08040D0C(5, 10);
    switch (*(u8 *)0x03000584)
    {
    case 0:
        for (index = 0; index <= 15; index++)
        {
            NAME_CONTEXT->bytes58[index] = gMain2SaveNamePointers_084836FC[0][index];
            if (NAME_CONTEXT->bytes58[index] == 0xFE)
                break;
        }
        NAME_CONTEXT->byte0F = index;
        break;
    case 1:
        {
            u32 identifier = gInventoryRecords[gQuantityResult_030017EC].byte1;
            if (identifier <= 1)
            {
                for (index = 0; index <= 15; index++)
                {
                    NAME_CONTEXT->bytes58[index] = ((const u8 *)gUnknownPointers_083B6590[identifier + 32])[index];
                    if (NAME_CONTEXT->bytes58[index] == 0xFE)
                        break;
                }
            }
            else
            {
                for (index = 0; index <= 15; index++)
                {
                    NAME_CONTEXT->bytes58[index] = ((const u8 *)gUnknownPointers_083B6590[identifier])[index];
                    if (NAME_CONTEXT->bytes58[index] == 0xFE)
                        break;
                }
            }
            NAME_CONTEXT->byte0F = index;
        }
        break;
    case 2:
        for (index = 0; index <= 15; index++)
        {
            NAME_CONTEXT->bytes58[index] = gInventoryNames[gQuantityResult_030017EC][index];
            if (NAME_CONTEXT->bytes58[index] == 0xFE)
                break;
        }
        NAME_CONTEXT->byte0F = index;
        break;
    }
    CpuSet(NAME_CONTEXT->bytes58, NAME_CONTEXT->bytes68, 8);
    gFrameObjects[4].screenX = sub_0805E300(NAME_CONTEXT->bytes58) + 40;
    gFrameObjects[4].screenY = 27;
    sub_08040DB8(NAME_CONTEXT->bytes58, 5, 5, 3, 10, 13, 1, 0);
    x = gFrameObjects[4].screenX + 2;
    index = NAME_CONTEXT->byte0F;
    if (index <= 9)
    {
        u32 backing = (u32)gFrameObjects;
        u32 zero = 0;
        const u8 *metrics = gGlyphMetrics_083B4E08;
        for (; index <= 9; index++)
        {
            struct FrameObject *object = (struct FrameObject *)(((s32)index + 5) * 64 + backing);

        object->flags = 0xC000;
        object->tableSelector = zero;
        object->palette = 13;
        object->frameAndGroup = 66;
        object->screenX = x;
        object->screenY = 28;
        object->priority = 255;
        x += metrics[0x86];
        }
    }
    CpuFastSet(gMain2NameTransfer_08483534, (void *)0x0202FA20, 8);
    CpuFastSet(gUnknownWords_084E43F8, (void *)0x0202F9C0, 8);
    CpuFastSet(gMain2NameTransfer_084E43D8, (void *)0x0202F9A0, 8);
    CpuFastSet(gMain2NameTransfer_080AF988, (void *)0x0202F800, 8);
    CpuFastSet(gMain2NameTransfer_0879461C, (void *)0x0202FA00, 128);
    NAME_PHASE->byte84 = 0;
    gUnknown_0300137C++;
}
