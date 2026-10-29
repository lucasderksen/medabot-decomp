#ifndef GUARD_SCENE_VIEW_H
#define GUARD_SCENE_VIEW_H
#include "global.h"

/* Observed float scene/projection work at 0x03005350 (gLaterBuffer_03005350)
 * used by the soft-float block 0x08054014-0x08056F24. Field names and the
 * extent are provisional. */
struct SceneView
{
    s32 width;              /* 000 */
    s32 height;             /* 004 */
    u8 unknown08[0x44];
    float depth4C;          /* 04C */
    float rotation50;       /* 050; cosine-like */
    float rotation54;       /* 054; sine-like */
    float rotation58;       /* 058 */
    float rotation5C;       /* 05C */
    float outA[4];          /* 060 */
    float outB[4];          /* 070 */
    float outC[4];          /* 080 */
    float baseX;            /* 090 */
    float baseY;            /* 094 */
    float scale98;          /* 098 */
    s32 word9C;             /* 09C */
    s32 wordA0;             /* 0A0 */
    double doubleA4;        /* 0A4 */
    double doubleAC;        /* 0AC */
    u8 unknownB4[0xC];
    s32 rows[3][4];         /* 0C0 */
    s32 wordF0;             /* 0F0 */
    s32 wordF4;             /* 0F4 */
    s32 tableIndex;         /* 0F8 */
    u8 unknownFC[0xD0];
    s32 word1CC;            /* 1CC */
    s32 word1D0;            /* 1D0 */
    u8 unknown1D4[0x40];
    s32 word214;            /* 214 */
    s32 word218;            /* 218 */
    s32 word21C;            /* 21C */
    s32 word220;            /* 220 */
};
extern u8 gLaterBuffer_03005350[];
#define gSceneView (*(struct SceneView *)gLaterBuffer_03005350)

/* Observed 0x300-byte records behind gSetupPointer_03006D30 (16 entries). */
struct SceneActor
{
    s32 active;             /* 000 */
    s32 word04;             /* 004 */
    s32 word08;             /* 008 */
    u8 unknown0C[4];
    float float10;          /* 010 */
    u8 unknown14[0x44];
    float float58;          /* 058 */
    u8 unknown5C[0x44];
    float floatA0;          /* 0A0 */
    u8 unknownA4[0x54];
    float floatF8;          /* 0F8 */
    u8 unknownFC[0x14];
    float float110;         /* 110 */
    u8 unknown114[0x50];
    float float164;         /* 164 */
    u8 unknown168[0x14];
    float float17C;         /* 17C */
    u8 unknown180[0x14];
    float float194;         /* 194 */
    u8 unknown198[0x28];
    s32 word1C0;            /* 1C0 */
    s32 word1C4;            /* 1C4 */
    s32 word1C8;            /* 1C8 */
    u8 unknown1CC[0x110];
    u8 objects[4];          /* 2DC; gFrameObjects indices */
    u8 unknown2E0[0x20];
};

struct SceneSource
{
    long count; /* Native word-sized object count; all four axis entries are stored. */
    s32 rows[3][4];
};
#endif
