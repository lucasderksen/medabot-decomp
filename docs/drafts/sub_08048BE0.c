extern u8 gContinuedByte_03002B64;
void sub_08048BE0(void)
{
  if (gContinuedByte_03002B64 & 2)
  {
    u8 keys;
    if (gContinuedByte_03002B64 & 0x40)
    {
      gBackgroundState_03005310.scrollY[0] -= 4;
      gBackgroundState_03005310.scrollY[1] -= 4;
      gBackgroundState_03005310.scrollY[2] -= 4;
    }
    ;
    if (gContinuedByte_03002B64 & 0x80)
    {
      gBackgroundState_03005310.scrollY[0] += 4;
      gBackgroundState_03005310.scrollY[1] += 4;
      gBackgroundState_03005310.scrollY[2] += 4;
    }
    if (gContinuedByte_03002B64 & 0x20)
    {
      gBackgroundState_03005310.scrollX[0] -= 4;
      gBackgroundState_03005310.scrollX[1] -= 4;
      gBackgroundState_03005310.scrollX[2] -= 4;
    }
    if (gContinuedByte_03002B64 & 0x10)
    {
      gBackgroundState_03005310.scrollX[0] += 4;
      gBackgroundState_03005310.scrollX[1] += 4;
      gBackgroundState_03005310.scrollX[2] += 4;
    }
  }
  if (gContinuedByte_03002B64 & 0x10)
  {
    gBackgroundState_03005310.angle = ((u32) ((gBackgroundState_03005310.angle + 1) & 0xFFFF)) % 0x100;
  }
  if (gContinuedByte_03002B64 & 0x20)
  {
    gBackgroundState_03005310.angle = (gBackgroundState_03005310.angle + 0xFF) & 0xFF;
  }
}
