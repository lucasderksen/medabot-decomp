#ifndef GUARD_COORDINATE_HELPERS_H
#define GUARD_COORDINATE_HELPERS_H

#include "tile_text.h"

void sub_08015F90(u32 frameIndex);
void sub_08016080(u32 frameIndex);
struct TileCoordinates sub_08042CA0(u32 angle, u32 radius, u32 x, u32 y, u32 reduceY, u32 reduceX);
void sub_08042D94(u32 first, u32 second, u32 third, u32 fourth, u32 graphicsSlot);
void sub_08042E58(u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);
void sub_0804305C(u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);
void sub_08043240(u32 firstObject, u32 increment);
void sub_080432A0(u32 firstObject, u32 tileGroup, u32 unused);

#endif
