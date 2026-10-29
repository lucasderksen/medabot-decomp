/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "graphics.h"

extern const u8 gUnknown_084881E0[];
extern const u8 gUnknown_084882CC[];
extern const u8 gUnknown_08488308[];

void sub_0801AC98(u32 bank);

void sub_0801AC98(u32 bank) {

    if(bank<=2){
        LoadLeTilemap(0,0xD,gUnknown_084882CC,*(volatile u16 *)0x0400000A,0x258);
        LoadLeTilemap(0,0x11,gUnknown_084881E0,*(volatile u16 *)0x0400000A,0x210);
    }else{
        LoadLeTilemap(0x12,0xD,gUnknown_08488308,*(volatile u16 *)0x0400000A,0x270);
        LoadLeTilemap(0x14,0x11,gUnknown_084881E0,*(volatile u16 *)0x0400000A,0x210);
    }
}
