#ifndef GUARD_STATE0_DISPLAY_H
#define GUARD_STATE0_DISPLAY_H

#include "render_work.h"
#include "object_helpers.h"
#include "tile_text.h"
#include "coordinate_helpers.h"
#include "equipment_helpers.h"

/* Partial observed RAM view; descriptive names are provisional. */
struct RecordDisplayWork
{
    struct RenderWork *render;
    const void *source;
    void *data;
    u8 unknown0C[0xC4];
};
extern struct RecordDisplayWork gRecordDisplayWork;
extern u8 gRecordDisplayData[];
extern u8 gRecordDisplayExtra[];
extern u8 *gRecordDisplayExtraPointer;
extern const u8 gUnknownBytes_083D1D78[];
extern const u8 gUnknownBytes_083AC5A0[18];
extern const u8 gUnknownBytes_083AC5B2[9];
extern const u8 gUnknownBytes_083AC5BB[18];
extern const u8 gUnknownBytes_083AC5CD[18];
extern const u8 gUnknownBytes_083AC5DF[36];
extern const u8 *const gUnknownPointers_083AC604[4];
extern const void *const gUnknownPointers_083B6590[];
extern u8 gUnknown_03000BAA[];
extern const u8 gUnknownBytes_084C29D8[];
extern const u8 gUnknownBytes_084C38D8[];

void ScrollBg3Diagonally2(void);
void InitMarkerOrbitObjects(void);
void StepMarkerOrbitForward(u32 index);
void LoadActiveRecordObjGraphics(void);
void PlaceNineRecordObjectGroups(void);
void sub_0800508C(void);
void DrawSelectedRecordNameText(void);
void sub_0800519C(void);
void LoadSelectedRecordTileGraphic(void);
void InitSelectedRecordPreview(void);
void sub_080053C8(void);
void sub_080054C0(void);
u32 MoveRecordSelectionByDirection(void);
void sub_08005628(void);
void StepMarkerOrbitReverse(u32 index);
void BlinkSwapMarkerObjects(void);
u32 sub_080058A4(void);
void sub_08005948(void);
void sub_0800598C(void);

/* Interfaces observed at these call sites; implementations remain copied. */
void InitRecordDisplayWork(struct RecordDisplayWork *, struct RenderWork *, const void *, void *);
void sub_08046A60(void *, struct RecordDisplayWork *, s32 index, s32 category,
                 s32 y, s32 x, u32 priority, u32 palette, u32 flags);
void sub_08046D1C(void *, struct RecordDisplayWork *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32);

#endif
