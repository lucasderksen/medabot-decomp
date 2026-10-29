#ifndef GUARD_TILE_TEXT_H
#define GUARD_TILE_TEXT_H

#include "global.h"

struct TileCoordinates
{
    u16 x;
    u16 y;
};

void sub_0803EA38(void);
void sub_08042678(void *destination, u32 length);
void sub_08042698(u32 width, u32 height, u32 x, u32 y, u32 control, u32 firstEntry);
void sub_080426F0(u32 value, u32 x, u32 y, u32 control, u32 firstEntry);
void sub_08042838(u32 value, u32 x, u32 y, u32 columns, u32 control, u32 firstEntry);
void sub_08042950(u32 value, u32 x, u32 y, u32 columns, u32 control, u32 firstEntry);
void sub_08042A90(u32 first, u32 second, u32 x, u32 y, u32 separator, u32 control, u32 firstEntry);
void sub_08042B58(u32 record, u32 slot, void *destination);
u32 sub_08042B80(u32 value);
struct TileCoordinates sub_08042BC0(u32 angle, u32 radius, u32 x, u32 y);

#endif
