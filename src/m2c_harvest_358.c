/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_graphics.h"
#include "continued_selector_assets.h"
#include "serial.h"
#include "state0_work.h"

struct SelectionLatchWork4AA44 {
    u8 unknown00[0xC5C];
    u8 current;
    u8 unknownC5D[0xC];
    u8 previous;
};

extern struct SelectionLatchWork4AA44 gSelectionLatchWork4AA44;

void sub_0804AA44(void);

void sub_0804AA44(void) {

 u32 addressOrCurrent, offsetOrPreviousAddress, currentAddress, offsetOrPrevious;
 /* Derive both field addresses before reusing the temporary words. */
 addressOrCurrent = (u32)&gSelectionLatchWork4AA44;
 offsetOrPreviousAddress = (u32)&gSelectionLatchWork4AA44.current - addressOrCurrent;
 currentAddress = addressOrCurrent + offsetOrPreviousAddress;
 offsetOrPrevious = (u32)&gSelectionLatchWork4AA44.previous - addressOrCurrent;
 offsetOrPreviousAddress = addressOrCurrent + offsetOrPrevious;
 addressOrCurrent = *(u8 *)currentAddress;
 offsetOrPrevious = *(u8 *)offsetOrPreviousAddress;
 if (addressOrCurrent == offsetOrPrevious) {
  addressOrCurrent = 0;
  *(u8 *)currentAddress = 0;
 }
 *(u8 *)offsetOrPreviousAddress = (u8)addressOrCurrent;
 sub_0804A210();
}
