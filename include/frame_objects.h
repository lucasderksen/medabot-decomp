#ifndef GUARD_FRAME_OBJECTS_H
#define GUARD_FRAME_OBJECTS_H

#include "frame.h"

/* Address-based names remain provisional; see docs/FRAME_OBJECTS.md. */
void InitFrameObjectCommands(const u8 *commands, u8 index);
void RunFrameObjectCommands(const u8 *commands, u8 index);
void ClearFrameObjects(u8 start, u8 count);
void HideFrameObjects(u8 start, u8 count);
void ShowFrameObjects(u8 start, u8 count);
u32 sub_08040D78(u8 start, u8 count);
/* Word slots are narrowed inside the callee, as observed at both call sites and entry. */
void PlaceAlignedTextObjects(const u8 *bytes, u32 start, s32 x, s32 y, u32 boxWidth, u32 palette, u32 alignment, u32 flags);
void sub_08040EE4(const u8 *bytes, u8 start, s32 x, s32 y, u8 boxWidth, u8 palette, u8 alignment, u16 flags, s32 xOffset, s32 yOffset);
void sub_08041020(const u8 *bytes, u8 start, s32 x, s32 y, u8 boxWidth, u8 palette, u8 alignment, u16 flags);
void FormatDecimalString(u8 *output, u32 value);
void sub_08041490(u8 *output, u32 value, u32 base);

#endif
