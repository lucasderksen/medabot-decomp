#ifndef GUARD_EQUIPMENT_HELPERS_H
#define GUARD_EQUIPMENT_HELPERS_H
#include "global.h"
#include "encounter_records.h"
void sub_08043560(u32 index, u32 row, u32 byteOffset, u32 subtract, u32 amount);
void sub_080435B0(u32 value, u32 x, u32 y, u32 control, u16 entry);
u32 sub_08043814(u8 record, u8 first, u8 second, u8 third, u8 fourth);
u32 sub_0804384C(u8 record);
extern const u8 *const gEquipmentAssets_083B2578[];
extern const u8 *const gEquipmentAssets_083B2628[];
extern u16 gEquipmentPaletteShadow[];
extern const u8 gEquipmentTable_083C3CDC[][8];
extern const u8 gEquipmentWidths_083C4238[11];
extern const u8 gEquipmentFrames_083C4243[11][128];
extern u8 gEquipmentTiles_02027000[];
u32 sub_080424B8(void);
void sub_08043CD4(void);
void sub_08043E78(void);
void sub_08043B58(void);
void sub_08043B7C(u32 index, u32 shadowPalette);
void sub_08043C08(u32 index, u32 shadowPalette);
s32 sub_08043C94(void);
void sub_08043CA8(void);
void sub_08043DF8(void);
void sub_08043E48(void);
void sub_08043E54(void);
void sub_08043F9C(void);
void sub_08043FEC(u32 index);
void sub_0804387C(void);
void sub_08043AE0(void);

#endif
