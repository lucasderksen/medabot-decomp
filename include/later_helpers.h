#ifndef GUARD_LATER_HELPERS_H
#define GUARD_LATER_HELPERS_H

#include "global.h"

struct RecordDisplayWork;
struct RenderWork;
void sub_08047204(void);
void sub_0804725C(void *unused, struct RecordDisplayWork *work, s32 mode, u32 index, u32 unused4, u32 palette, u32 bank, u32 enabled);
extern const u32 gLaterCommands_0807EE70[][4];
extern const u32 gLaterCommands_0807F610[][4];
extern const u32 gLaterCommands_0807FDB0[][4];
extern const u32 gLaterCommands_08080550[][8];
void sub_08047414(struct RecordDisplayWork *work, struct RenderWork *render, const void *source, void *data);
void sub_08047570(void);
void sub_08047574(void);

#endif
