#ifndef GUARD_CONTINUED_LATE_GRAPHICS_H
#define GUARD_CONTINUED_LATE_GRAPHICS_H

#include "global.h"
#include "map_metadata.h"
#include "main_callbacks.h"

extern u32 gUnknown_0300137C;
extern const MainCallback gUnknownCallbacks_083D5FF4[];
void sub_0805716C(void);
void sub_0805718C(void);
void sub_080492A8(const u16 *source, u16 *destination, s32 row, s32 column,
                  s32 width, s32 height, u32 unused6, u32 unused7,
                  u32 offset, u32 mode);
u32 sub_08057D80(u32 index);
void sub_08057F1C(u32 index);
void sub_08057FD4(void);
void sub_08058070(u32 mode);
extern u8 gContinuedCommandWork_030064A0[];
extern const u8 gUnknownBytes_084C22E8[];
void sub_080491B8(u16 *destination, s32 row, s32 column, s32 width,
                  s32 height, u32 value, u32 palette, u32 mode);
void sub_08049210(const u16 *source, u16 *destination, s32 row, s32 column,
                  s32 width, s32 height, u32 tileOffset, u32 palette, u32 mode);
void sub_080581C8(u32 index);
extern const u8 gUnknownBytes_085FB6E4[];
extern const u8 gUnknownBytes_085FBB78[];
extern const u8 gUnknownBytes_085FBA78[];
extern const u8 gUnknownBytes_085FBBC0[];
extern const u16 gUnknownHalfwords_083D611C[];
extern const u8 gUnknownBytes_085FBC00[];
extern const u8 gUnknownBytes_085FBC88[];
extern const u8 gUnknownBytes_085FBD14[];
extern const u8 gUnknownBytes_085FBD9C[];
extern const u8 gUnknownBytes_085FBE1C[];
extern const u8 gUnknownBytes_085FBEA4[];
extern const u8 gUnknownBytes_085FBF30[];
extern const u8 gUnknownBytes_085FBFB8[];
extern const u8 gUnknownBytes_085FC038[];
extern const u8 gUnknownBytes_085FBBE0[];
extern const u8 gUnknownBytes_085FBDFC[];
extern const u8 gUnknownBytes_084C7F34[];
void sub_08057440(void);
void sub_080574D4(void);
void sub_080575DC(void);
void sub_08057688(void);
void sub_08057698(void);
void sub_080576BC(void);
void sub_080576D0(void);
extern const u8 gUnknownBytes_08487388[];
extern const u8 gUnknownBytes_08487408[];
extern const u8 gUnknownBytes_084C88B8[];
extern u8 gUnknown_030057E0[];
extern u8 gLaterBuffer_030055A0[];
void sub_080576E0(void);
extern const void *const gStateScripts_084144B4[];
void sub_08057AD0(void);
void sub_08057D04(void);
void sub_08057D40(void);
void sub_08057D14(void);
void sub_08057D50(void);
void sub_08057FB4(void);
void sub_08057B0C(void);
void sub_08057B6C(void);
void sub_08057CB0(void);
extern u8 gContinuedOtherWork_030057A0[];
extern const u8 gSelectorLookup_083D2B6B[];
extern const u8 gUnknownBytes_083D6118[];
void sub_08058208(u32 unused);
void sub_0805821C(u32 selector);
void sub_080582B8(u32 selector, s32 mode);
void sub_080589A4(s32 count);
void sub_08058C0C(u32 selector);
void sub_08059434(u32 index,u32 value,unsigned short digits,u32 x,u32 y);
void sub_08059734(u32 value,u32 digits,u32 x,u32 y);
void sub_080598C0(const void *source,u32 count,u32 x,u32 y);
extern u16 *const gNavigationHalfwordPointers_083D625C[];
extern const u8 gCopiedBytes_083D2DBD[];
extern u8 gLaterBuffer_03006D38[];
extern const void *const *const gStateScriptTables_0847DF24[];
void sub_08058A10(u32 index, s32 limit);
extern u16 *const gNavigationHalfwordPointers_083D6268[];
void sub_08058AB8(u32 index, s32 limit);
extern u8 *const gNavigationBytePointers_083D6274[];
void sub_08058B28(u32 index, s32 limit);
extern u8 *const *const gNavigationNestedBytePointers_083D62C8[];
void sub_08058B90(u32 category, u32 subindex, s32 limit);
void sub_08059960(void);
u32 sub_080594C8(void);
void sub_08059560(void);
void sub_08059578(void);
extern const u8 gNumericTiles_080ACCF4[];
void sub_0805FD10(void);
s32 sub_08067578(s32 step);

#endif
