#ifndef GUARD_FRAME_H
#define GUARD_FRAME_H

#include "gba.h"

/* Stride and accessed offsets are established; gameplay roles are provisional. */
struct FrameObject
{
    u16 flags;                 /* 00 */
    s16 screenX;               /* 02 */
    s16 screenY;               /* 04 */
    u16 frameAndGroup;         /* 06; frame low byte, group high byte */
    u8 scaleX;                 /* 08 */
    u8 scaleY;                 /* 09 */
    u8 palette;                /* 0A */
    u8 priority;               /* 0B */
    union { s32 value; struct { u16 low; s16 high; } parts; } positionX; /* 0C */
    s32 positionY;             /* 10 */
    s32 positionZ;             /* 14 */
    u16 angle;                 /* 18; index masked to 10 bits */
    u16 unknown1A;
    u8 tableSelector;          /* 1C; low nibble selects one of four table bases */
    u8 affineIndex;            /* 1D */
    u8 unknown1E[2];
    u8 commandDelay;           /* 20; decremented by the frame-command helper */
    u8 commandOffset;          /* 21; byte offset in three-byte commands */
    u8 commandStopped;         /* 22; FF suppresses command processing */
    u8 unknown23[8];
    u8 byte2B;                 /* 2B; also accessed by packed-index helpers */
    u8 unknown2C[4];
    s16 value30;               /* 30 */
    s16 value32;               /* 32 */
    u8 unknown34[0xC];
};

union FrameOrderEntry
{
    struct { u8 index; u8 priority; u16 unknown02; } bytes;
    u16 value;
};

extern struct FrameObject gFrameObjects[128];
extern s32 gFrameAffineOverride;
extern struct OamEntry gOamShadow[128];

void sub_08001520(void);
void sub_08001CAC(u32 affineIndex, u32 angle, s32 scaleX, s32 scaleY, u32 flags);
void sub_08001EA8(u32 affineIndex, s32 scaleX, s32 scaleY, u32 flags);
void sub_08001FF8(s32 *x, s32 *y, const struct FrameObject *object);
void sub_08002060(union FrameOrderEntry *entries, u16 count);

#endif
