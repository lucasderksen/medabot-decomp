/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "continued_scene_records.h"
#include "frame.h"


void sub_0806CEDC(void);

void sub_0806CEDC(void) {

    s32 t;

    t = gFrameObjects[0x20].unknown1A;
    if (t != 0) {
        if (gFrameObjects[0x1E].commandOffset != 0) {
            gFrameObjects[0x20].frameAndGroup = 8;
            gFrameObjects[0x1F].screenY = 0x12;
        } else if (t <= 3) {
            gFrameObjects[0x20].frameAndGroup = 8;
        } else {
            switch (gFrameObjects[0x20].commandOffset) {
            case 0: {
                s32 frame = 0xB;
                if (t <= 7)
                    frame = 0xA;
                gFrameObjects[0x20].frameAndGroup = frame;
                break;
            }
            case 1: {
                s32 frame = 8;
                if (t <= 0xE)
                    frame = 9;
                gFrameObjects[0x20].frameAndGroup = frame;
                break;
            }
            case 2: {
                s32 frame = 0xD;
                if (t <= 7)
                    frame = 0xC;
                gFrameObjects[0x20].frameAndGroup = frame;
                break;
            }
            }
        }
    } else {
        gFrameObjects[0x20].frameAndGroup = 7;
    }
}
