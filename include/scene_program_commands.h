#ifndef GUARD_SCENE_PROGRAM_COMMANDS_H
#define GUARD_SCENE_PROGRAM_COMMANDS_H
#include "global.h"

/* 0805424C consumes signed 32-bit words. Many actor commands skip a word;
 * that stored operand is retained even though actor selection comes from CALL.
 * Pointer-to-word initializers use the target GCC ROM-relocation extension. */
#define SCENE_SETUP(a0, a1, a2, a3) 0x01, (a0), (a1), (a2), (a3)
#define SCENE_TICK 0x02
#define SCENE_ACTOR_TIMER(a0, a1, a2, a3, a4) 0x03, (a0), (a1), (a2), (a3), (a4)
#define SCENE_END 0x04
#define SCENE_POSITION_X(a0, a1, a2) 0x06, (a0), (a1), (a2)
#define SCENE_POSITION_Y(a0, a1, a2) 0x07, (a0), (a1), (a2)
#define SCENE_POSITION_Z(a0, a1, a2) 0x08, (a0), (a1), (a2)
#define SCENE_TIMER_VALUE_0(a0, a1) 0x09, (a0), (a1)
#define SCENE_TIMER_VALUE_1(a0, a1) 0x0A, (a0), (a1)
#define SCENE_WAVE_VALUE_0(a0, a1, a2) 0x0B, (a0), (a1), (a2)
#define SCENE_WAVE_VALUE_1(a0, a1, a2) 0x0C, (a0), (a1), (a2)
#define SCENE_MOTION_X(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) 0x10, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9), (a10), (a11), (a12), (a13), (a14), (a15), (a16)
#define SCENE_MOTION_Y(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) 0x11, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9), (a10), (a11), (a12), (a13), (a14), (a15), (a16)
#define SCENE_MOTION_Z(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) 0x12, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9), (a10), (a11), (a12), (a13), (a14), (a15), (a16)
#define SCENE_TIMER_0(a0, a1, a2, a3, a4, a5) 0x13, (a0), (a1), (a2), (a3), (a4), (a5)
#define SCENE_TIMER_1(a0, a1, a2, a3, a4, a5) 0x14, (a0), (a1), (a2), (a3), (a4), (a5)
#define SCENE_WAVE_0(a0, a1, a2, a3, a4, a5, a6, a7) 0x15, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7)
#define SCENE_WAVE_1(a0, a1, a2, a3, a4, a5, a6, a7) 0x16, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7)
#define SCENE_RAMP_X(a0, a1, a2, a3, a4, a5) 0x17, (a0), (a1), (a2), (a3), (a4), (a5)
#define SCENE_RAMP_Y(a0, a1, a2, a3, a4, a5) 0x18, (a0), (a1), (a2), (a3), (a4), (a5)
#define SCENE_ALPHA(a0, a1, a2, a3, a4, a5) 0x1A, (a0), (a1), (a2), (a3), (a4), (a5)
#define SCENE_CREATE_OBJECT(a0, a1, a2, a3, a4) 0x1B, (a0), (a1), (a2), (a3), (a4)
#define SCENE_HIDE(a0, a1, a2, a3, a4) 0x1C, (a0), (a1), (a2), (a3), (a4)
#define SCENE_OBJECT_STATE(a0, a1, a2) 0x1D, (a0), (a1), (a2)
#define SCENE_BLINK(a0, a1, a2, a3, a4) 0x1E, (a0), (a1), (a2), (a3), (a4)
#define SCENE_ACTOR_FIELDS_1E0(a0, a1, a2, a3) 0x1F, (a0), (a1), (a2), (a3)
#define SCENE_ACTOR_FIELDS_1EC(a0, a1, a2, a3) 0x20, (a0), (a1), (a2), (a3)
#define SCENE_CALL(a0, a1) 0x22, (a0), (s32)(a1)
#define SCENE_RETURN 0x23
#define SCENE_SCHEDULE(a0, a1, a2, a3) 0x24, (a0), (a1), (a2), (s32)(a3)
#define SCENE_SCHEDULE_RELATIVE(a0, a1, a2, a3, a4, a5) 0x24, (a0), (a1), (a2), (s32)(a3), (a4), (a5)
#define SCENE_FADE_IN(a0, a1, a2) 0x80, (a0), (a1), (a2)
#define SCENE_FADE_COLOR(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) 0x82, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9)
#define SCENE_FADE_COLOR_REVERSE(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) 0x83, (a0), (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8), (a9)
#define SCENE_RESTORE_MAP 0x84
#define SCENE_VIEWPORT(a0, a1, a2, a3) 0x85, (a0), (a1), (a2), (a3)
#define SCENE_ASSIGN_OBJECT(a0, a1, a2, a3, a4, a5, a6) 0x86, (a0), (a1), (a2), (a3), (a4), (a5), (a6)
#define SCENE_CONTINUED_STATE(a0) 0x88, (a0)
#define SCENE_COPY_ACTOR(a0, a1, a2) 0x89, (a0), (a1), (a2)
#define SCENE_TIMED_CALL(a0, a1, a2, a3, a4, a5) 0x8A, (a0), (a1), (a2), (a3), (a4), (a5)
#define SCENE_RESTORE_ACTORS 0x8B

#endif
