

#include "state0_inventory_numbers.h"
#include "state0_inventory_view.h"
#include "state0_inventory_view.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "state0_inventory.h"
#include "display_helpers.h"
#include "graphics.h"
#include "frame.h"
#include "main.h"
#include "input.h"

extern const u8 gUnknownBytes_083B7F8C[];
extern const u8 *const gUnknownPointers_083B803C[];
void sub_0800AA1C(void);
void sub_0800AAC0(void);
void sub_0800AB0C(void);
void sub_0800ABA4(void);
void sub_0800AC2C(void);
void sub_0800AED0(void);
void sub_0800AF0C(void);
void sub_0800AF64(void);

extern u8 gState0Page;
void sub_0800AFF8(void);
void sub_0800B0F8(void);
void sub_0800B174(void);


void sub_0800B0F8(void)
{
    u32 i = 0;
    u8 *page = &gState0Page;
    u8 *destination = (u8 *)0x06007A00;
    do
    {
        { u32 offset = i * 256 + *page * 32; CpuFastSet((const u8 *)0x084C4330 + offset, destination, 8); }
        destination += 32;
        i++;
    } while (i < 5);
}

void sub_0800B130(void)
{
    u8 *work = gState0TypedWork.bytes;
    u16 *counter = &gState0TypedWork.selection.word48;
    (*counter)++;
    if (*counter > 180 && (*counter & 1))
    {
        sub_0800B0F8();
        work[0x3F]++;
        if (work[0x3F] == 8)
        {
            *counter = 0;
            work[0x3F] = 0;
        }
    }
}


void sub_0800B468(void)
{
    if (*(u8 *)&gRepeatedKeys & 48)
    {
        sub_08009EA0(); sub_08009EF4(); sub_08009F50(); sub_08009FC8();
        sub_0800AFF8(); sub_0800B174();
    }
}
