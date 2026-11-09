#ifndef GUARD_RECORD_HELPERS_H
#define GUARD_RECORD_HELPERS_H
#include "gba.h"

struct RecordObjectPlacement
{
    u16 unknown00;
    u16 x;
    u16 y;
    s8 key;
    u8 flags;
};

struct RecordObjectWork
{
    struct OamEntry *objects;
    const struct RecordObjectPlacement *placement;
    s16 key;
    u8 rows;
    u8 columns;
};

struct RecordObjectList
{
    struct RecordObjectWork **entries;
    u16 count;
};

struct RecordAssetPair { const void *source; u32 unknown04; };
struct RecordSpriteFlags { u8 color:1, affineMode:2, mode:2, hFlip:1, vFlip:1, unknown:1; } __attribute__((packed));
struct RecordSpriteGrid { u8 rows:4, columns:4; } __attribute__((packed));
struct RecordAssetSet
{
    const struct RecordAssetPair *entries;
    u8 unknown04[0xB];
    u8 child0F;
    u8 child10;
    u8 palette;
    u8 height;
    u8 width;
    struct RecordSpriteGrid grid;
    struct RecordSpriteFlags flags;
};
struct RecordTileBlock { u8 unknown00[4]; u16 tile; u8 unknown06[10]; };

void sub_08044CDC(u32 mode);
u32 DecompressLz77OrCopy(const void *source, void *destination);
u32 CopyWordUnits(u32 *destination, const u32 *source, u32 bytes);
u32 CopyHalfwordUnits(u16 *destination, const u16 *source, u32 bytes);
void CopyByteUnits(u8 *destination, const u8 *source, u32 bytes);
void SetOamShapeAndSize(struct OamEntry *object, s32 width, s32 height);
u32 GetOamDimensions(s32 shape, s32 size);
void LoadObjectTiles(const void *source, u32 tile, void *scratch, u32 useCpu);
void ReorderObjectTileGrid(void *destination, const void *source, s32 shape, s32 size, s32 rows, s32 columns, s32 mode);
void LoadReorderedObjectTiles(const void *source, s32 shape, s32 size, s32 rows, s32 columns, s32 mode, u32 tile, u32 unused, void *scratch, u32 useCpu);
u32 LoadRecordObjectGrid(struct OamEntry *, const void *, const void *, const u32 *, const struct RecordObjectPlacement *, u8, u16);
u32 InitRecordObjectWork(struct RecordObjectWork *, struct OamEntry *, const void *, const void *, const u32 *, const struct RecordObjectPlacement *, u8, u16);
void sub_0804538C(struct RecordObjectWork *, s32 y, s32 x, s32 key);
u32 FindOamInsertIndex(const struct OamEntry *, u16 count, u16 key);
u32 CopyRecordObjects(const struct RecordObjectWork *, struct OamEntry *, u16 index, u16 limit);
struct OamEntry *MakeOamInsertGap(struct OamEntry *, u16 count, s32 gap, s32 key);
u32 InsertRecordObjects(const struct RecordObjectWork *, struct OamEntry *, u16 index, s32 priority, u32 limit, u32 mode);
u32 InsertAffineRecordObjects(const struct RecordObjectWork *, struct OamEntry *, u16 index, s32 priority, u32 limit, u32 mode);
void InitRecordObjectList(struct RecordObjectList *, struct RecordObjectWork **entries);
void AppendRecordObjectList(struct RecordObjectList *, struct RecordObjectWork *, s32 key);
u32 CopyRecordObjectList(const struct RecordObjectList *, struct OamEntry *, u16 limit);
u32 SortAndCopyRecordObjectList(struct RecordObjectList *, struct OamEntry *, u16 limit);
void SortOamRangeByKey(struct OamEntry *, u16 start, u16 end);
void WriteOamAffineFields(struct OamEntry *objects, const u16 *parameters);
u32 IsObjectPositionVisible(s32 y, s32 x);
u32 InsertRecordObjectsLimited(const struct RecordObjectWork *, struct OamEntry *, u16 index, u32 unused, u32 priority, u8 mode);
void PositionRecordObjectWork(struct RecordObjectWork *, u16 y, u16 x, u32 mode);
u32 PlaceRecordObjects(struct RecordObjectWork *, struct OamEntry *, u16 index, s16 y, s16 x, u16 key, u8 priority, u8 mode);
u32 PlaceScaledRecordObjects(struct RecordObjectWork *, struct OamEntry *, u16 index, s16 y, s16 x, u16 key, u8 priority, u8 flip, u16 scale, u16 *affine, u32 mode);
u32 PlaceRotatedRecordObjects(struct RecordObjectWork *, struct OamEntry *, u16 index, s16 y, s16 x, u16 key, u8 priority, u16 angle, u16 *affine, u32 mode);
void sub_08045D1C(u8 *work);
u16 InitRecordSpriteObject(struct OamEntry *, const struct RecordAssetSet *, u8 palette, u32 tile);
u32 sub_08045E6C(const struct RecordAssetSet *const *, const u32 *commands, u8 selector, u8 palette, struct RecordTileBlock *records, u16 *tileBase, u32 mode);
void LoadRecordCommandTiles(const struct RecordAssetSet *const *, struct RecordTileBlock *, const u32 *commands, u8 selector, u8 recordIndex);
void sub_08046CC8(s32 first, s32 second, s32 third, s32 fourth);

#endif
