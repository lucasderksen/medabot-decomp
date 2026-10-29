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
u32 sub_08044D0C(const void *source, void *destination);
u32 sub_08044D64(u32 *destination, const u32 *source, u32 bytes);
u32 sub_08044D78(u16 *destination, const u16 *source, u32 bytes);
void sub_08044D90(u8 *destination, const u8 *source, u32 bytes);
void sub_08044DA8(struct OamEntry *object, s32 width, s32 height);
u32 sub_08044E64(s32 shape, s32 size);
void sub_08044F54(const void *source, u32 tile, void *scratch, u32 useCpu);
void sub_08044FB4(void *destination, const void *source, s32 shape, s32 size, s32 rows, s32 columns, s32 mode);
void sub_08045084(const void *source, s32 shape, s32 size, s32 rows, s32 columns, s32 mode, u32 tile, u32 unused, void *scratch, u32 useCpu);
u32 sub_08045120(struct OamEntry *, const void *, const void *, const u32 *, const struct RecordObjectPlacement *, u8, u16);
u32 sub_08045328(struct RecordObjectWork *, struct OamEntry *, const void *, const void *, const u32 *, const struct RecordObjectPlacement *, u8, u16);
void sub_0804538C(struct RecordObjectWork *, s32 y, s32 x, s32 key);
u32 sub_080454F0(const struct OamEntry *, u16 count, u16 key);
u32 sub_080455E0(const struct RecordObjectWork *, struct OamEntry *, u16 index, u16 limit);
struct OamEntry *sub_08045588(struct OamEntry *, u16 count, s32 gap, s32 key);
u32 sub_08045680(const struct RecordObjectWork *, struct OamEntry *, u16 index, s32 priority, u32 limit, u32 mode);
u32 sub_08045794(const struct RecordObjectWork *, struct OamEntry *, u16 index, s32 priority, u32 limit, u32 mode);
void sub_0804589C(struct RecordObjectList *, struct RecordObjectWork **entries);
void sub_080458A4(struct RecordObjectList *, struct RecordObjectWork *, s32 key);
u32 sub_080458B8(const struct RecordObjectList *, struct OamEntry *, u16 limit);
u32 sub_08045908(struct RecordObjectList *, struct OamEntry *, u16 limit);
void sub_080459A4(struct OamEntry *, u16 start, u16 end);
void sub_08045A14(struct OamEntry *objects, const u16 *parameters);
u32 sub_08045A40(s32 y, s32 x);
u32 sub_08045A60(const struct RecordObjectWork *, struct OamEntry *, u16 index, u32 unused, u32 priority, u8 mode);
void sub_08045A8C(struct RecordObjectWork *, u16 y, u16 x, u32 mode);
u32 sub_08045AEC(struct RecordObjectWork *, struct OamEntry *, u16 index, s16 y, s16 x, u16 key, u8 priority, u8 mode);
u32 sub_08045B68(struct RecordObjectWork *, struct OamEntry *, u16 index, s16 y, s16 x, u16 key, u8 priority, u8 flip, u16 scale, u16 *affine, u32 mode);
u32 sub_08045C30(struct RecordObjectWork *, struct OamEntry *, u16 index, s16 y, s16 x, u16 key, u8 priority, u16 angle, u16 *affine, u32 mode);
void sub_08045D1C(u8 *work);
u32 sub_08045D34(struct OamEntry *, const struct RecordAssetSet *, u8 palette, u32 tile);
u32 sub_08045E6C(const struct RecordAssetSet *const *, const u32 *commands, u8 selector, u8 palette, struct RecordTileBlock *records, u16 *tileBase, u32 mode);
void sub_08046034(const struct RecordAssetSet *const *, struct RecordTileBlock *, const u32 *commands, u8 selector, u8 recordIndex);
void sub_08046CC8(s32 first, s32 second, s32 third, s32 fourth);

#endif
