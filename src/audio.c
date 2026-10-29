#include "audio.h"
#include "sound_work.h"
#include "sound_samples.h"

/* Install the reviewed music, effect, PCM and auxiliary-command banks. */
extern void sub_080723AC(void *context);
extern void sub_08074B88(u32 value);
extern void sub_08074090(void);
extern void sub_080740D4(void);


/* 0x0800058C; context arrives from GameMain at 0x03002430. */
void InitAudio(void *context)
{
    sub_080723AC(context);
    sub_08074A78(gSoundMusicBank);
    sub_08074D3C(gSoundEffectBank);
    sub_08074FE8(&gSoundAuxBank);
    sub_08073C5C(gSoundPcmInstruments);
    sub_08073C70(gSoundPcmDrums);
    sub_08074B88(0);
}

/* 0x0800099C; installed in the DMA1 slot of the game's interrupt table. */
void Dma1AudioHandler(void)
{
    sub_08074090();
}

/* 0x080009A8; installed in the DMA2 slot of the game's interrupt table. */
void Dma2AudioHandler(void)
{
    sub_080740D4();
}
