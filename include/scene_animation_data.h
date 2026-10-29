#ifndef GUARD_SCENE_ANIMATION_DATA_H
#define GUARD_SCENE_ANIMATION_DATA_H
#include "global.h"

/* Native 08049440 fetches four halfwords at an eight-byte command stride.
 * Loops store only two words, stops one, and empty roots may have one word.
 * The reader deliberately fetches adjacent ROM words before testing the opcode. */
extern const u16 gSceneAnimationWords_083F704C[1434];
extern const u16 *const gUnknown_083F7B80[128];
#endif
