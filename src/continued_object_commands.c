#include "continued_commands.h"
#include "frame.h"
#include "later_graphics.h"
#include "background_state.h"
#include "post_dispatch.h"

/* Partial observed view; byte38 is at 03005348 and total work size is unknown. */
struct CommandBackgroundView { u8 bytes[0x38]; u8 byte38; };
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D38[];
extern u8 gLaterBuffer_03006D20[];
void sub_0804B9E8(void);

void sub_0804B7C8(void)
{
    u8 *work = gUnknown_030057E0;
    struct CommandBackgroundView *settings;
    u8 *objects;
    u8 *first = work + 0xC88;
    u32 zero = 0;
    u32 byteZero;
    *first = zero;
    work[0xC89] = zero;
    work[0xC93] = zero;
    {
        u16 *field = (u16 *)(work + 0xC8A);
        byteZero = 0;
        *field = zero;
    }
    *(u16 *)(work + 0xC8E) = zero;
    work[0xC5F] = byteZero;
    work[0xC60] = byteZero;
    gLaterBuffer_03006D38[6] = byteZero;
    settings = (struct CommandBackgroundView *)&gBackgroundState_03005310;
    settings->byte38 = byteZero;
    sub_08049714(work + 0xCA4, 16);
    sub_08049714(gLaterBuffer_03006D20, 16);
    objects = (u8 *)gFrameObjects;
    objects[47 * 64 + 0x25] = 1;
    sub_0805196C();
}

void sub_0804B9B0(void)
{
    gUnknown_030057E0[0xC5B] = 1;
    sub_0804B9E8();
}

void sub_0804B9CC(void)
{
    gUnknown_030057E0[0xC5B] = 0;
    sub_0804B9E8();
}

void sub_0804B9E8(void)
{
    u8 *work;
    u8 *objects;
    {
        u32 value = sub_0804D83C();
        work = gUnknown_030057E0;
        work[0x7FE] = value;
    }
    { u32 value = sub_0804D83C(); work[0x7FC] = value; }
    { u32 value = sub_0804D83C(); work[0x7FD] = value; }
    { u32 value = sub_0804D83C(); work[0xC56] = value; }
    { u32 value = sub_0804D83C(); work[0xC57] = value; }
    objects = (u8 *)gFrameObjects;
    { u32 value = objects[47 * 64 + 0x20]; work[0xC67] = value; }
    work[0xC89] = 1;
}

void sub_0804BA5C(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *argument = work + 0xC94;
    u8 *objects;
    u8 *flags;
    *argument = value;
    objects = (u8 *)gFrameObjects;
    flags = objects + 47 * 64 + 0x21;
    *flags = value;
    sub_08049420(47, *flags);
    value = *flags;
    objects[47 * 64 + 0x20] = value;
    sub_08052E0C(*argument);
}

void sub_0804BA9C(void)
{
    u8 *work = gUnknown_030057E0;
    u8 *objects = (u8 *)gFrameObjects;
    u32 value = *(u16 *)(objects + 47 * 64 + 4);
    u8 *argument = work + 0xC94;
    u32 zero = 0;
    *argument = value;
    objects[47 * 64 + 0x26] = zero;
    objects[47 * 64 + 0x28] = zero;
    sub_08047BA8(112);
    work[0xC89] = 1;
}
