#ifndef GUARD_SCENE_ANIMATION_H
#define GUARD_SCENE_ANIMATION_H
#include "global.h"
struct SceneAnimationRecord {
    u16 frame;
    s16 duration;
    u8 next;
    u8 padding[3];
};
extern const struct SceneAnimationRecord gSceneAnimationRecords_084857FC[32];
#endif
