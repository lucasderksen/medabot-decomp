struct HeldKeys1CB8 {
    u8 low:4;
    u8 right:1;
    u8 left:1;
    u8 up:1;
    u8 down:1;
    u8 rest:8;
    u16 rest2;
};
extern struct HeldKeys1CB8 gHeldKeys1CB8 asm("gContinuedByte_03002B64");
extern u8 gWork1CB8[] asm("gContinuedWork_030057E0");
s32 sub_0807CD2C(s32, s32);

void sub_08051CB8(void)
{
    u8 direction = 0;
    u32 keys;
    struct HeldKeys1CB8 held;

    if (gWork1CB8[0xC58] == 0) {
        held = gHeldKeys1CB8;
        if ((held.down | held.up | held.left | held.right) == 0)
            return;
        keys = held.down << 3;
        keys = keys | (held.up << 2) | (held.left << 1) | held.right;
        if (gWork1CB8[0xC88] == 0 && gWork1CB8[0x7FE] == 0x53)
            keys = (u8)sub_08051C64(keys);
        do switch (keys) {
        case 4:
            direction = 0;
            break;
        case 8:
            direction = 1;
            break;
        case 1:
            direction = 3;
            break;
        case 5:
            direction = 3;
            break;
        case 9:
            direction = 3;
            break;
        case 2:
            direction = 2;
            break;
        case 6:
            direction = 2;
            break;
        case 10:
            direction = 2;
            break;
        } while (0);
        if (gWork1CB8[0xC59] != direction) {
            gWork1CB8[0xC59] = direction;
            sub_08052E0C(direction);
            sub_08049420(0x2F, direction);
            sub_08051EFC(3);
        }
        if (sub_08052CC0(direction) == 0 && sub_080525BC(direction) == 0) {
            gWork1CB8[0xC58] = sub_0807CD2C(0x10, sub_08051940(0x2F));
            sub_08051988(gWork1CB8[0xC59]);
            sub_08051EFC(3);
            if (gWork1CB8[0xC5C] == 2 || gWork1CB8[0xC5C] == 9)
                sub_08047BA8(0x57);
            sub_0805203C(gWork1CB8[0xC75]);
        }
    } else {
        sub_08051988(gWork1CB8[0xC59]);
        sub_0805203C(gWork1CB8[0xC75]);
    }
}
