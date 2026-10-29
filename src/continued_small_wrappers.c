#include "continued_commands.h"
#include "post_dispatch.h"

extern u8 gUnknown_030057E0[];
/* Two observed word slots; copied dispatcher semantics remain provisional. */

void sub_0804C928(void) {}

void sub_0804C92C(void)
{
    sub_0804D8CC(2);
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804C94C(void)
{
    sub_08047BA8((u8)sub_0804D83C());
}

void sub_0804C960(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    sub_0804842C(1, work[0xC94]);
}

void sub_0804C984(void)
{
    sub_0804842C(2, 0);
}

void sub_0804C994(void)
{
    sub_08047BC0(120);
}

void sub_0804C9A0(void)
{
    u32 value = sub_0804D83C();
    u8 *work = gUnknown_030057E0;
    work[0xC94] = value;
    sub_0804842C(3, work[0xC94]);
}

void sub_0804C9C4(void)
{
    sub_0804842C(4, 0);
}

void sub_0804CD60(void) {}
void sub_0804CD64(void) {}

void sub_0804CD68(void)
{
    gUnknown_030057E0[0xC89] = 1;
}

void sub_0804CD7C(void) {}
void sub_0804CD80(void) {}
