#ifndef GUARD_AUDIO_H
#define GUARD_AUDIO_H

#include "global.h"
#include "sound_voice.h"

/* Select sixteen waveform bytes; the original caller lookup is unchecked. */
void sub_08073A48(s32 waveform);

/* Update one hardware channel's routing bits. */
void sub_08073604(void *channel);

/* Reset the observed fields of an audio channel (at least 0x70 bytes). */
void sub_0807490C(void *channel);

/* Refresh alternate channels or the requested channel; observed caller uses slot 12. */
void sub_0807462C(s32 slot);

/* Consume the following byte from the channel command cursor. */
void sub_08072AC0(void *channel);

/* The parameter's low byte is stored at channel offset 0x69. */
void sub_08072B20(void *channel, u32 value);

/* Process one command from the secondary channel cursor. */
void sub_08072F7C(void *channel);

/* Update the wave-channel pitch/status halfword when the pending flag is set. */
void sub_08073480(void *channel, volatile u16 *output);

/* Select a stream from the initialized 22-entry bank using the note's low byte. */
void sub_080728A0(void *channel, u32 note);

void InitAudio(void *context);
void Dma1AudioHandler(void);
void Dma2AudioHandler(void);

#endif
