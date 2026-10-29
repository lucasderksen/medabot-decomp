extern const void *const gFreshPointers_08483ED8[];
void sub_0805A444(s32 value, s32 x, s32 y);
u32 sub_0805B5FC(u32 index);
void sub_0805B530(u32 a, u32 b, u32 c);
void sub_0805B558(void);

struct PairAED0 { u16 name; u16 value; };
struct CtxAED0 { u8 unknown00[0x11]; u8 first; };

void sub_0805AED0(void)
{
  u32 saved0;
  u32 saved1;
  s32 count = 5;
  int new_var;
  u8 names[count];
  u8 values[count];
  s8 i;
  new_var = sizeof(names);
  for (i = 0; i < ((s32) new_var); i++)
  {
    names[i] = ((struct PairAED0 *) 0x02040000)[((struct CtxAED0 *) gMainContextPointer_03006F74)->first + i].name;
    values[i] = ((struct PairAED0 *) 0x02040000)[((struct CtxAED0 *) gMainContextPointer_03006F74)->first + i].value;
  }

  for (i = 0; i < ((s32) new_var); i++)
  {
    sub_08040D0C(i << 4, 0x10);
    sub_0805B530(0x18, (i * 2) + 3, 3);
    sub_0805B530(0x18, (i * 2) + 4, 3);
  }

  do
  {
    saved0 = *((u16 *) 0x0600F0EE);
  }
  while (0);
  saved1 = *((u16 *) 0x0600F12E);
  for (i = 0; i < ((s32) new_var); i++)
  {
    if (values[i] != 0)
    {
      sub_0803F63C(gFreshPointers_08483ED8[names[i]], gDebugMenuTextBuffer, 0x11);
      sub_08040DB8(gDebugMenuTextBuffer, (u8) (i * 15), 0xC, (i * 2) + 3, 7, 8, 1, 2);
      sub_0805A444(values[i], 0x18, (i * 2) + 3);
      *((u16 *) ((((i * 2) + 3) << 6) + 0x0600F02E)) = saved0;
      *((u16 *) ((((i * 2) + 4) << 6) + 0x0600F02E)) = saved1;
      gFrameObjects[i + 0x55].flags |= 0x4000;
      gFrameObjects[i + 0x55].frameAndGroup = (sub_0805B5FC(names[i])) ? (0x21) : (0x22);
    }
    else
    {
      *((u16 *) ((((i * 2) + 3) << 6) + 0x0600F02E)) = 0;
      *((u16 *) ((((i * 2) + 3) << 6) + 0x0600F030)) = 0;
      *((u16 *) ((((i * 2) + 3) << 6) + 0x0600F032)) = 0;
      *((u16 *) ((((i * 2) + 4) << 6) + 0x0600F02E)) = 0;
      *((u16 *) ((((i * 2) + 4) << 6) + 0x0600F030)) = 0;
      *((u16 *) ((count = ((i * 2) + 4) << 6) + 0x0600F032)) = 0;
      gFrameObjects[i + 0x55].flags &= 0xBFFF;
    }
  }

  sub_0805B558();
}
