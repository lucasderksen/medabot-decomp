/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "compression.h"
#include "continued_late_graphics.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct Continued30E78Selected {u8 prefix[0x87];u8 selected;};
struct Continued30E78State {u8 prefix[0x9C];u8 choice;};

extern void sub_0801B274(s32);
extern void sub_0801BE48(s32);
extern void PlaySoundEffect(u32);
extern void FadeOutMusic(u32);

void sub_08030E78(void);

void sub_08030E78(void){
 struct Continued30E78Selected *work;
 LeDecompress(gMain2SharedObjectTiles_084C8034,(void *)0x06017400);
 work=(void *)gState0TransferWork.bytes;
 sub_0801BE48(work->selected);sub_0801B274(work->selected);
 ((struct Continued30E78State *)&gState0TypedWork)->choice=0;
 if(gSetupBuffer_03000590[0x40]==0){((struct Continued30E78State *)&gState0TypedWork)->choice=2;FadeOutMusic(4);PlaySoundEffect(0x6F);gNestedCallbackIndex++;}
 else if(gSetupBuffer_03000590[0x340]==0){((struct Continued30E78State *)&gState0TypedWork)->choice=1;FadeOutMusic(4);PlaySoundEffect(0x6F);gNestedCallbackIndex++;}
 else gNestedCallbackIndex=0x48;
}
