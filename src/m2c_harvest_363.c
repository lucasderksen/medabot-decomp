/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "gba.h"
#include "graphics.h"

extern const u8 gAudioWaveformBytes_080B0820[];

void sub_08073A48(s32 waveform);

void sub_08073A48(s32 waveform) {

  u16 soundControl;
  u32 value;
  u32 address;
  value = (u32)waveform * 0x10U;
  address = (u32) gAudioWaveformBytes_080B0820;
  value += address;
  CpuSet((void *) value, (void *) 0x04000090, 0x04000004U);
  address = (u32) (&soundControl);
  value = (u32) (*((volatile u16 *)0x04000070U));
  *((u16 *) address) = (u16) value;
  value = (u32) (&soundControl);
  value = (u32) (*((u16 *) value));
  address = 0x80;
  if (value == 0x80)
  {
    address = 0xC0;
  }
  *((volatile u16 *)0x04000070U) = (u16) address;
}
