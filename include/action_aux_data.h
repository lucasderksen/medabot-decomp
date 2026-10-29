#ifndef GUARD_ACTION_AUX_DATA_H
#define GUARD_ACTION_AUX_DATA_H
#include "global.h"
struct ActionSpriteSetup { u8 count, kind, x, y; };
extern const struct ActionSpriteSetup gActionSpriteSetup[6];
extern const u8 gActionBaseStats[27][8];
#endif
