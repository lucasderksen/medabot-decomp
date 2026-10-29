struct ObjectAffineInput { s16 xScale; s16 yScale; u16 angle; };
struct ObjectAffineOutput { s16 pa, pb, pc, pd; };
void ObjAffineSet(const void *, void *, u32, u32);
extern const struct ObjectAffineOutput D_080ABD64;
extern const u8 D_08081490[];
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

void sub_080465B8(struct LaterWork *work, const u32 *commands, u32 selectorArg, s32 y, s32 x, s32 priorityArg, s32 angleArg, u32 flipArg)
{
  struct OamView *obj;
  u8 selector = selectorArg;
  s16 priority = priorityArg;
  u16 angle = angleArg;
  s16 pd;
  u8 flip = flipArg;
  s32 origY = y;
  s32 origX = x;
  unsigned int angleOffset;
  u16 depth;
  const struct AssetSetView *set = work->sets[selector];
  struct TileBlockView *block = &work->blocks[selector];
  struct ObjectAffineOutput matrix = D_080ABD64;
  struct ObjectAffineInput input = {0x100, 0x100, -angle};
  s32 dx;
  s32 dy;
  int angleSum;
  s32 halfH;
  s32 halfW;
  s32 py;
  s32 px;
  int new_var;
  u32 visible;
  u32 found;
  const u32 *p;
  s32 by;
  s32 bx;
  u8 index;
  if (flip)
  {
    index = D_08081490[selector];
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
  do
  {
    depth = ((s16) priority) + set->depth;
    if (((s16) depth) < 0)
    {
      depth = 0;
    }
    dx = set->offsetY + (by >> 8);
  }
  while (0);
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
          do {
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
    u16 *affine;
    u32 k;
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
    k = 2 * (2 * slot);
    if (flip)
    {
      matrix.pa = -matrix.pa;
      matrix.pb = (halfW = (u16)-matrix.pb);
    }
    work->render->affine[k++] = matrix.pa;
    work->render->affine[k++] = matrix.pb;
    work->render->affine[k++] = matrix.pc;
    work->render->affine[k] = matrix.pd;
    if ((++work->render->byte1095) > 0x1F)
    {
      work->render->byte1095 = 0;
    }
  }

  if (visible)
  {
    halfH = set->height >> 1;
    halfW = set->width >> 1;
    dx = set->y - halfH;
    dy = set->x - halfW;
    py = y - (((dy * matrix.pb) + (dx * matrix.pd)) + (halfH << 8));
    px = x - (((dy * matrix.pa) + (dx * matrix.pc)) + (halfW << 8));
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

  obj = (struct OamView *) sub_08045588(gRenderWork->objects, gRenderWork->byte1094++, 1, (s16) depth);
  *obj = block->oam;
  obj->affineParam = depth;
  if ((!visible) && flip)
  {
    ((struct OamBytes *) obj)->hFlip = 1;
  }
  obj->y = py >> 8;
  obj->x = (px >> 8) & (py = 0x3FF);
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

  do {
  if (work->sets[selector]->child0F)
  {
    sub_080465B8(work, commands, work->sets[selector]->child0F, origY, origX, (s16) priority, (s16) angle, flip);
  }
  } while (0);
}
