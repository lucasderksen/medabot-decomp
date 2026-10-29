#ifndef GUARD_FRAME_COMMAND_HANDLERS_H
#define GUARD_FRAME_COMMAND_HANDLERS_H

#include "global.h"

/* Word index and status for the indirect call at 0806B0D4. Handlers that
 * observe a byte index narrow it inside the callee, as the ROM does. */
typedef s32 (*FrameCommandHandler)(u32 index);
extern FrameCommandHandler const gFrameCommandHandlers_084857D0[];

s32 sub_0806B134(u32 index);
s32 sub_0806B1A8(u32 index);
s32 sub_0806B1D0(u32 index);
s32 sub_0806B1F8(u32 index);
s32 sub_0806B1FC(u32 index);
s32 sub_0806B248(u32 index);
s32 sub_0806B2B8(u32 index);
s32 sub_0806B2F4(u32 index);
s32 sub_0806B3D8(u32 index);
s32 sub_0806B484(u32 index);
void sub_0806B0D4(void);
void sub_0806B530(u8 index, u8 state, u8 first, u8 second);

/* Word index/status for the third and fourth handlers at 08485BB8. The dispatcher
 * supplies indices 0..25; the handler narrows to a byte at entry. */
s32 sub_08071A64(u32 index);
s32 sub_08071B64(u32 index);
void sub_08071DB8(u32 command, u32 frame, u32 field34);

#endif
