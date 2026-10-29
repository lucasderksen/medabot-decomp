extern u8 sub_0807CEC8(u8 numerator, s32 denominator);
extern u8 sub_0807CF40(u8 numerator, s32 denominator);

void sub_0805E334(u8 *name)
{
    u16 *top;
    u16 *bottom;
    s32 i;
    u16 value;
    u8 code;
    u32 block;
    u8 column;
    u8 row;

    top = (u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x060000CA);
    bottom = (u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + 0x0600010A);
    for (i = 0; i < 10; i++)
    {
        code = *name;
        value = code;
        if (value != 0)
        {
            code--;
            block = (*(volatile u16 *)0x0400000A >> 8) & 0x1F;
            column = sub_0807CF40(code, 26);
            row = sub_0807CEC8(code, 26);
            *top++ = *(u16 *)((block << 11) + column * 2 + row * 0xC0 + 0x06000204);
            value = *(u16 *)((((*(volatile u16 *)0x0400000A >> 8) & 0x1F) << 11) + column * 2 + row * 0xC0 + 0x06000244);
        }
        else
        {
            *top++ = value;
        }
        *bottom++ = value;
        name++;
    }
}
