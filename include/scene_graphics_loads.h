#ifndef GUARD_SCENE_GRAPHICS_LOADS_H
#define GUARD_SCENE_GRAPHICS_LOADS_H
#include "global.h"
struct GraphicsLoad { u8 loaded; u8 pad[3]; const void *source; void *destination; u32 unused; };
extern const struct GraphicsLoad gUnknown_080AEB74[192];
#endif
