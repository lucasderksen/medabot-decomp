#ifndef GUARD_FRAME_COMMAND_DATA_H
#define GUARD_FRAME_COMMAND_DATA_H
#include "global.h"

/* Native 08040BD8 encoding. FE reads two bytes; FF reads only its opcode.
 * Sequential instructions advance the byte cursor by three. */
#define FRAME_STEP(delay, frame) (u8)(delay), (u8)((frame) >> 8), (u8)(frame)
#define FRAME_SOUND(sound, unused) 0xFD, (u8)(sound), (u8)(unused)
#define FRAME_JUMP(command) 0xFE, (u8)(command)
#define FRAME_STOP() 0xFF
#define FRAME_UNUSED(value) (u8)(value)
#define FRAME_CLEAR_FLAG(delay, unused) 0xFB, (u8)(delay), (u8)(unused)
#define FRAME_SET_FLAG(unused1, unused2) 0xFC, (u8)(unused1), (u8)(unused2)

extern const u8 gFrameCommandBytes_083B55D4[2860];
extern const void *const gUnknownPointers_083B6100[118];
#endif
