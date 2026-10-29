#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"
#include "state0_display.h"


void sub_08011078(void)
{
    u8 *work;
    u8 *selected;
    sub_08012098();
    sub_08043CD4();
    work = gState0TransferWork.bytes;
    selected = work + 0x186;
    if (*selected == 3)
    {
        *selected = 0;
        gUnknown_0300137C = 71;
    }
    else
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *identifiers = work + 0x16E;
        if (identifiers[scaled])
        {
            const void *const *names;
            sub_0803FB0C();
            names = gUnknownPointers_083B6590;
            {
                u32 identifier = identifiers[*selected * 8];
                identifier--;
                sub_0803F63C(names[identifier], gDebugMenuTextBuffer, 11);
            }
            sub_08074B88(16);
            gUnknown_0300137C++;
        }
        else
            (*selected)++;
    }
}

void sub_080110FC(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[119]))
        gUnknown_0300137C++;
}

void sub_0801112C(void)
{
    sub_08012098();
    sub_08043CD4();
    gState0TransferWork.bytes[0x186]++;
    gUnknown_0300137C = 67;
}

void sub_08011158(void)
{
    u8 *work;
    u8 *selected;
    sub_08012098();
    sub_08043CD4();
    work = gState0TransferWork.bytes;
    selected = work + 0x186;
    if (*selected == 3)
    {
        *selected = 0;
        gUnknown_0300137C = 75;
    }
    else
    {
        u32 index = *selected;
        u32 scaled = index * 8;
        u8 *items = work + 0x174;
        if (items[scaled])
        {
            const void *const *names;
            const void *source;
            u8 *buffer;
            sub_0803FB0C();
            names = gUnknownPointers_083B6590;
            {
                u32 index = *selected;
                u32 scaled = index * 8;
                u8 *identifiers = work + 0x16E;
                u32 identifier = identifiers[scaled];
                identifier--;
                source = names[identifier];
            }
            buffer = gDebugMenuTextBuffer;
            sub_0803F63C(source, buffer, 11);
            names = gUnknownPointers_083B74B8;
            {
                u32 index = *selected;
                u32 scaled = index * 8;
                u8 *parts = work + 0x175;
                sub_0803F63C(names[parts[scaled]], buffer + 20, 17);
            }
            sub_08074B88(16);
            gUnknown_0300137C++;
        }
        else
            (*selected)++;
    }
}

void sub_0801120C(void)
{
    sub_08012098();
    sub_08043CD4();
    if (sub_0803FB3C(gState0FixedMessages_083C6744[120]))
        gUnknown_0300137C++;
}

void sub_0801123C(void)
{
    sub_08012098();
    sub_08043CD4();
    gState0TransferWork.bytes[0x186]++;
    gUnknown_0300137C = 71;
}
