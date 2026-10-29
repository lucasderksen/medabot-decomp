

#include "record_helpers.h"

struct ObjectAttributes
{
    u32 y:8, affineMode:2, mode:2, mosaic:1, color:1, shape:2;
    u32 x:9, matrixLow:3, hFlip:1, vFlip:1, size:2;
    u32 tile:10, priority:2, palette:4, key:16;
};

u32 sub_08045D34(struct OamEntry *entry, const struct RecordAssetSet *source, u8 palette, u32 tile)
{
    struct ObjectAttributes *object = (struct ObjectAttributes *)entry;
    const struct RecordAssetSet *descriptor = source;
    struct RecordSpriteFlags flags;
    u16 dimensions[2];
    u16 tiles;
    object->y = 0;
    flags = descriptor->flags;
    object->affineMode = flags.affineMode;
    object->mode = flags.mode;
    object->mosaic = 0;
    object->color = flags.color;
    object->shape = 0;
    object->x = 0;
    object->matrixLow = 0;
    object->hFlip = flags.hFlip;
    object->vFlip = flags.vFlip;
    object->size = 0;
    object->tile = (u16)tile;
    object->priority = 2;
    object->palette = palette + source->palette;
    object->key = 0;
    dimensions[0] = source->height;
    if ((descriptor->grid.rows) > 1)
        dimensions[0] = Div(dimensions[0], descriptor->grid.rows);
    dimensions[1] = source->width;
    if ((descriptor->grid.columns) > 1)
        dimensions[1] = Div(dimensions[1], descriptor->grid.columns);
    sub_08044DA8(entry, dimensions[0], dimensions[1]);
    tiles = (dimensions[0] >> 3) * (dimensions[1] >> 3);
    if (((const u8 *)source)[0x15] & 1)
        tiles *= 2;
    return tiles;
}
