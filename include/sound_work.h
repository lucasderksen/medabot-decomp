#ifndef GUARD_SOUND_WORK_H
#define GUARD_SOUND_WORK_H

#include "global.h"
#include "sound_voice.h"

struct SoundSampleHeader;
struct SoundAuxBank;

/* Shared partial sound-work layout; channel records have a 0x74-byte stride. */
struct SoundChannelState {
    s32 position;
    s32 counter;
    void *queue;              /* 08; three 0x34-byte queues begin at root + 5EC */
    u32 refreshAddress;       /* 0C; Thumb callback address */
    u32 updateAddress;        /* 10; Thumb callback address */
    void *track;
    s32 words18[7];
    s32 word34;
    s32 word38;
    s32 word3C;
    u16 half40;
    u16 half42;
    u16 half44;
    u16 unknown46;
    u16 half48;
    s16 envelope;
    u16 half4C;
    u16 song;
    u8 flags;
    u8 unknown51;
    u8 byte52;
    u8 byte53;
    u8 byte54;
    u8 byte55;
    u8 byte56;
    u8 byte57;
    u8 byte58;
    u8 byte59;
    u8 byte5A;
    u8 unknown5B[7];
    u8 byte62;
    u8 byte63;
    u8 type;
    u8 byte65;
    u8 byte66;
    u8 byte67;
    u8 byte68;
    u8 byte69;
    u8 byte6A;
    u8 byte6B;
    u8 lastNote;
    u8 priority;
    u8 byte6E;
    u8 byte6F;
    u8 parameter;
    u8 unknown71[3];
};
/* A header is followed by one word-sized stream pointer per selected channel. */
struct SoundSongHeader
{
    u16 channelMask;
    u8 priority;
    u8 unknown03;
};

struct SoundRootState {
    struct SoundChannelState channels[13];
    u8 unknown5E4[0x688 - 0x5E4];
    const struct SoundSongHeader *const *music;
    const struct SoundSongHeader *const *effects;
    struct SoundVoiceState waveA;
    struct SoundVoiceState waveB;
    const struct SoundSampleHeader *const *instruments;
    const struct SoundSampleHeader *const *drums;
    const struct SoundAuxBank *aux;
    u8 flags;
    u8 unknown72D[2];
    u8 songIndex;
};


struct SoundTrackInit {
    u32 refreshAddress;
    u32 updateAddress;
    u8 kind;
    u8 queueIndex;
    u8 unknown0A[2];
};

extern const struct SoundTrackInit gSoundTrackInitializers[13];
extern const struct SoundSongHeader *const gSoundMusicBank[54];
extern const struct SoundSongHeader *const gSoundEffectBank[128];
extern struct SoundRootState *gFamilySoundRoot74028;

void sub_08073C5C(const struct SoundSampleHeader *const *bank);
void sub_08073C70(const struct SoundSampleHeader *const *bank);
void sub_08074A78(const struct SoundSongHeader *const *bank);
void sub_08074D3C(const struct SoundSongHeader *const *bank);
void sub_08074FE8(const struct SoundAuxBank *bank);
void sub_080741F4(void *record);
void sub_0807455C(struct SoundChannelState *channel, void *track);
void sub_08074A04(void);
void sub_08074A8C(u32 song, u32 parameter);
void sub_08074D50(u32 song, u32 parameter);
struct SoundRootState *sub_08075244(void);

typedef char SoundChannelSize[(sizeof(struct SoundChannelState) == 0x74) ? 1 : -1];
typedef char SoundTrackInitSize[(sizeof(struct SoundTrackInit) == 12) ? 1 : -1];

#endif
