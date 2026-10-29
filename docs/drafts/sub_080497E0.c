struct BlendWork7E0 {
    u8 control;
    u8 type;
    u8 active;
    u8 byte3;
    u8 byte4;
    u8 byte5;
    u8 first;
    u8 second;
    u8 third;
    u8 currentFirst;
    u8 currentSecond;
    float valueFirst;
    float valueSecond;
    float elapsed;
    float stepFirst;
    float stepSecond;
};
extern struct BlendWork7E0 gBlendSetupWork_03006F40;
void sub_080497E0(u8 control, u16 targets, u8 type, u8 frames, u8 frames2, u8 frames3, u8 first, u8 second, u8 third)
{
    if (frames == 0)
        frames = 1;
    if (frames2 == 0)
        frames2 = 1;
    /* the third frame count is defaulted like the others but never read */
    if (frames3 == 0)
        frames3 = 1;
    gBlendSetupWork_03006F40.control = control;
    gBlendSetupWork_03006F40.type = type;
    gBlendSetupWork_03006F40.elapsed = 0.0f;
    gBlendSetupWork_03006F40.active = 1;
    if (control & 0x80)
        targets |= 0x20;
    else
        targets &= 0xFFDF;
    switch (gBlendSetupWork_03006F40.type) {
    case 0:
    case 2:
        gBlendSetupWork_03006F40.byte5 = 0x10;
        break;
    case 1:
    case 3:
        gBlendSetupWork_03006F40.byte5 = 0x10;
        break;
    case 4:
        gBlendSetupWork_03006F40.first = *(volatile u16 *)0x04000052 & 0x1F;
        gBlendSetupWork_03006F40.second = (*(volatile u16 *)0x04000052 & 0x1F00) >> 8;
        gBlendSetupWork_03006F40.third = *(volatile u16 *)0x04000054 & 0x1F;
        gBlendSetupWork_03006F40.valueFirst = 0.0f;
        gBlendSetupWork_03006F40.valueSecond = 0.0f;
        gBlendSetupWork_03006F40.stepFirst = (0x10 - gBlendSetupWork_03006F40.first) / (float)frames;
        gBlendSetupWork_03006F40.stepSecond = (0x10 - gBlendSetupWork_03006F40.second) / (float)frames2;
        break;
    case 5:
        gBlendSetupWork_03006F40.first = first;
        gBlendSetupWork_03006F40.second = second;
        gBlendSetupWork_03006F40.third = third;
        gBlendSetupWork_03006F40.valueFirst = 0.0f;
        gBlendSetupWork_03006F40.valueSecond = 0.0f;
        gBlendSetupWork_03006F40.stepFirst = (0x10 - first) / (float)frames;
        gBlendSetupWork_03006F40.stepSecond = (0x10 - second) / (float)frames2;
        gBlendSetupWork_03006F40.byte3 = 0x10;
        gBlendSetupWork_03006F40.byte4 = 0x10;
        gUnknownCallback_030017F0 = sub_08049CC8;
        break;
    case 6:
        gBlendSetupWork_03006F40.currentFirst = *(volatile u16 *)0x04000052 & 0x1F;
        gBlendSetupWork_03006F40.currentSecond = (*(volatile u16 *)0x04000052 & 0x1F00) >> 8;
        gBlendSetupWork_03006F40.first = first;
        gBlendSetupWork_03006F40.second = second;
        gBlendSetupWork_03006F40.third = third;
        gBlendSetupWork_03006F40.valueFirst = 0.0f;
        gBlendSetupWork_03006F40.valueSecond = 0.0f;
        gBlendSetupWork_03006F40.stepFirst = (gBlendSetupWork_03006F40.currentFirst - first) / (float)frames;
        gBlendSetupWork_03006F40.stepSecond = (gBlendSetupWork_03006F40.currentSecond - second) / (float)frames2;
        break;
    default:
        gBlendSetupWork_03006F40.byte5 = 0;
        break;
    }
    *(volatile u16 *)0x04000050 = targets | control;
}
