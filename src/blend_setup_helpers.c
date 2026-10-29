#include "blend_setup_helpers.h"
#include "global.h"

struct BlendSetupWork
{
    u8 unknown00[12];
    float first;
    float second;
};
extern struct BlendSetupWork gBlendSetupWork_03006F40;

void sub_080487F8(void)
{
    *(volatile u16 *)0x04000050 = 0x1F41;
    gBlendSetupWork_03006F40.first = 12.0f;
    gBlendSetupWork_03006F40.second = 8.0f;
    {
        u32 first = 12;
        u32 second = 8;
        *(volatile u16 *)0x04000052 = first | (second << 8);
    }
}

void sub_08048830(void)
{
    *(volatile u16 *)0x04000050 = 0x0F40;
    gBlendSetupWork_03006F40.first = 12.0f;
    gBlendSetupWork_03006F40.second = 10.0f;
    {
        u32 first = 12;
        u32 second = 10;
        *(volatile u16 *)0x04000052 = first | (second << 8);
    }
}
