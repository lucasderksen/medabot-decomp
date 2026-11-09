/*
 * Byte-verified functions derived from m2c drafts, source rewrites and clones.
 * Names and types are provisional;
 * see docs/M2C.md.
 */

#include "global.h"
#include "action_aux_data.h"
#include "action_scene_data.h"
#include "audio.h"
#include "background_state.h"
#include "battle_work.h"
#include "bg_scroll.h"
#include "composite_graphics.h"
#include "continued_scene_records.h"
#include "fallback_map_assets.h"
#include "frame.h"
#include "frame_command_data.h"
#include "gba.h"
#include "graphics.h"
#include "main_callbacks.h"
#include "map_object_spawns.h"
#include "pose_channels.h"
#include "record_helpers.h"
#include "render_work.h"
#include "scene_view.h"
#include "sound_work.h"
#include "sprite_layouts.h"
#include "state0_display.h"
#include "state0_work.h"
#include "tile_text.h"

struct ObjectAffineInput { s16 xScale; s16 yScale; u16 angle; };
struct ObjectAffineOutput { s16 pa, pb, pc, pd; };
struct OamView
{
    u8 y;
    u8 attr0hi;
    u16 x:9, unused9:7;
    u16 tileNum:10, priority:2, paletteNum:4;
    u16 affineParam;
};
struct OamBytes
{
    u8 y;
    u8 attr0hi;
    u8 xlo;
    u8 xhi:1, matrixNum:3, hFlip:1, vFlip:1, size:2;
    u8 tilelo;
    u8 tilehi:2, priority:2, paletteNum:4;
    u16 affineParam;
};
struct TileBlockView { struct OamView oam; s16 y; s16 x; u16 angle; u16 unknownE; };
struct AssetSetView
{
    const void *entries;
    s32 y;
    s32 x;
    s8 offsetY;
    s8 offsetX;
    s8 depth;
    u8 child0F;
    u8 child10;
    u8 palette;
    u8 height;
    u8 width;
};
struct RenderAffineView { u8 unknown000[0xF8C]; u16 affine[0x84]; u8 byte1094; u8 byte1095; };
struct LaterWork { struct RenderAffineView *render; const struct AssetSetView **sets; struct TileBlockView *blocks; };

extern const struct ObjectAffineOutput gObjectAffineIdentity_080ABD64;
extern const u8 gLaterRendererOrder_08081490[];
extern void ObjAffineSet(const void *, void *, u32, u32);

void sub_080465B8(struct LaterWork *work, const u32 *commands, u32 selectorArg, s32 y, s32 x, s32 priorityArg, s32 angleArg, u32 flipArg);

void sub_080465B8(struct LaterWork *work, const u32 *commands, u32 selectorArg, s32 y, s32 x, s32 priorityArg, s32 angleArg, u32 flipArg) {

  struct OamView *obj;
  u8 selector = selectorArg;
  s16 priority = priorityArg;
  u16 angle = angleArg;
  u8 flip = flipArg;
  s32 origY = y;
  s32 origX = x;
  unsigned int angleOffset;
  u16 depth;
  const struct AssetSetView *set = work->sets[selector];
  struct TileBlockView *block = &work->blocks[selector];
  struct ObjectAffineOutput matrix = gObjectAffineIdentity_080ABD64;
  struct ObjectAffineInput input = {0x100, 0x100, -angle};
  s32 dx;
  s32 dy;
  int angleSum;
  s32 py;
  s32 px;
  u32 visible;
  u32 found;
  const u32 *p;
  s32 by;
  s32 bx;
  u8 index;
  if (flip)
  {
    index = gLaterRendererOrder_08081490[selector];
    set = work->sets[index];
    angleOffset = work->blocks[index].angle;
    by = work->blocks[index].y;
    bx = work->blocks[index].x;
  }
  else
  {
    angleOffset = block->angle;
    by = block->y;
    bx = block->x;
  }
  depth = ((s16) priority) + set->depth;
  if (((s16) depth) < 0)
  {
    depth = 0;
  }
  dx = set->offsetY + (by >> 8);
  dy = set->offsetX + (bx >> 8);
  ObjAffineSet(&input, &matrix, 1, 2);
  if (flip)
  {
    input.angle = -input.angle;
  }
  y += (dy * matrix.pb) + (dx * matrix.pd);
  if (flip)
  {
    x -= (dy * matrix.pa) + (dx * matrix.pc);
  }
  else
  {
    x += (dy * matrix.pa) + (dx * matrix.pc);
  }
  if (gState0TypedWork.bytes[0x96])
  {
    visible = 0;
  }
  else
  {
    visible = 1;
  }
  if (commands != ((void *) 0))
  {
    found = 0;
    if ((*((const u8 *) commands)) & 0x3F)
    {
      u8 sel = selector;
      const u8 *flag = &gState0TypedWork.bytes[0x96];
      p = commands;
    search:
        if (sel == (((*p) << 26) >> 26))
        {
          do { /* FAKE MATCH: wrap weights the flag test so found/flag get r4/r5 as in the reference */
            if (*flag)
            {
              visible = 0;
              goto plain;
            }
          } while (0);
          visible = ((*p) << 17) >> 31;
          goto shown;
        }
        p++;
      if ((*((const u8 *) p)) & 0x3F) goto search;
    }
  }
  else
  {
    found = 1;
  }
  if (!found)
  {
    goto children;
  }
  shown:
  if (visible)
  {
    u8 slot;
    if (flip)
    {
      input.angle += angleOffset;
    }
    else
    {
      input.angle -= angleOffset;
    }
    ObjAffineSet(&input, &matrix, 1, 2);
    ((struct OamBytes *) (&block->oam))->matrixNum = work->render->byte1095 & 7;
    ((struct OamBytes *) (&block->oam))->hFlip = (work->render->byte1095 & 8) >> 3;
    ((struct OamBytes *) (&block->oam))->vFlip = (work->render->byte1095 & 0x10) >> 4;
    slot = work->render->byte1095;
    dx = 2 * (2 * slot); /* dx is free here and doubles as the affine index, as in the reference (r5) */
    if (flip)
    {
      matrix.pa = -matrix.pa;
      matrix.pb = -matrix.pb;
    }
    work->render->affine[dx++] = matrix.pa;
    work->render->affine[dx++] = matrix.pb;
    work->render->affine[dx++] = matrix.pc;
    work->render->affine[dx] = matrix.pd;
    if ((++work->render->byte1095) > 0x1F)
    {
      work->render->byte1095 = 0;
    }
  }

  if (visible)
  {
    py = set->height >> 1;
    px = set->width >> 1;
    dx = set->y - py;
    dy = set->x - px;
    py = y - (((dy * matrix.pb) + (dx * matrix.pd)) + (py << 8));
    px = x - (((dy * matrix.pa) + (dx * matrix.pc)) + (px << 8));
  }
  else
  {
    plain:
    py = y - (set->y << 8);

    if (flip)
    {
      px = x - ((set->width - set->x) << 8);
    }
    else
    {
      px = x - (set->x << 8);
    }
  }
  while (((s8) gRenderWork->byte1094) < 0)
  {
    ;
  }

  obj = (struct OamView *) MakeOamInsertGap(gRenderWork->objects, gRenderWork->byte1094++, 1, (s16) depth);
  *obj = block->oam;
  obj->affineParam = depth;
  if ((!visible) && flip)
  {
    ((struct OamBytes *) obj)->hFlip = 1;
  }
  obj->y = py >> 8;
  px = (px >> 8) & 0x3FF;
  obj->x = px;
  if (((s16) priority) > 0x17B)
  {
    ((struct OamBytes *) obj)->priority = 3;
  }
  else
    if (((s16) priority) > 0x117)
  {
    ((struct OamBytes *) obj)->priority = 2;
  }
  else
    if (((s16) priority) > 0xB3)
  {
    ((struct OamBytes *) obj)->priority = 1;
  }
  else
  {
    ((struct OamBytes *) obj)->priority = 0;
  }
  children:
  if (work->sets[selector]->child10)
  {
    if (!visible)
    {
      sub_080465B8(work, commands, work->sets[selector]->child10, y, x, (s16) depth, visible, flip);
    }
    else
    {
      sub_080465B8(work, commands, work->sets[selector]->child10, y, x, (s16) depth, (s16) (angleSum = ((s16) angleOffset) + ((s16) angle)), flip);
    }
  }

  do { /* FAKE MATCH: wrap keeps work in r8 and set in sb; without it global-alloc swaps them */
    if (work->sets[selector]->child0F)
    {
      sub_080465B8(work, commands, work->sets[selector]->child0F, origY, origX, (s16) priority, (s16) angle, flip);
    }
  } while (0);
}
