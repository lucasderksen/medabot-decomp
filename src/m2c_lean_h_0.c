/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "continued_scene_records.h"
#include "encounter_choices.h"
#include "frame.h"
#include "graphics.h"
#include "state0_work.h"

extern u8 sub_0807CEC8(u8 numerator, s32 denominator);
extern u8 sub_0807CF40(u8 numerator, s32 denominator);

void sub_0805E334(u8 *name);

void sub_0805E334(u8 *name) {

    u16 *top;
    u16 *bottom;
    s32 i;
    u16 value;
    u8 code;
    u32 block;
    u32 addr;
    u8 column;
    u8 row;

    top = (u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x060000CA);
    bottom = (u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x0600010A);
    for (i = 0; i < 10; i++)
    {
        code = *name;
        if ((value = code) != 0)
        {
            code--;
            block = (*(volatile u16 *)0x0400000A >> 8) & 0x1F;
            column = sub_0807CF40(code, 26);
            row = sub_0807CEC8(code, 26);
            block <<= 11;
            block += column * 2;
            block += row * 0xC0;
            block += 0x06000204;
            *top++ = *(u16 *)block;
            addr = (*(volatile u16 *)0x0400000A >> 8) & 0x1F;
            addr <<= 11;
            addr += column * 2;
            addr += row * 0xC0;
            addr += 0x06000244;
            value = *(u16 *)addr;
            *bottom++ = value;
        }
        else
        {
            *top++ = value;
            *bottom++ = value;
        }
        name++;
    }
}
