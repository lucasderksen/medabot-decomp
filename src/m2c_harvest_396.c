/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_display.h"
#include "state0_work.h"


void sub_0802E7A0(void);

void sub_0802E7A0(void) {

  u32 index;
  u32 stateRoot;
  u8 *clearDestination;
  u32 frameRoot;
  u32 enabledRoot;
  u32 bankRoot;
  int stateOffset;
  u32 address;
  u32 source;
  u8 *clear;
  u8 *out;
  u8 *state;
  u8 zero;
  index = 0;
  stateRoot = 0x03001800U; /* Mapped gState0TransferWork.bytes. */
  enabledRoot = stateRoot;
  enabledRoot += 0xD2;
  frameRoot = 0x03002C30U; /* Mapped gFrameObjects backing. */
  bankRoot = stateRoot;
  bankRoot += 0x87;
  zero = 0;
  clear = (u8 *) frameRoot;
  clear += 0x2A3;
  out = (u8 *) frameRoot;
  out += 0x2B0;
  stateOffset = 0xAA;
  do
  {
    clearDestination = clear;
    address = index;
    address += enabledRoot;
    if (*((u8 *) address))
    {
      source = *((u8 *) bankRoot);
      source <<= 8;
      source += 0x1740;
      source += frameRoot;
      *((u16 *) (out + 0)) = *((u16 *) (source + 2));
      source = *((u8 *) bankRoot);
      source <<= 8;
      source += 0x1740;
      source += frameRoot;
      *((u16 *) (out + 2)) = (*((u16 *) (source + 4))) - 4;
      *clearDestination = zero;
    }
    clear += 0x40;
    out += 0x40;
    index++;
  }
  while (index <= 2);
  state = (u8 *) stateRoot;
  state += stateOffset;
  *state = (*state) + 1;
}
