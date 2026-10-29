#include "global.h"
#include "continued_commands.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_03006D20[];
extern void sub_08050554(u32 value);

#define SELECT_ACTION(name) \
void name(void) \
{ \
    u8 *work; \
    u8 *argument; \
    u32 index; \
    sub_0804D8CC(5); \
    work = gUnknown_030057E0; \
    argument = work + 0xC94; \
    index = *argument; \
    { u32 value = sub_08050710(); sub_0804DBD0(index, (u8)value); } \
    { s32 value = sub_0804DBF0(*argument); gLaterBuffer_03006D20[10] = value + 79; } \
    work[0xC89] = 1; \
}

SELECT_ACTION(sub_0804C02C)
SELECT_ACTION(sub_0804C078)
SELECT_ACTION(sub_0804C318)

void sub_0804C0C4(void)
{
    u8 *work;
    sub_0804D8CC(4);
    work = gUnknown_030057E0;
    sub_08050358(work[0xC94], work[0xC95], work[0xC96], work[0xC97]);
}

void sub_0804C100(void)
{
    u8 *work;
    sub_0804D8CC(2);
    work = gUnknown_030057E0;
    sub_0805076C(work[0xC94] & 15, work[0xC95]);
}

#define FRAME_ACTION(name) \
void name(void) \
{ \
    u8 *work; \
    sub_0804D8CC(2); \
    work = gUnknown_030057E0; \
    { s32 value = sub_0804DBF0(work[0xC94]); gLaterBuffer_03006D20[10] = value + 79; } \
    work[0xC89] = 1; \
}

FRAME_ACTION(sub_0804C130)
FRAME_ACTION(sub_0804C168)
FRAME_ACTION(sub_0804C3AC)

void sub_0804C1A0(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    u8 *argument = work + 0xC94;
    *argument = value;
    sub_08050554(*argument);
}

#define MARK_ACTION(name) \
void name(void) \
{ \
    u32 value = sub_0804D83C(); \
    u8 *work = gUnknown_030057E0; \
    work[0xC94] = value; \
    work[0xC89] = 1; \
}

MARK_ACTION(sub_0804C2C8)
MARK_ACTION(sub_0804C2F0)
