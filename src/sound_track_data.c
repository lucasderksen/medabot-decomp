#include "sound_work.h"

extern void sub_080746C0(void);
extern void sub_080746E0(void);
extern void sub_08074704(void);
extern void sub_08074728(void);
extern void sub_0807474C(void);
extern void sub_08074780(void);
extern void sub_080747B8(void);
extern void sub_080747F4(void);
extern void sub_08074834(void);
extern void sub_0807485C(void);
extern void sub_08074890(void);
extern void sub_080748B8(void);
extern void sub_080748E8(void);
extern void sub_08072FF4(s32 channel);
extern void sub_08073010(void *channel);
extern void sub_08073044(s32 channel);

const struct SoundTrackInit gSoundTrackInitializers[13] = {
    { (u32)sub_080746C0, (u32)sub_08072FF4, 0, 0, {0, 0} },
    { (u32)sub_080746E0, (u32)sub_08072FF4, 1, 1, {0, 0} },
    { (u32)sub_08074704, (u32)sub_08072FF4, 2, 2, {0, 0} },
    { (u32)sub_08074728, (u32)sub_08073010, 3, 0xFF, {0, 0} },
    { (u32)sub_0807474C, (u32)sub_08072FF4, 0, 0xFF, {0, 0} },
    { (u32)sub_08074780, (u32)sub_08072FF4, 1, 0xFF, {0, 0} },
    { (u32)sub_080747B8, (u32)sub_08072FF4, 2, 0xFF, {0, 0} },
    { (u32)sub_080747F4, (u32)sub_08073010, 3, 0xFF, {0, 0} },
    { (u32)sub_08074834, (u32)sub_08073044, 4, 0xFF, {0, 0} },
    { (u32)sub_0807485C, (u32)sub_08073044, 5, 0xFF, {0, 0} },
    { (u32)sub_08074890, (u32)sub_08073044, 4, 0xFF, {0, 0} },
    { (u32)sub_080748B8, (u32)sub_08073044, 5, 0xFF, {0, 0} },
    { (u32)sub_080748E8, (u32)sub_08073010, 3, 0xFF, {0, 0} }
};
