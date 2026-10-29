/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "frame.h"
#include "record_helpers.h"
#include "state0_work.h"

#include "sound_work.h"

extern struct SoundRootState *gFamilySoundRoot74028;
extern void sub_080736A0(struct SoundChannelState *);
extern void sub_08073718(struct SoundChannelState *);
extern void sub_08073784(struct SoundChannelState *);
extern void sub_080737E8(struct SoundChannelState *);
extern void sub_08073E1C(void *);
extern void sub_08073F90(void *);
extern void sub_08073FB8(void *);
extern void sub_080741F4(void *record);
extern void sub_0807495C(struct SoundChannelState *);
extern void sub_08074978(struct SoundChannelState *channel);

void sub_08074288(s32 pause);
void sub_0807455C(struct SoundChannelState *channel, void *track);

void sub_08074288(s32 pause) {

    struct SoundRootState **rootp = &gFamilySoundRoot74028;

    if (pause != 0) {
        (*rootp)->flags |= 2;
        *(volatile u16 *)0x04000062 &= 0xFFF;
        *(volatile u16 *)0x04000064 |= 0x8000;
        *(volatile u16 *)0x04000068 &= 0xFFF;
        *(volatile u16 *)0x0400006C |= 0x8000;
        *(volatile u16 *)0x04000072 &= 0x1FFF;
        *(volatile u16 *)0x04000078 &= 0xFFF;
        *(volatile u16 *)0x0400007C |= 0x8000;
        if ((*rootp)->channels[10].track != 0)
            sub_08073E1C(&(*rootp)->waveA);
        else if ((*rootp)->channels[8].track != 0)
            sub_08073FB8(&(*rootp)->waveA);
        if (gFamilySoundRoot74028->channels[11].track != 0)
            sub_08073E1C(&gFamilySoundRoot74028->waveB);
        else if (gFamilySoundRoot74028->channels[9].track != 0)
            sub_08073FB8(&gFamilySoundRoot74028->waveB);
        sub_0807495C(&gFamilySoundRoot74028->channels[4]);
        sub_0807495C(&gFamilySoundRoot74028->channels[5]);
        sub_0807495C(&gFamilySoundRoot74028->channels[6]);
        sub_0807495C(&gFamilySoundRoot74028->channels[7]);
        sub_0807495C(&gFamilySoundRoot74028->channels[10]);
        sub_0807495C(&gFamilySoundRoot74028->channels[11]);
    } else {
        (*rootp)->flags &= 0xFD;
        if ((*rootp)->channels[4].track == 0 && (*rootp)->channels[0].track != 0) {
            (*rootp)->channels[0].flags |= 0x5F;
            sub_080736A0(&(*rootp)->channels[0]);
        }
        if (gFamilySoundRoot74028->channels[5].track == 0 && gFamilySoundRoot74028->channels[1].track != 0) {
            gFamilySoundRoot74028->channels[1].flags |= 0x5F;
            sub_08073718(&gFamilySoundRoot74028->channels[1]);
        }
        if (gFamilySoundRoot74028->channels[6].track == 0 && gFamilySoundRoot74028->channels[2].track != 0) {
            gFamilySoundRoot74028->channels[2].flags |= 0x7F;
            sub_08073784(&gFamilySoundRoot74028->channels[2]);
        }
        if (gFamilySoundRoot74028->channels[7].track == 0 && gFamilySoundRoot74028->channels[3].track != 0) {
            gFamilySoundRoot74028->channels[3].flags |= 0x5F;
            sub_080737E8(&gFamilySoundRoot74028->channels[3]);
        }
        if (gFamilySoundRoot74028->channels[10].track == 0 && gFamilySoundRoot74028->channels[8].track != 0) {
            sub_08073F90(&gFamilySoundRoot74028->waveA);
            gFamilySoundRoot74028->channels[8].flags = 0;
        }
        if (gFamilySoundRoot74028->channels[11].track == 0 && gFamilySoundRoot74028->channels[9].track != 0) {
            sub_08073F90(&gFamilySoundRoot74028->waveB);
            gFamilySoundRoot74028->channels[9].flags = 0;
        }
    }
}

void sub_0807455C(struct SoundChannelState *channel, void *track) {

    sub_080741F4(channel);
    channel->track = track;
    channel->words18[0] = 0;
    channel->words18[1] = 0;
    channel->words18[2] = 0;
    channel->words18[3] = 0;
    channel->words18[4] = 0;
    channel->words18[5] = 0;
    channel->words18[6] = 0;
    channel->flags = 0x5F;
    channel->byte52 = 0;
    channel->byte53 = 0;
    channel->byte54 = 8;
    channel->byte55 = 0;
    channel->byte56 = 0;
    channel->byte57 = 0;
    channel->byte58 = 0;
    channel->byte59 = 0;
    channel->byte5A = 0;
    channel->word34 = 0;
    channel->word38 = 0;
    channel->byte63 = 0;
    channel->half48 = 0xFF;
    channel->byte65 = 0xF;
    channel->byte66 = 0;
    channel->byte67 = 0;
    channel->byte68 = 0;
    channel->byte69 = 0;
    channel->byte6A = 0;
    channel->byte6B = 0;
    channel->lastNote = 0xFF;
    channel->byte62 = 0;
    channel->priority = 0;
    channel->byte6E = 0;
    channel->half40 = 0x1000;
    channel->half42 = 0x1000;
    channel->half44 = 0;
    channel->word3C = 0;
    channel->byte6F = 3;
    channel->parameter = 0;
    channel->half4C = 0;
    channel->song = 0xFFFF;
    sub_08074978(channel);
}
