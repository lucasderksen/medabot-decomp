#include "link_tiles.h"

/* Selectors 5..7 generate tile numbers instead of reading this address. */
extern const u16 gLinkGeneratedPattern_087C68A0[];

const u8 gLinkTileWidths[8] = { 2, 1, 2, 2, 8, 2, 2, 2 };
const u8 gLinkTileHeights[8] = { 2, 10, 10, 2, 5, 2, 2, 2 };
const u16 gLinkTileOffsets[8] = { 576, 580, 590, 610, 104, 133, 135, 137 };
const struct LinkTilePatternPointers gLinkTilePatterns = {{
    &gLinkTilePattern0[0][0], &gLinkTilePattern1[0][0],
    &gLinkTilePattern2[0][0], &gLinkTilePattern3[0][0],
    &gLinkTilePattern4[0][0], gLinkGeneratedPattern_087C68A0,
    gLinkGeneratedPattern_087C68A0, gLinkGeneratedPattern_087C68A0
}};
const u16 gLinkTileBases[8] = {
    0x8000, 0x9000, 0xA000, 0xB000, 0xC000, 0xD000, 0xD000, 0xD000
};

const u16 gLinkTilePattern0[2][2] = { {0, 1}, {2, 3} };
const u16 gLinkTilePattern1[10][1] = {
    {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}
};
const u16 gLinkTilePattern2[10][2] = {
    {0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9},
    {10, 11}, {12, 13}, {14, 15}, {16, 17}, {18, 19}
};
const u16 gLinkTilePattern3[2][2] = { {0, 1}, {2, 3} };
const u16 gLinkTilePattern4[5][8] = {
    {0, 1, 2, 3, 3, 3, 4, 5},
    {6, 7, 8, 9, 9, 9, 9, 10},
    {11, 12, 13, 9, 9, 9, 9, 14},
    {15, 16, 17, 18, 19, 20, 21, 22},
    {23, 24, 25, 26, 26, 26, 27, 28}
};
