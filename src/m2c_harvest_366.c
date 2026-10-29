/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "audio.h"
#include "background_state.h"
#include "continued_scene_records.h"
#include "coordinate_helpers.h"
#include "frame.h"
#include "frame_objects.h"
#include "main_callbacks.h"
#include "record_helpers.h"
#include "state0_callbacks.h"
#include "state0_work.h"
#include "tile_text.h"

struct AudioRouteTrack { u32 unknown00; const u8 *route; };
struct AudioRouteWork { u8 pad00[0x728]; struct AudioRouteTrack *track; u8 flags; };
struct AudioRouteChannel { u8 pad00[0x48]; u16 index; u8 pad4A[6]; u8 flags; u8 pad51[0x12]; u8 mode; u8 channel; u8 pad65[0xA]; u8 route; u8 forcedRoute; };

extern const u16 gState0MotionSteps_083AF7B0[32];
extern const u8 *const gState0NextCommands_083B6100[];
extern const u8 gUnknown_083ABBF2[];
extern const u8 gUnknown_083ABBF6[];
extern void *gUnknown_03007014;
extern void sub_080378F0(u32, u32);

void sub_08037C50(void);
void sub_08073604(void *channelPointer);

void sub_08037C50(void) {

    union {struct TileCoordinates coordinates;s32 word;} result4;
    union {struct TileCoordinates coordinates;s32 word;} result8;
    s32 packedPosition;
    struct FrameObject *radiusFrame;
    struct FrameObject *negativeAngleFrame;
    struct FrameObject *negativePhaseFrame;
    struct FrameObject *negativePositionFrame;
    struct FrameObject *positiveAngleFrame;
    struct FrameObject *positivePhaseFrame;
    struct FrameObject *positivePositionFrame;
    struct FrameObject *tickFrame;
    struct FrameObject *statusFrame;
    u32 frameRoot;

    sub_08040BD8(gState0NextCommands_083B6100[gFrameObjects[gState0TypedWork.bytes[0x12F]].unknown2C[2]], gState0TypedWork.bytes[0x12F]);
    statusFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    if (statusFrame->unknown2C[1] == 0xFF) {
        statusFrame->unknown23[6] += 1;
        return;
    }
    if ((statusFrame->unknown2C[1]&0x3FU)==0) {
        switch (gState0TransferWork.bytes[0x51]) {
        case 0:
            sub_08074DE0(0x36U);
            break;
        case 1:
            sub_08074DE0(0x28U);
            break;
        case 2:
            sub_08074DE0(0x31U);
            break;
        case 3:
            sub_08074DE0(0x71U);
            break;
        case 4:
            sub_08074DE0(0x4FU);
            break;
        case 5:break;
        }
    }
    frameRoot=(u32)gFrameObjects;
    radiusFrame=(struct FrameObject*)(frameRoot+((u32)gState0TypedWork.bytes[0x12F]<<6));
    radiusFrame->byte2B += gState0MotionSteps_083AF7B0[radiusFrame->unknown2C[1]&0x1Fu];
    if (!(1 & gState0TransferWork.bytes[0xF8])) {
        if (gState0TransferWork.bytes[0x51] != 3) {
            negativeAngleFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
            negativeAngleFrame->angle = (negativeAngleFrame->angle - 0x10) & 0x3FF;
        }
        negativePhaseFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        negativePhaseFrame->unknown2C[0] -= 1;
        negativePositionFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        result4.coordinates=sub_08042BC0((u32)negativePositionFrame->unknown2C[0],(u32)negativePositionFrame->byte2B,0xB8U,0x34);
        packedPosition=result4.word;
    } else {
        if (gState0TransferWork.bytes[0x51] != 3) {
            positiveAngleFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
            positiveAngleFrame->angle = (positiveAngleFrame->angle + 0x10) & 0x3FF;
        }
        positivePhaseFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        positivePhaseFrame->unknown2C[0] += 1;
        positivePositionFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
        result8.coordinates=sub_08042BC0((u32)positivePositionFrame->unknown2C[0],(u32)positivePositionFrame->byte2B,0x38U,0x34);
        packedPosition=result8.word;
    }
    gFrameObjects[gState0TypedWork.bytes[0x12F]].screenX = (s16) packedPosition;
    gFrameObjects[gState0TypedWork.bytes[0x12F]].screenY = (s16) (packedPosition >> 0x10);
    sub_080378F0(gState0TypedWork.bytes[0x12F], (u32)(packedPosition >> 16));
    tickFrame = &gFrameObjects[gState0TypedWork.bytes[0x12F]];
    tickFrame->unknown2C[1] += 1;
}

void sub_08073604(void *channelPointer) {

    struct AudioRouteChannel *channel;
    struct AudioRouteWork *work;
    const u8 *route;
    u8 *flags;
    u32 selection;
    u32 channelIndex;
    u8 mask;
    const u8 *maskRoot;
    const u8 *routeRoot;
    channel = channelPointer;
    flags = &channel->flags;
    if (0x40 & *flags) {
        work = gUnknown_03007014;
        if (4 & work->flags) {
            selection = 3;
        } else {
            if (channel->forcedRoute != 0) {
                selection = channel->forcedRoute;
            } else {
                if (channel->mode == 2) {
                    route = work->track->route + channel->index;
                } else {
                    route = &channel->route;
                }
                selection = *route;
            }
        }
        maskRoot = gUnknown_083ABBF2;
        channelIndex = channel->channel;
        mask = maskRoot[channelIndex];
        routeRoot = gUnknown_083ABBF6;
        selection = *(const u8 *)((u32)routeRoot + (selection + (channelIndex << 2)));
        *(volatile u8 *)0x04000081 = (mask & *(volatile u8 *)0x04000081) | selection;
        *flags = 0xBF & *flags;
    }
}
