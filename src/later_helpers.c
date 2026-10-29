

#include "state0_display.h"

void sub_08047414(struct RecordDisplayWork *work, struct RenderWork *render, const void *source, void *data)
{
    work->render = render;
    work->source = source;
    work->data = data;
    render->byte1094 = 0;
}

void sub_08047570(void)
{
}

extern u8 gLaterBuffer_03005310[];
extern u8 gLaterBuffer_030057A0[];
extern u8 gLaterBuffer_03006D14[];
extern u8 gLaterBuffer_030057DC[];
extern u8 gLaterBuffer_0300534C[];
extern u8 gLaterBuffer_030055A0[];
extern u8 gLaterBuffer_03006D40[];
extern u8 gLaterBuffer_03006F40[];
extern u8 gLaterBuffer_03006D38[];
extern u8 gLaterBuffer_03006D20[];
extern u8 gLaterBuffer_030057D8[];
extern u8 gLaterBuffer_03005590[];
extern u8 gLaterBuffer_03005350[];
extern u8 gLaterBuffer_03006D30[];
extern u8 gLaterBuffer_030064A0[];
extern void sub_08049714(void *destination, u32 length);

void sub_08047574(void)
{
    sub_08049714(gLaterBuffer_03005310, 60);
    sub_08049714(gLaterBuffer_030057A0, 56);
    sub_08049714(gLaterBuffer_03006D14, 4);
    sub_08049714(gLaterBuffer_030057DC, 4);
    sub_08049714(gLaterBuffer_0300534C, 4);
    sub_08049714(gLaterBuffer_030055A0, 512);
    sub_08049714(gLaterBuffer_03006D40, 512);
    sub_08049714(gLaterBuffer_03006F40, 52);
    sub_08049714(gLaterBuffer_03006D38, 8);
    sub_08049714(gLaterBuffer_03006D20, 16);
    sub_08049714(gLaterBuffer_030057D8, 4);
    sub_08049714(gLaterBuffer_03005590, 4);
    sub_08049714(gLaterBuffer_03005350, 576);
    sub_08049714(gLaterBuffer_03006D30, 4);
    sub_08049714(gLaterBuffer_030064A0, 0x874);
}


#include "state0_display.h"

struct LaterRecord48
{
    u8 unknown00[44];
    u32 flags;
};
extern u8 *gUnknownPointer_03005308;

void sub_08047204(void)
{
    u8 **base = &gUnknownPointer_03005308;
    u32 pending = 2;
    u32 offset = 0;
    s32 remaining = 1;
    do
    {
        struct LaterRecord48 *record = (struct LaterRecord48 *)((u8 *)(offset + (u32)*base));
        u32 flags = record->flags;
        if (flags & 1)
            record->flags = (flags & ~1) | pending;
        else if (!(flags & pending))
        {
            if (flags & 8)
            {
                if (flags & 4)
                    record->flags = flags & ~4;
            }
        }
        offset += 48;
        remaining--;
    } while (remaining >= 0);
}



#include "later_helpers.h"
#include "state0_display.h"
#include "record_helpers.h"

extern const u32 gLaterCommands_0807EE70[][4];
extern const u32 gLaterCommands_0807F610[][4];
extern const u32 gLaterCommands_0807FDB0[][4];
extern const u32 gLaterCommands_08080550[][8];

void sub_0804725C(void *unused, struct RecordDisplayWork *work, s32 mode, u32 index, u32 unused4, u32 palette, u32 bank, u32 enabled)
{
    u16 tileBase;
    u32 offset = 0;

    if (bank == 2)
        offset = 352;
    switch (mode)
    {
    case 0:
    {
        const struct RecordAssetSet *const *sets;
        tileBase = 320 + offset;
        sets = work->source;
        sub_08045E6C(sets, gLaterCommands_0807EE70[index], gLaterCommands_0807EE70[index][0] << 26 >> 26, (u8)palette, work->data, &tileBase, enabled);
        break;
    }
    case 1:
    {
        const struct RecordAssetSet *const *sets;
        const u32 *commands;
        u32 commandIndex;
        tileBase = 416 + offset;
        sets = work->source;
        commands = gLaterCommands_0807F610[index];
        sub_08045E6C(sets, gLaterCommands_0807F610[index], gLaterCommands_0807F610[index][0] << 26 >> 26, (u8)palette, work->data, &tileBase, enabled);
        if (enabled)
        {
            commandIndex = index * 16;
            if (((u32)*(const u8 *)commands << 26) != 0)
            {
                const u32 *cursor = commands;
                u32 cursorOffset = commandIndex;
                do
                {
                if (!(((const u8 *)cursor)[1] >> 7))
                    sub_08046034(work->source, work->data, gLaterCommands_0807FDB0[index], ((u32)*(const u8 *)(const void *)(cursorOffset + (u32)gLaterCommands_0807FDB0) << 26 >> 26), ((u32)*(const u8 *)cursor << 26 >> 26));
                cursor++;
                cursorOffset += 4;
            } while (((u32)*(const u8 *)cursor << 26) != 0);
            }
        }
        break;
    }
    case 2:
    {
        const struct RecordAssetSet *const *sets;
        const u32 *commands;
        u32 commandIndex;
        tileBase = 480 + offset;
        sets = work->source;
        commands = gLaterCommands_0807FDB0[index];
        sub_08045E6C(sets, gLaterCommands_0807FDB0[index], gLaterCommands_0807FDB0[index][0] << 26 >> 26, (u8)palette, work->data, &tileBase, enabled);
        if (enabled)
        {
            commandIndex = index * 16;
            if (((u32)*(const u8 *)commands << 26) != 0)
            {
                const u32 *cursor = commands;
                u32 cursorOffset = commandIndex;
                do
                {
                if (!(((const u8 *)cursor)[1] >> 7))
                    sub_08046034(work->source, work->data, gLaterCommands_0807F610[index], ((u32)*(const u8 *)(const void *)(cursorOffset + (u32)gLaterCommands_0807F610) << 26 >> 26), ((u32)*(const u8 *)cursor << 26 >> 26));
                cursor++;
                cursorOffset += 4;
            } while (((u32)*(const u8 *)cursor << 26) != 0);
            }
        }
        break;
    }
    case 3:
    {
        const struct RecordAssetSet *const *sets;
        tileBase = 544 + offset;
        sets = work->source;
        sub_08045E6C(sets, gLaterCommands_08080550[index], gLaterCommands_08080550[index][0] << 26 >> 26, (u8)palette, work->data, &tileBase, enabled);
        break;
    }
    }
}
