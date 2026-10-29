#include "global.h"

const u8 gSceneObjectFrames_083AE060[4] = { 0x19, 0x1C, 0x04, 0x07 };

struct SceneObjectPosition {
    u16 x;
    u8 y;
    u8 storedPad;
};

const struct SceneObjectPosition gSceneObjectPositions_083AFACC[4] = {
    { 150, 240, 0xFF },
    { 170, 248, 0xFF },
    { 198, 248, 0xFF },
    { 218, 240, 0xFF },
};
