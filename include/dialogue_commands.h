#ifndef GUARD_DIALOGUE_COMMANDS_H
#define GUARD_DIALOGUE_COMMANDS_H
#include "global.h"

/* Native commands of the 0803FD28 dialogue interpreter. Operands are bytes,
 * including portrait FF (blank) and timer FF; those are not end commands. */
#define DIALOGUE_DELAY_F7(ticks) 0xF7, (ticks)
#define DIALOGUE_FONT_TOGGLE 0xF8
#define DIALOGUE_INSERT(buffer) 0xF9, (buffer)
#define DIALOGUE_DELAY_FA(ticks) 0xFA, (ticks)
#define DIALOGUE_PORTRAIT(side, character, frame) 0xFB, (side), (character), (frame)
#define DIALOGUE_PAGE 0xFC
#define DIALOGUE_NEWLINE 0xFD
#define DIALOGUE_SKIP 0xFE
#define DIALOGUE_END(mode) 0xFF, (mode)

/* Root 0/1 uses the first directory; roots 2..17 use the sixteen child
 * directories. Native self-references in the first directory are retained. */
extern const void *const gStateScripts_084144B4[256];
extern const void *const *const gStateScriptTables_0847DF24[16];
extern const void *const gQuantityScripts_0847E388[33];

#endif
