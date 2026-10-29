void sub_080697B4(u8 selector, u8 x, u8 y) {
    u8 widths[8];
    u8 heights[8];
    u16 offsets[8];
    struct LinkTilePatternPointers patterns;
    u16 bases[8];
    u16 tile;
    s32 row;
    s32 column;
    u32 source;
    u32 mode;
    u32 vram;
    memcpy(widths, gLinkTileWidths, 8);
    memcpy(heights, gLinkTileHeights, 8);
    memcpy(offsets, gLinkTileOffsets, 16);
    patterns = gLinkTilePatterns;
    memcpy(bases, gLinkTileBases, 16);
    mode = selector & 7;
    source = (u32)patterns.items[mode];
    for (row = 0; row < heights[mode]; row++) {
        u32 position = (u32)x << 16;
        for (column = 0; column < widths[mode]; column++) {
            u32 value;
            volatile struct DmaTransfer *dma = (volatile struct DmaTransfer *)0x040000D4;
            if (mode > 4) value = row * 6 + column + offsets[mode];
            else value = offsets[mode] + *(const u16 *)source;
            tile = bases[mode] + value;
            if (mode <= 3) {
                dma->source = &tile;
                vram = (position >> 16) * 2 + 0x0600F800;
            } else {
                dma->source = &tile;
                vram = (position >> 16) * 2 + 0x0600E800;
            }
            dma->destination = (void *)(((u32)(u16)(row + y) << 6) + vram);
            dma->control = 0x80000001;
            (void)dma->control;
            source += 2;
            position += 0x10000;
        }
    }
}
