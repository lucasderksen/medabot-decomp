/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_commands.h"
#include "encounter_choices.h"
#include "fresh_helpers.h"
#include "gba.h"
#include "record_helpers.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

extern const struct EncounterChoiceRecord gChoiceRecords6A024[];
extern const u16 gObjectPaletteBanks_0807C210[53][16];
extern const u8 *const gFreshPointers_083F7E80[];
extern const u8 gUnknown_087AE6D8[];
extern u8 gUnknown_03006FDC;

void sub_08069A08(void);

void sub_08069A08(void) {

    volatile struct DmaTransfer *dma;
    const void *const *palettes;
    const struct EncounterChoiceRecord *choices;
    const u8 *const *encounters;
    const u8 *selection;
    const u8 *record;
    u32 control;
    LZ77UnCompVram(gFreshPointers_083F7E80[37], (void *)0x06012400);
    dma = (volatile struct DmaTransfer *)0x040000D4;
    palettes = gPaletteSourcePointers_083F83C0;
    dma->source = palettes[37];
    dma->destination = (void *)0x05000200;
    dma->control = 0x80000010;
    (void)dma->control;
    LZ77UnCompVram(gUnknown_087AE6D8, (void *)0x06012E00);
    LZ77UnCompVram(gFreshPointers_083F7E80[0], (void *)0x06015100);
    dma->source = palettes[0];
    dma->destination = (void *)0x05000300;
    control = 0x84000008;
    dma->control = control;
    (void)dma->control;
    encounters = gState0EncounterRecords_083C1B80;
    choices = gChoiceRecords6A024;
    selection = &gUnknown_03006FDC;
    record = encounters[choices[*selection].firstRecord];
    LZ77UnCompVram(gFreshPointers_083F7E80[record[0]], (void *)0x06015A00);
    dma->source = palettes[record[0]];
    dma->destination = (void *)0x05000320;
    dma->control = control;
    (void)dma->control;
    record = encounters[choices[*selection].secondRecord];
    LZ77UnCompVram(gFreshPointers_083F7E80[record[0]], (void *)0x06016300);
    dma->source = palettes[record[0]];
    dma->destination = (void *)0x05000340;
    dma->control = control;
    (void)dma->control;
    dma->source = gObjectPaletteBanks_0807C210[19];
    dma->destination = (void *)0x050003A0;
    dma->control = control;
    (void)dma->control;
}
