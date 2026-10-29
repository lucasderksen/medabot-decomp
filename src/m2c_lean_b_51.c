/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "continued_numeric.h"
#include "continued_scene_records.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "scene_view.h"
#include "sprite_layouts.h"
#include "tile_text.h"


void sub_08053C7C(float x, float y, float z, float *outX, float *outY, float *outZ);

void sub_08053C7C(float x, float y, float z, float *outX, float *outY, float *outZ) {

    float u, v, w, d;

    u = x * gSceneView.rotation50 + y * gSceneView.rotation54;
    v = -x * gSceneView.rotation54 + y * gSceneView.rotation50;
    w = z * gSceneView.rotation58 - u * gSceneView.rotation5C;
    d = gSceneView.depth4C - (u * gSceneView.rotation58 + z * gSceneView.rotation5C);
    if (d == 0.0f)
        d = 1.0f;
    u = (float)gSceneView.wordA0 / d;
    *outX = v * u;
    *outY = w * u;
    *outZ = d;
}
