extern u16 gUnknown_0202FE00[];
extern u16 *gPalettePointer71FF80300700C;
extern void sub_0806B718(u8);
struct DmaRegs72080 { u32 source, destination, control; };
s32 sub_08072080(void) {
    u8 k;
    u8 inv;
    s32 i;
    u16 c;
    if (gCounter6ED08_03001800.pad00[0x11] > 0x40) {
        sub_08074DE0(0xA);
        gCounter6ED08_03001800.pad00[0x10]++;
    } else {
        if (gCounter6ED08_03001800.pad00[0x11] <= 0x1F)
            k = 0x20 - gCounter6ED08_03001800.pad00[0x11];
        else
            k = gCounter6ED08_03001800.pad00[0x11] - 0x20;
        if (gCounter6ED08_03001800.pad00[0x11] == 0x20)
            sub_0806B718(0);
        if (gCounter6ED08_03001800.pad00[0x11] == 0x14)
            sub_08074DE0(0x51);
        inv = 0x20 - k;
        for (i = 0; i <= 0xFF; i++) {
            gUnknown_0202FE00[i] = (((0x1F & gPalettePointer71FF80300700C[i]) * k + 0x1F * inv) >> 5)
                + ((((0x3E0 & gPalettePointer71FF80300700C[i]) * k + 0x3E0 * inv) >> 5) & 0x3E0)
                + ((((0x7C00 & gPalettePointer71FF80300700C[i]) * k + 0x7C00 * inv) >> 5) & 0x7C00);
        }
        {
            volatile struct DmaRegs72080 *dma = (void *)0x040000D4;
            dma->source = (u32)gUnknown_0202FE00;
            dma->destination = 0x05000200;
            dma->control = 0x84000080;
            (void)dma->control;
        }
    }
    if (gFrameCounter & 1)
        gCounter6ED08_03001800.pad00[0x11]++;
    return 0;
}
