/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "encounter_parts.h"
#include "frame.h"
#include "record_helpers.h"
#include "sound_samples.h"
#include "sprite_layouts.h"
#include "state0_work.h"
#include "tile_text.h"

struct SetupPart364A8 { u8 name[0x11]; u8 count; u8 rest[6]; };
struct SetupRecord364A8 { u8 head[0x48]; struct SetupPart364A8 parts[4]; u8 tail[0x58]; };

extern struct SetupRecord364A8 gSetupRecords364A8[] asm("gSetupBuffer_03000590");

void sub_080364A8(s32 mode, s32 slot);

void sub_080364A8(s32 mode, s32 slot) {

    u32 x;
    u32 row;


    x = 6;
    if (mode == 0)
        x = 0x14;
    row = 2;
    if (gSetupRecords364A8[slot].parts[0].count != 0) {
        sub_08042838(gSetupRecords364A8[slot].parts[0].count, x, row, 3, *(volatile u16 *)0x0400000A, 0xA330);
        
        sub_08042838(gSetupRecords364A8[slot].parts[0].name[4], x + 4, row, 3, *(volatile u16 *)0x0400000A, 0xA330);
    } else {
        sub_08042838(gSetupRecords364A8[slot].parts[0].count, x, row, 3, *(volatile u16 *)0x0400000A, 0x8330);
        
        sub_08042838(gSetupRecords364A8[slot].parts[0].name[4], x + 4, row, 3, *(volatile u16 *)0x0400000A, 0x8330);
    }
    if (gSetupRecords364A8[slot].parts[1].count != 0) {
        sub_08042838(gSetupRecords364A8[slot].parts[1].count, x, row + 3, 3, *(volatile u16 *)0x0400000A, 0xA330);
        sub_08042838(gSetupRecords364A8[slot].parts[1].name[4], x + 4, row + 3, 3, *(volatile u16 *)0x0400000A, 0xA330);
    } else {
        sub_08042838(gSetupRecords364A8[slot].parts[1].count, x, row + 3, 3, *(volatile u16 *)0x0400000A, 0x8330);
        sub_08042838(gSetupRecords364A8[slot].parts[1].name[4], x + 4, row + 3, 3, *(volatile u16 *)0x0400000A, 0x8330);
    }
    if (gSetupRecords364A8[slot].parts[2].count != 0) {
        sub_08042838(gSetupRecords364A8[slot].parts[2].count, x, row + 6, 3, *(volatile u16 *)0x0400000A, 0xA330);
        sub_08042838(gSetupRecords364A8[slot].parts[2].name[4], x + 4, row + 6, 3, *(volatile u16 *)0x0400000A, 0xA330);
    } else {
        sub_08042838(gSetupRecords364A8[slot].parts[2].count, x, row + 6, 3, *(volatile u16 *)0x0400000A, 0x8330);
        sub_08042838(gSetupRecords364A8[slot].parts[2].name[4], x + 4, row + 6, 3, *(volatile u16 *)0x0400000A, 0x8330);
    }
    if (gSetupRecords364A8[slot].parts[3].count != 0) {
        sub_08042838(gSetupRecords364A8[slot].parts[3].count, x, row + 9, 3, *(volatile u16 *)0x0400000A, 0xA330);
        sub_08042838(gSetupRecords364A8[slot].parts[3].name[4], x + 4, row + 9, 3, *(volatile u16 *)0x0400000A, 0xA330);
    } else {
        sub_08042838(gSetupRecords364A8[slot].parts[3].count, x, row + 9, 3, *(volatile u16 *)0x0400000A, 0x8330);
        sub_08042838(gSetupRecords364A8[slot].parts[3].name[4], x + 4, row + 9, 3, *(volatile u16 *)0x0400000A, 0x8330);
    }
}
