#ifndef GUARD_BANKED_COMMANDS_H
#define GUARD_BANKED_COMMANDS_H
#include "global.h"

#define BANKED_COMMAND_COUNT 2288
#define BANKED_COMMAND_WINDOW 0x4000
/* Native offsets are in the 4000..7FFF window. Reader 0804D83C uses:
 * root + (offset - 0x4000) + (bank << 14) + command position.
 * The offset and bank arrays share the same script index. */
extern const u16 gBankedCommandOffsets_08769EC0[BANKED_COMMAND_COUNT];
extern const u8 gBankedCommandBanks_0876B0A0[BANKED_COMMAND_COUNT];
/* Header offsets followed by reserved storage; scripts occupy banks 2..7. */
extern const u8 gSetupData_08765EC0[BANKED_COMMAND_WINDOW];

#endif
