struct ContinuedWorkC48
{
    u8 unknown000[0xC48];
    u16 cameraX;
    u16 cameraY;
};
extern struct ContinuedWorkC48 gContinuedWork_030057E0;

void sub_08052784(void)
{
    s32 i;
    s32 k;

    i = 0x31;
    for (k = 0; k < 36; k++, i++) {
        s32 visible;
        struct FrameObject *obj;

        if (((u16 *)gLaterBuffer_030055A0)[i * 2] == 0)
            continue;
        obj = &gFrameObjects[i];
        visible = 0;
        if ((s16)gBgScroll1.y < (obj->positionY >> 8) - gContinuedWork_030057E0.cameraY + 16
         && (obj->positionY >> 8) - gContinuedWork_030057E0.cameraY < (s16)gBgScroll1.y + 0xA8
         && (s16)gBgScroll1.x < (obj->positionX.value >> 8) - gContinuedWork_030057E0.cameraX + 16
         && (obj->positionX.value >> 8) - gContinuedWork_030057E0.cameraX < (s16)gBgScroll1.x + 0xF0)
            visible = 1;
        if (visible) {
            struct FrameObject *o = &gFrameObjects[i];
            if (o->unknown2C[1] != 1) {
                o->flags = o->value32;
                o->unknown2C[2] = 1;
                o->screenX = (o->positionX.value >> 8) - gBgScroll1.x;
                o->screenY = (o->positionY >> 8) - gBgScroll1.y;
                if (gObjectAuxiliaryLookup_083D2D0D[(u16)o->value30]) {
                    gFrameObjects[i + 0x2A].flags = 0xCC0C;
                    gFrameObjects[i + 0x2A].screenX = o->screenX;
                    gFrameObjects[i + 0x2A].screenY = (u16)(o->unknown2C[0] - 5) + o->screenY;
                } else {
                    gFrameObjects[i + 0x2A].flags = 0;
                }
            } else {
                o->flags = 0;
                o->unknown2C[2] = 0;
                gFrameObjects[i + 0x2A].flags = 0;
            }
        } else {
            do {
            gFrameObjects[i].flags = 0;
            gFrameObjects[i].unknown2C[2] = 0;
            gFrameObjects[i + 0x2A].flags = 0;
            } while (0);
        }
    }
}
