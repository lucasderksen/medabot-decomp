#ifndef GUARD_RENDER_WORK_H
#define GUARD_RENDER_WORK_H

#include "gba.h"

/* Accessed offsets are verified; broader object roles remain provisional. */
struct RenderWork
{
    u8 unknown000[0xB84];
    struct OamEntry objects[128];
    u8 unknownF84[8];
    u8 unknownF8C[0x108];
    u8 byte1094;
    u8 byte1095;
};

extern u32 gRenderMode;
extern struct RenderWork *gRenderWork;

#endif
