#ifndef GUARD_OBJECT_HELPERS_H
#define GUARD_OBJECT_HELPERS_H

#include "global.h"

typedef void (*ObjectHelperCallback)(void);

struct ObjectSortEntry { u16 key, tie, word4, word6; };
extern struct ObjectSortEntry gObjectSortEntries[];
/* Constant-address view of gObjectSortEntries; the bubble sorts reload this
 * base in every inner iteration, which the symbol form does not (CSE/loop hoist). */
#define OBJECT_SORT_ENTRIES ((struct ObjectSortEntry *)0x02023000)
extern u16 gObjectFourthKey;
extern u8 gObjectCountPairs[64][2];

/* Callback counts are physical storage bounds, not runtime index clamps. */
extern u8 gObjectParameterWork[8];
extern const ObjectHelperCallback gObjectCallbacks_083B2994[14];
extern const ObjectHelperCallback gObjectCallbacks_083B29CC[6];
extern const ObjectHelperCallback gObjectCallbacks_083B29E4[2];
extern u8 gObjectHalfwordBytes[];
extern const u8 gUnknownBytes_08487388[];
extern const u8 gUnknownBytes_08487408[];
extern const u8 gUnknownBytes_084C88B8[];
extern const u8 gUnknownBytes_0848816C[];
extern const u8 gUnknownBytes_084881B4[];
extern const u16 gUnknownWords_084E43F8[];

void sub_080415BC(void);
void sub_080415E8(u8 first, u8 second, u8 third);
void sub_08041624(u8 first, u8 second, u8 third, u8 fourth);
u32 sub_08041674(void);
void sub_0804169C(void);
void sub_0804172C(void);
void sub_0804177C(void);
void sub_08041818(void);
void sub_080418C0(void);
void sub_08041920(void);
void sub_080419CC(void);
void sub_08041BA4(void);
void sub_08041BF4(void);
void sub_08041C14(u8 index, u8 operation, u16 value);
void sub_08041C5C(u8 index, u8 operation, u16 value);
u32 sub_08041CA4(void);
u32 sub_08041CD4(void);
void sub_08041D04(const u8 *source, u8 *destination, u8 size);
void sub_08041D28(void);
u32 sub_08041D3C(u8 identifier);
void sub_08041FE4(u8 identifier);
s32 sub_0804206C(void);
u32 sub_080420C4(u8 value, u8 first, u8 second, u8 third, u8 fourth);
u32 sub_08042114(u8 index, u8 row);
void sub_0804213C(u8 index, u8 row, u8 increment);
void sub_08042170(u8 index, u8 row, u8 decrement);
void sub_080421A0(void);
u32 sub_08042218(void);
u32 sub_08042278(u8 input);
void sub_0804242C(u8 count);
void sub_0804253C(u8 mode, u16 control, u16 duration);
/* Requires a mode of 1..6 previously configured by sub_0804253C. */
u32 sub_080425DC(void);

void sub_08042318(u8 kind, u8 amount);
#endif
