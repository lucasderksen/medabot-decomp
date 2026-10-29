#ifndef GUARD_STATE0_INVENTORY_H
#define GUARD_STATE0_INVENTORY_H

#include "global.h"
#include "object_helpers.h"
#include "tile_text.h"
#include "coordinate_helpers.h"
#include "equipment_helpers.h"

/* Accessed bytes and the 64-byte stride are observed; broader roles are provisional. */
struct InventoryRecord { u8 byte0; u8 byte1; u8 unknown02[3]; u8 byte5; u8 unknown06[58]; };
extern struct InventoryRecord gInventoryRecords[30];
extern u8 gInventoryNames[30][64]; /* Aliases the record base plus ten bytes. */
extern const void *const gPartTextPointers_083BBB4C[480];
extern const u8 gInventoryMetadata_083B62D8[];

void sub_080059D0(void);
void sub_08005AD0(void);
void sub_08005B44(void);
void sub_08005BB4(void);
void sub_08005C10(void);
void sub_08005C9C(void);
void sub_08005D1C(void);
void sub_08005E00(void);
void sub_08005E84(void);
void sub_08005F68(void);
void sub_08005FEC(void);
void sub_080060D0(void);
void sub_08006154(void);

void sub_08006238(u32);
void sub_08006284(u32);
void sub_080062D0(u32);
void sub_0800631C(u32);
void sub_08006368(u32);
void sub_080063B4(void);
void sub_08006414(void);
void sub_08006444(void);
void sub_08006494(void);
void sub_08006514(void);
void sub_0800656C(void);
void sub_0800667C(void);
void sub_08006764(void);
void sub_08006824(void);
u32 sub_080068EC(void);
u32 sub_08006980(void);
u32 sub_08006A00(void);
u32 sub_08006A98(void);
u32 sub_08006B30(void);
u32 sub_08006BC8(void);

u32 sub_08006C64(void);
u32 sub_08006E08(u32 part);
void sub_08006E44(void);
void sub_08006F14(void);
void sub_08006FB0(void);
void sub_080070F0(void);

/* Call-site interfaces; these implementations remain copied. */

u32 sub_0804361C(u32,u32);
u32 sub_080436AC(u32,u32,u32,u32);

#endif
