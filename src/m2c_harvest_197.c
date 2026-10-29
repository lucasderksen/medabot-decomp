/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "display_effects.h"
#include "effect_work.h"
#include "frame.h"
#include "main_callbacks.h"
#include "state0_callbacks.h"
#include "state0_next_helpers.h"
#include "state0_work.h"

struct EncounterChoice6A3C4 {s16 field0; s16 field2; s16 field4; s16 field6; s16 field8; s16 fieldA;};

extern const struct EncounterChoice6A3C4 gEncounterChoiceTable08485C00[];
extern const void *const gScriptTable08485F88[31];
extern s32 gUnknown_03006F88;
extern u8 gSelectionOrder03006F94[3];
extern u8 gUnknown_03006FDC;
extern void sub_0806941C(u8);
extern void sub_08069DF0(void);
extern void sub_08069EDC(void);
extern void sub_08069F44(void);
extern void sub_0806A078(u8 *,const u8 *);
extern void sub_0806B0D4(void);
extern void sub_0806B4C8(void);
extern void sub_0806B530(u8,u8,u8,u8);

void sub_080212A0(void);
s32 sub_0806A3C4(void);

void sub_080212A0(void) {
 if (gFrameObjects[0x21].unknown23[4]==16) gState0TransferWork.bytes[0xAA]++;
 else {
  if (!(gState0TransferWork.bytes[0xF8]&1)) gFrameObjects[0x21].screenX=(u16)gFrameObjects[0x21].screenX+1;
  else gFrameObjects[0x21].screenX=(u16)gFrameObjects[0x21].screenX-1;
  gFrameObjects[0x21].unknown23[4]++;
 }
}

s32 sub_0806A3C4(void) {
 const void *script;
 const u8 *encounterRecord;
 switch(gUnknown_03006F88) {
 case 0:
        sub_0803FAA0(1U, 2U, 0U);
        sub_08069DF0();
        sub_08074DE0(0x15U);
        if(gSelectionOrder03006F94[0]==1) {
            sub_0806B530(0, 1, 0x18, 0x58);
            sub_0806A078(gDebugMenuTextBuffer, gUnknown_03002B74);
        } else if(gSelectionOrder03006F94[0]==2) {
            sub_0806B530(0, 1, 0x58, 0x58);
            encounterRecord=gState0EncounterRecords_083C1B80[gEncounterChoiceTable08485C00[gUnknown_03006FDC].field2];
            sub_0806A078(gDebugMenuTextBuffer,gState0EncounterLabels_083C40B8[*encounterRecord]);
        } else if(gSelectionOrder03006F94[0]==3) {
            sub_0806B530(0, 1, 0x98, 0x58);
            encounterRecord=gState0EncounterRecords_083C1B80[gEncounterChoiceTable08485C00[gUnknown_03006FDC].field6];
            sub_0806A078(gDebugMenuTextBuffer,gState0EncounterLabels_083C40B8[*encounterRecord]);
        }
        *(volatile u16 *)0x04000000 |= 0x400;
        gUnknown_03006F88 += 1;
 return 0;
 case 6 ... 13:
 if(gUnknown_03006F88==6) {
                    sub_08069F44();
                    sub_0806B530(4, 7, 2, 0);
                    gFrameObjects[4].screenX = ((gSelectionOrder03006F94[2] - 1) * 64) + 0x38;
                    gFrameObjects[4].screenY = 0x18;
                    sub_0806B530(3, 7, 1, 0);
                    gFrameObjects[3].screenX = ((gSelectionOrder03006F94[1] - 1) * 64) + 0x38;
                    gFrameObjects[3].screenY = 0x18;
                    sub_0806B530(2, 7, 0, 0);
                    gFrameObjects[2].screenX = ((gSelectionOrder03006F94[0] - 1) * 64) + 0x38;
                    gFrameObjects[2].screenY = 0x18;
 }
 sub_0806941C((u8)(gUnknown_03006F88-6));
 default:
 sub_0803FB3C(gScriptTable08485F88[30]);
 gUnknown_03006F88++;
 break;
 case 0x96:
        sub_08074DE0(0x16U);
        *(volatile u16 *)0x04000050 = 0x7F;
        sub_08069EDC();
        sub_0806B530(1, 6, 0, 0);
        gFrameObjects[1].screenX = ((gSelectionOrder03006F94[0] - 1) * 64) + 0x18;
        sub_0803FB0C();
 gUnknown_03006F88++;
 break;
 case 0x97:
        if ((sub_0803FB3C(gScriptTable08485F88[7]) != 0) && (gFrameObjects[1].commandDelay == 0)) {
            sub_0803FB0C();
            if (gSelectionOrder03006F94[0] == 1) {
gUnknown_03006F88 += 1;
            } else {
                gUnknown_03006F88 += 2;
            }
        }
 break;
 case 0x98:
 script=gScriptTable08485F88[8];
 goto waitScript;
 case 0x99:
 script=gScriptTable08485F88[9];
 waitScript:
 if(sub_0803FB3C(script)) return 1;
 break;
 }
 sub_0806B0D4();
 sub_0806B4C8();
 return 0;
}
