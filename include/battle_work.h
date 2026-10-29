#ifndef BATTLE_WORK_H
#define BATTLE_WORK_H

#include "global.h"

/*
 * Observed layout of the 0x03001800 work block (symbol
 * gCounter6ED08_03001800). Field names are provisional; offsets are
 * byte-verified by the functions that access them.
 */
struct BattlePoint {
    u16 x;
    u16 y;
};

/* 8-byte records from 0x28, indexed by the bytes at 0x89 and 0x8A. */
struct BattleRecord28 {
    u8 value0;
    u8 pad1[2];
    u8 kind3;
    u8 value4;
    u8 pad5[3];
};

struct BattleWork {
    u8 pad00[0x28];
    struct BattleRecord28 records28[2];
    u8 shift38;
    u8 pad39[3];
    u8 byte3C;
    u8 pad3D[0x14];
    u8 frame51;
    u8 count52;
    u8 frame53;
    u8 count54;
    u8 flags55;
    u8 pad56[3];
    u8 value59;
    u8 pad5A[6];
    u8 base60;
    u8 pad61[3];
    u8 buffer64[0x23];
    u8 slot87;
    u8 value88;
    u8 record89;
    u8 byte8A;
    u8 group8B;
    u8 pad8C[0x1A];
    u8 resultA6;
    u8 partA7;
    u8 kindA8;
    u8 padA9;
    u8 counterAA;
    u8 flagAB;
    u8 padAC[9];
    u8 flagB5;
    u8 padB6;
    u8 byteB7;
    u8 padB8[0x10];
    u16 valueC8;
    u16 valueCA;
    u16 valueCC;
    u8 padCE[3];
    u8 flagD1;
    u8 activeD2[4];
    u16 valuesD6[4];
    u8 flagDE;
    u8 partDF;
    u8 padE0[8];
    s16 valueE8;
    u8 padEA[2];
    s16 valueEC;
    s16 valueEE;
    u8 padF0[2];
    u16 valueF2;
    u8 padF4[2];
    u8 flagsF6;
    u8 padF7;
    u8 flagsF8;
    u8 padF9[6];
    u8 flagsFF;
    u8 pad100[2];
    s16 value102;
    u16 value104;
    s16 index106;
    u16 value108;
    u16 value10A;
    u16 value10C;
    u16 value10E;
    u16 value110;
    u8 sideCommand112[2];
    u8 byte114;
    u8 byte115;
    u8 pad116[2];
    u8 flag118;
    u8 part119;
    u8 value11A;
    u8 pad11B;
    u8 partCopy11C[0x18];
    u8 pad134[8];
    struct BattlePoint pos13C[6];
    u16 pos154[4];
    u8 pad15C[3];
    u8 active15F[2];
    u8 value161;
    u8 index162;
    u8 pad163;
    u8 flag164;
    u8 pad165[7];
    u16 amount16C;
    u8 levelUp16E[3][8];
    u8 pad186[4];
    u8 received18A[0x10];
    u8 list19A[6];
    u8 value1A0;
    u8 pad1A1;
    u8 index1A2;
    u8 pad1A3;
    u8 result1A4;
    u8 result1A5;
    u8 pad1A6[2];
    u16 sum1A8;
    u8 pad1AA[4];
    u8 flag1AE;
    u8 toggle1AF;
    u8 toggle1B0;
};

extern struct BattleWork gCounter6ED08_03001800;

#endif
