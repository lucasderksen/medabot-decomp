#ifndef GUARD_DISPLAY_HELPERS_H
#define GUARD_DISPLAY_HELPERS_H

#include "global.h"

/* Character portrait frame/palette roots; payloads are reconstructed native assets. */
extern const u8 *const gUnknownPointers_083AFE88[176 * 9];
extern const void *const gUnknownPointers_083B1748[176];

/* Address names retain the observed interfaces until callers establish roles. */
u32 sub_0803EED8(void);
void sub_0803EF20(void);
void sub_0803EF8C(u32 width, u32 height, u32 x, u32 y, u32 control, u32 entry);
void sub_0803EFD8(u32 width, u32 height, u32 x, u32 y, u32 control, u32 entry);
void sub_0803F15C(u32 width, u32 height, u32 x, u32 y, const void *source, u32 control, u32 entryOffset);
void sub_0803F1C8(u32 width, u32 height, u32 x, u32 y, const void *source, u32 control, u32 entryOffset);
void sub_0803F3A8(void);
void sub_0803F3E0(void);
void sub_0803F41C(u32 bank, u32 frame, void *destination, u32 paletteSlot, u32 savedPalette);
void sub_0803F480(u32 bank, u32 frame, u32 x, u32 y, u32 mapBank);
u32 sub_0803F51C(u32 bank, u32 frame, u32 x, u32 y, u32 mapBank, u32 reverse);
void sub_0803F624(void *destination, u32 size, u32 value);
void sub_0803F63C(const void *source, void *destination, u32 size);
void sub_0803F65C(void *first, void *second, u32 size);

#endif
