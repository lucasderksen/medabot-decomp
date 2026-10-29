#include "global.h"
#include "continued_commands.h"
#include "continued_late_graphics.h"
#include "continued_blend_work.h"
#include "post_dispatch.h"
#include "continued_selector_assets.h"


/* Only observed offsets are modeled. Backing object extents remain unknown. */
struct DisplayOtherFields
{
    u8 unknown00[0x10];
    u8 byte10,byte11,byte12,byte13,byte14,byte15;
    u8 modes[8];
    u16 half1E,half20,half22,half24,half26,half28;
    u16 half2A,half2C,half2E,half30;
    u8 byte32;
    s8 byte33,byte34;
};
struct DisplaySetupFields
{
    u8 unknown000[0x7FF];
    u8 byte7FF;
    u8 unknown800[0x433];
    u8 byteC33;
    u8 unknownC34[0x19];
    u8 byteC4D,byteC4E,byteC4F;
    u8 unknownC50[2];
    u16 halfC52,halfC54;
    u8 unknownC56[6];
    u8 byteC5C,byteC5D;
    u8 unknownC5E[0x59];
    u8 byteCB7,byteCB8,byteCB9;
    u8 unknownCBA[2];
    s8 byteCBC,byteCBD;
};
#define OTHER (*(struct DisplayOtherFields *)gContinuedOtherWork_030057A0)

void sub_08058C0C(u32 selector)
{
    OTHER.byte13=0;
    sub_08052B70();
    sub_080598C0(gCopiedBytes_080AC604,2,40,24);
    sub_08059734(OTHER.byte14,8,80,24);
    switch(selector)
    {
    case 0:
    {
        u8 *work;
        sub_080598C0(gCopiedBytes_080AC608,2,104,24);
        sub_080598C0(gCopiedBytes_080AC60C,2,48,32);
        sub_08059434(0,OTHER.half26,8,80,32);
        sub_080598C0(gCopiedBytes_080AC610,2,48,40);
        work=gUnknown_030057E0;
        sub_08059434(1,((struct DisplaySetupFields *)work)->byteC5C,8,80,40);
        switch(((struct DisplaySetupFields *)work)->byteC5C)
        {
        case 0:sub_080598C0(gCopiedBytes_080AC614,3,112,40);break;
        case 1:sub_080598C0(gCopiedBytes_080AC618,3,112,40);break;
        case 2:sub_080598C0(gCopiedBytes_080AC61C,3,112,40);break;
        case 3:sub_080598C0(gCopiedBytes_080AC620,3,112,40);break;
        case 4:sub_080598C0(gCopiedBytes_080AC624,3,112,40);break;
        case 5:sub_080598C0(gCopiedBytes_080AC628,3,112,40);break;
        case 6:sub_080598C0(gCopiedBytes_080AC62C,3,112,40);break;
        case 7:sub_080598C0(gCopiedBytes_080AC630,3,112,40);break;
        case 8:sub_080598C0(gCopiedBytes_080AC634,3,112,40);break;
        case 9:sub_080598C0(gCopiedBytes_080AC638,3,112,40);break;
        case 10:sub_080598C0(gCopiedBytes_080AC63C,3,112,40);break;
        case 11:sub_080598C0(gCopiedBytes_080AC640,3,112,40);break;
        case 12:sub_080598C0(gCopiedBytes_080AC644,3,112,40);break;
        case 13:sub_080598C0(gCopiedBytes_080AC648,3,112,40);break;
        case 14:sub_080598C0(gCopiedBytes_080AC64C,3,112,40);break;
        case 15:sub_080598C0(gCopiedBytes_080AC650,3,112,40);break;
        }
        sub_080598C0(gCopiedBytes_080AC654,2,48,48);
        work=gUnknown_030057E0;
        sub_08059434(2,((struct DisplaySetupFields *)work)->byteC4D,8,80,48);
        sub_080598C0(gCopiedBytes_080AC658,2,48,56);
        sub_08059434(3,((struct DisplaySetupFields *)work)->byteCB7,8,80,56);
        switch(((struct DisplaySetupFields *)work)->byteCB7)
        {
        case 0:sub_080598C0(gCopiedBytes_080AC65C,2,112,56);break;
        case 1:sub_080598C0(gCopiedBytes_080AC608,2,112,56);break;
        case 2:sub_080598C0(gCopiedBytes_080AC660,2,112,56);break;
        case 3:sub_080598C0(gCopiedBytes_080AC664,2,112,56);break;
        }
        sub_080598C0(gCopiedBytes_080AC668,2,48,64);
        work=gUnknown_030057E0;
        sub_08059434(4,((struct DisplaySetupFields *)work)->byte7FF,8,80,64);
        sub_080598C0(gCopiedBytes_080AC66C,2,48,72);
        work+=0xC33;
        sub_08059434(5,*work,8,80,72);
        break;
    }
    case 1:
    {
        u16 *const *fields;
        const void *suffix;
        sub_080598C0(gCopiedBytes_080AC670,5,104,24);
        sub_080598C0(gCopiedBytes_080AC678,3,48,32);
        fields=gNavigationHalfwordPointers_083D625C;
        sub_08059434(0,*fields[0],16,80,32);
        sub_080598C0(gCopiedBytes_080AC67C,3,48,40);
        sub_08059434(1,*fields[1],8,80,40);
        suffix=gCopiedBytes_080AC680;
        sub_080598C0(suffix,1,112,40);
        sub_080598C0(gCopiedBytes_080AC684,2,48,48);
        sub_08059434(2,*fields[2],8,80,48);
        sub_080598C0(suffix,1,112,48);
        break;
    }
    case 2:
    {
        struct DisplaySetupFields *work;
        sub_080598C0(gCopiedBytes_080AC688,6,104,24);
        sub_080598C0(gCopiedBytes_080AC690,3,48,32);
        work=(struct DisplaySetupFields *)gUnknown_030057E0;
        sub_08059434(0,work->halfC52,16,80,32);
        sub_080598C0(gCopiedBytes_080AC694,3,48,40);
        sub_08059434(0,work->halfC54,16,80,40);
        break;
    }
    case 3:
        sub_080598C0(gCopiedBytes_080AC698,10,104,24);
        sub_080598C0(gCopiedBytes_080AC6A4,3,48,32);
        sub_08059434(0,OTHER.byte12,16,80,32);
        break;
    case 4:
    {
        struct DisplaySetupFields *work;
        sub_080598C0(gCopiedBytes_080AC6A8,3,104,24);
        sub_080598C0(gCopiedBytes_080AC6AC,2,48,32);
        sub_08059434(0,OTHER.byte11,8,80,32);
        sub_080598C0(gCopiedBytes_080AC6B0,2,48,40);
        sub_08059434(1,gLaterBuffer_03006D38[2],8,80,40);
        sub_080598C0(gCopiedBytes_080AC6B4,2,48,48);
        work=(struct DisplaySetupFields *)gUnknown_030057E0;
        sub_08059434(2,work->byteC4E,8,80,48);
        if(work->byteC4E&1)sub_080598C0(gCopiedBytes_080AC6B8,1,112,48);
        else sub_080598C0(gCopiedBytes_080AC6BC,1,112,48);
        if(((struct DisplaySetupFields *)gUnknown_030057E0)->byteC4E&2)sub_080598C0(gCopiedBytes_080AC6C0,1,144,48);
        else sub_080598C0(gCopiedBytes_080AC6BC,1,144,48);
        sub_080598C0(gCopiedBytes_080AC6C4,2,48,56);
        work=(struct DisplaySetupFields *)gUnknown_030057E0;
        sub_08059434(3,work->byteCB8,8,80,56);
        sub_080598C0(gCopiedBytes_080AC6C8,2,48,64);
        sub_08059434(4,work->byteCB9,8,80,64);
        sub_080598C0(gCopiedBytes_080AC680,1,112,64);
        sub_080598C0(gCopiedBytes_080AC6CC,2,48,72);
        sub_08059434(5,work->byteC4F,8,80,72);
        switch(work->byteC4F)
        {
        case 0:sub_080598C0(gCopiedBytes_080AC6D0,1,112,72);break;
        case 1:sub_080598C0(gCopiedBytes_080AC6D4,1,112,72);break;
        case 2:sub_080598C0(gCopiedBytes_080AC6D8,1,112,72);break;
        }
        break;
    }
    case 5:
    {
        struct DisplayOtherFields *work;
        sub_080598C0(gCopiedBytes_080AC6DC,4,104,24);
        sub_080598C0(gCopiedBytes_080AC6E4,3,48,32);
        work=(struct DisplayOtherFields *)gContinuedOtherWork_030057A0;
        sub_08059434(0,work->half20,16,80,32);
        if(work->byte32)
        {
            sub_08049440(49);
            sub_08049440(50);
            sub_08049440(51);
            sub_08049440(52);
            if(gCopiedBytes_083D2DBD[work->half20]==3)sub_08049440(57);
        }
        break;
    }
    case 6:
    {
        u32 state=OTHER.byte32;
        struct DisplayOtherFields *work=(struct DisplayOtherFields *)gContinuedOtherWork_030057A0;
        switch(state)
        {
        case 0:
            sub_080598C0(gCopiedBytes_080AC6E8,4,104,24);
            sub_080598C0(gCopiedBytes_080AC6F0,3,48,32);
            sub_08059434(0,work->half2E,16,80,32);
            if(work->half2E==16)sub_080598C0(gCopiedBytes_080AC6F4,3,120,32);
            else sub_080598C0(gCopiedBytes_080AC6F8,3,120,32);
            sub_080598C0(gCopiedBytes_080AC6FC,3,48,40);
            work=(struct DisplayOtherFields *)gContinuedOtherWork_030057A0;
            sub_08059434(1,work->half30,16,80,40);
            sub_080598C0(gCopiedBytes_080AC700,3,48,48);
            sub_08059434(2,work->half24,16,80,48);
            sub_080598C0(gCopiedBytes_080AC704,3,48,56);
            sub_08059434(3,work->half1E,16,80,56);
            break;
        case 1:
        {
            const void *const *scripts;
            if(work->half2E==16)scripts=gContinuedScripts_08411AE0;
            else scripts=gStateScriptTables_0847DF24[work->half2E];
            if(sub_08047C24(0,0,0,scripts[work->half30]))work->byte32=0;
            break;
        }
        }
        break;
    }
    case 7:
    {
        struct DisplaySetupFields *work;
        struct DisplayOtherFields *other;
        sub_080598C0(gCopiedBytes_080AC684,2,104,24);
        sub_080598C0(gCopiedBytes_080AC708,2,48,32);
        work=(struct DisplaySetupFields *)gUnknown_030057E0;
        sub_08059434(0,work->byteCBC,8,80,32);
        sub_080598C0(gCopiedBytes_080AC70C,2,48,40);
        sub_08059434(1,work->byteCBD,8,80,40);
        sub_080598C0(gCopiedBytes_080AC710,3,48,48);
        other=(struct DisplayOtherFields *)gContinuedOtherWork_030057A0;
        sub_08059434(2,other->byte33,8,80,48);
        sub_080598C0(gCopiedBytes_080AC714,2,48,56);
        sub_08059434(3,other->byte34,8,80,56);
        sub_080598C0(gCopiedBytes_080AC718,3,48,64);
        sub_08059434(4,work->byteC5D,8,80,64);
        sub_080598C0(gCopiedBytes_080AC680,1,112,64);
        break;
    }
    }
}
