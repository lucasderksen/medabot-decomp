extern u8 gUnknown_02023078;

void sub_0805B984(void)
{
    if (((u8 *)gMainContextPointer_03006F74)[0x20] > 4) {
        if (gUnknown_02023078 != 0 && (gFrameCounter & 8))
            gFrameObjects[0x68].flags = 0x4000 | gFrameObjects[0x68].flags;
        else
            gFrameObjects[0x68].flags &= ~0x4000;
        if (*(u8 *)0x02023078 + 3 != ((u8 *)gMainContextPointer_03006F74)[0x20] - 1 && (gFrameCounter & 8))
            gFrameObjects[0x69].flags |= 0x4000;
        else
            gFrameObjects[0x69].flags &= ~0x4000;
    }
}
