#include "global.h"
#include "continued_commands.h"

extern u8 gUnknown_030057E0[];

#define DEFAULT_ACTION(name) \
void name(void) \
{ \
    u8 *work; \
    sub_0804D8CC(2); \
    work = gUnknown_030057E0; \
    if (work[0xC95] == 0) work[0xC95] = 1; \
    work[0xC89] = 1; \
}
DEFAULT_ACTION(sub_0804C648)
DEFAULT_ACTION(sub_0804C678)

#define COMPLETE_ACTION(name, count) \
void name(void) \
{ \
    sub_0804D8CC(count); \
    gUnknown_030057E0[0xC89] = 1; \
}
COMPLETE_ACTION(sub_0804C6A8, 3)
COMPLETE_ACTION(sub_0804C6C8, 3)
COMPLETE_ACTION(sub_0804C6E8, 2)
COMPLETE_ACTION(sub_0804C708, 2)

#define MARK_ACTION(name) \
void name(void) \
{ \
    u32 value = sub_0804D83C(); \
    u8 *work = gUnknown_030057E0; \
    work[0xC94] = value; \
    work[0xC89] = 1; \
}
MARK_ACTION(sub_0804C728)
MARK_ACTION(sub_0804C750)
MARK_ACTION(sub_0804C840)
