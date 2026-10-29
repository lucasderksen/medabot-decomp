/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_late_graphics.h"
#include "gba.h"


s32 sub_08067578(s32 step);

s32 sub_08067578(s32 step) {

  s32 initialRow;
  s32 row;
  volatile u16 *control;
  u32 sourceRow, destinationRow;
  u32 sourceBank, destinationBank, sourceAddress, destinationAddress;
  u32 mask, base;
  initialRow = 0;
  if (step > 3)
  {
    return 1;
  }
  row = initialRow;
  control = (u16 *) 0x04000008;
  mask = 0x1FU;
  base = 0x06000000U;
  do
  {
    sourceBank = (((u32)*control >> 8) & mask) << 11;
    sourceRow = (u32)row + 4U;
    sourceRow -= (u32)step;
    sourceRow <<= 6;
    sourceRow += base;
    sourceAddress = sourceBank + sourceRow;
    destinationBank = (((u32)*control >> 8) & mask) << 11;
    destinationRow = (u32)row + 3U;
    destinationRow -= (u32)step;
    destinationRow <<= 6;
    destinationRow += base;
    destinationAddress = destinationBank + destinationRow;
    CpuSet((const void *)sourceAddress, (void *)destinationAddress, 0xDU);
    row += 1;
  }
  while (row <= 2);
  return 0;
}
