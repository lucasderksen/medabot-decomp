#include "scene_animation_data.h"

#define ANIMATION_FRAME(op, argument, duration, frame) (op), (argument), (duration), (frame)
#define ANIMATION_LOOP(index) 0xFFFE, (index)
#define ANIMATION_STOP 0xFFFF

/* Variable-width native records, including abbreviated terminals and empty roots. */
const u16 gSceneAnimationWords_083F704C[1434] __attribute__((aligned(2))) = {
    /* Root 0; ROM 083F704C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0001),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0000),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0002),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0000),
    ANIMATION_LOOP(0),
    /* Root 1; ROM 083F7070. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0004),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0003),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0005),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0003),
    ANIMATION_LOOP(0),
    /* Root 2; ROM 083F7094. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0007),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0006),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0008),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0006),
    ANIMATION_LOOP(0),
    /* Root 3; ROM 083F70B8. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0009),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0009),
    ANIMATION_LOOP(0),
    /* Root 4; ROM 083F70DC. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000C),
    ANIMATION_LOOP(0),
    /* Root 5; ROM 083F7100. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0010),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0011),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x000F),
    ANIMATION_LOOP(0),
    /* Root 6; ROM 083F7124. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0013),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0012),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0014),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0012),
    ANIMATION_LOOP(0),
    /* Root 7; ROM 083F7148. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0016),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0015),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0017),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0015),
    ANIMATION_LOOP(0),
    /* Root 8; ROM 083F716C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0019),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0018),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0018),
    ANIMATION_LOOP(0),
    /* Root 9; ROM 083F7190. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001B),
    ANIMATION_LOOP(0),
    /* Root 10; ROM 083F71B4. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0020),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x001E),
    ANIMATION_LOOP(0),
    /* Root 11; ROM 083F71D8. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0022),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0021),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0023),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0021),
    ANIMATION_LOOP(0),
    /* Root 12; ROM 083F71FC. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0025),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0024),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0026),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0024),
    ANIMATION_LOOP(0),
    /* Root 13; ROM 083F7220. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0028),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0027),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0029),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0027),
    ANIMATION_LOOP(0),
    /* Root 14; ROM 083F7244. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002A),
    ANIMATION_LOOP(0),
    /* Root 15; ROM 083F7268. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x002D),
    ANIMATION_LOOP(0),
    /* Root 16; ROM 083F728C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0031),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0030),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0032),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0030),
    ANIMATION_LOOP(0),
    /* Root 17; ROM 083F72B0. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0034),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0033),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0035),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0033),
    ANIMATION_LOOP(0),
    /* Root 18; ROM 083F72D4. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0037),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0036),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0038),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0036),
    ANIMATION_LOOP(0),
    /* Root 19; ROM 083F72F8. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0039),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0039),
    ANIMATION_LOOP(0),
    /* Root 20; ROM 083F731C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003C),
    ANIMATION_LOOP(0),
    /* Root 21; ROM 083F7340. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0040),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0041),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x003F),
    ANIMATION_LOOP(0),
    /* Root 22; ROM 083F7364. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0043),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0042),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0044),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0042),
    ANIMATION_LOOP(0),
    /* Root 23; ROM 083F7388. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0046),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0045),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0047),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0045),
    ANIMATION_LOOP(0),
    /* Root 24; ROM 083F73AC. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0049),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0048),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0048),
    ANIMATION_LOOP(0),
    /* Root 25; ROM 083F73D0. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004B),
    ANIMATION_LOOP(0),
    /* Root 26; ROM 083F73F4. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0050),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x004E),
    ANIMATION_LOOP(0),
    /* Root 27; ROM 083F7418. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0052),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0051),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0053),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0051),
    ANIMATION_LOOP(0),
    /* Root 28; ROM 083F743C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0055),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0054),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0056),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0054),
    ANIMATION_LOOP(0),
    /* Root 29; ROM 083F7460. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0058),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0057),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0059),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0057),
    ANIMATION_LOOP(0),
    /* Root 30; ROM 083F7484. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005A),
    ANIMATION_LOOP(0),
    /* Root 31; ROM 083F74A8. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x005D),
    ANIMATION_LOOP(0),
    /* Root 32; ROM 083F74CC. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0061),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0060),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0062),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0060),
    ANIMATION_LOOP(0),
    /* Root 33; ROM 083F74F0. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0064),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0063),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0065),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0063),
    ANIMATION_LOOP(0),
    /* Root 34; ROM 083F7514. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0067),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0066),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0068),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0066),
    ANIMATION_LOOP(0),
    /* Root 35; ROM 083F7538. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0069),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0069),
    ANIMATION_LOOP(0),
    /* Root 36; ROM 083F755C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006C),
    ANIMATION_LOOP(0),
    /* Root 37; ROM 083F7580. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0070),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0071),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x006F),
    ANIMATION_LOOP(0),
    /* Root 38; ROM 083F75A4. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0073),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0072),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0074),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0072),
    ANIMATION_LOOP(0),
    /* Root 39; ROM 083F75C8. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0076),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0075),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0077),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0075),
    ANIMATION_LOOP(0),
    /* Root 40; ROM 083F75EC. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0079),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0078),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0078),
    ANIMATION_LOOP(0),
    /* Root 41; ROM 083F7610. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007B),
    ANIMATION_LOOP(0),
    /* Root 42; ROM 083F7634. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0080),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x007E),
    ANIMATION_LOOP(0),
    /* Root 43; ROM 083F7658. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0082),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0081),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0083),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0081),
    ANIMATION_LOOP(0),
    /* Root 44; ROM 083F767C. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0085),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0084),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0086),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0084),
    ANIMATION_LOOP(0),
    /* Root 45; ROM 083F76A0. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0088),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0087),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0089),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x0087),
    ANIMATION_LOOP(0),
    /* Root 46; ROM 083F76C4. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008B),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008A),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008C),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008A),
    ANIMATION_LOOP(0),
    /* Root 47; ROM 083F76E8. */
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008E),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008D),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008F),
    ANIMATION_FRAME(0xFFFB, 0x0000, 0x0008, 0x008D),
    ANIMATION_LOOP(0),
    /* Root 48; ROM 083F770C. */
    ANIMATION_FRAME(0xFFFC, 0x0000, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0001, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0002, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0003, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 49; ROM 083F7734. */
    ANIMATION_FRAME(0xFFFC, 0x0008, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0009, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x000A, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x000B, 0x0004, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 50; ROM 083F775C. */
    ANIMATION_FRAME(0xFFFC, 0x000C, 0x0001, 0x0101),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 51; ROM 083F776C. */
    0, /* Empty native storage. */
    /* Root 52; ROM 083F776E. */
    0, /* Empty native storage. */
    /* Root 53; ROM 083F7770. */
    0, /* Empty native storage. */
    /* Root 54; ROM 083F7772. */
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0001, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0002, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0002, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0002, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0002, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0028, 0x0002, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0029, 0x0002, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 55; ROM 083F787A. */
    ANIMATION_FRAME(0xFFFC, 0x0030, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0031, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0032, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0033, 0x0006, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 56; ROM 083F78A2. */
    ANIMATION_FRAME(0xFFFC, 0x0038, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0039, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x003A, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x003B, 0x0006, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 57; ROM 083F78CA. */
    ANIMATION_FRAME(0xFFFC, 0x0040, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0041, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0042, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0043, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 58; ROM 083F78F2. */
    ANIMATION_FRAME(0xFFFC, 0x0048, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0049, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x004A, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x004B, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 59; ROM 083F791A. */
    ANIMATION_FRAME(0xFFFD, 0x0008, 0x0000, 0x0000),
    ANIMATION_FRAME(0xFFFC, 0x0050, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0051, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0052, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0053, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 60; ROM 083F794A. */
    ANIMATION_FRAME(0xFFFC, 0x0058, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0059, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x005A, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x005B, 0x0006, 0x0100),
    ANIMATION_STOP,
    0, 0, 0, /* Empty native storage. */
    /* Root 61; ROM 083F7972. */
    ANIMATION_FRAME(0xFFFC, 0x0060, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0061, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0062, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0063, 0x0006, 0x0100),
    ANIMATION_STOP,
    0, 0, 0, /* Empty native storage. */
    /* Root 62; ROM 083F799A. */
    ANIMATION_FRAME(0xFFFC, 0x0068, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 63; ROM 083F79AA. */
    ANIMATION_FRAME(0xFFFC, 0x0070, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 64; ROM 083F79BA. */
    ANIMATION_FRAME(0xFFFC, 0x0071, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 65; ROM 083F79CA. */
    ANIMATION_FRAME(0xFFFC, 0x0079, 0x0020, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0078, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0079, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0078, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0079, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0078, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0079, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0078, 0x0038, 0x0100),
    ANIMATION_STOP,
    0, 0, 0, /* Empty native storage. */
    /* Root 66; ROM 083F7A12. */
    ANIMATION_FRAME(0xFFFC, 0x0080, 0x0020, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0081, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0080, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0081, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0081, 0x0008, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0081, 0x0040, 0x0100),
    ANIMATION_STOP,
    0, 0, 0, /* Empty native storage. */
    /* Root 67; ROM 083F7A4A. */
    ANIMATION_FRAME(0xFFFC, 0x0008, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0009, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x000A, 0x0004, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x000B, 0x0004, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 68; ROM 083F7A72. */
    0, /* Empty native storage. */
    /* Root 69; ROM 083F7A74. */
    0, /* Empty native storage. */
    /* Root 70; ROM 083F7A76. */
    0, /* Empty native storage. */
    /* Root 71; ROM 083F7A78. */
    ANIMATION_FRAME(0xFFFD, 0x0068, 0x0000, 0x0000),
    ANIMATION_FRAME(0xFFFC, 0x00A8, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x00A9, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x00AA, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x00AB, 0x0006, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 72; ROM 083F7AA8. */
    ANIMATION_FRAME(0xFFFC, 0x00B0, 0x0008, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 73; ROM 083F7AB8. */
    ANIMATION_FRAME(0xFFFD, 0x0042, 0x0000, 0x0000),
    ANIMATION_FRAME(0xFFFC, 0x0038, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x0039, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFD, 0x0042, 0x0000, 0x0000),
    ANIMATION_FRAME(0xFFFC, 0x003A, 0x0006, 0x0100),
    ANIMATION_FRAME(0xFFFC, 0x003B, 0x0006, 0x0100),
    ANIMATION_LOOP(0),
    0, 0, /* Empty native storage. */
    /* Root 74; ROM 083F7AF0. */
    0, /* Empty native storage. */
    /* Root 75; ROM 083F7AF2. */
    0, /* Empty native storage. */
    /* Root 76; ROM 083F7AF4. */
    0, /* Empty native storage. */
    /* Root 77; ROM 083F7AF6. */
    0, /* Empty native storage. */
    /* Root 78; ROM 083F7AF8. */
    0, /* Empty native storage. */
    /* Root 79; ROM 083F7AFA. */
    0, /* Empty native storage. */
    /* Root 80; ROM 083F7AFC. */
    0, /* Empty native storage. */
    /* Root 81; ROM 083F7AFE. */
    0, /* Empty native storage. */
    /* Root 82; ROM 083F7B00. */
    0, /* Empty native storage. */
    /* Root 83; ROM 083F7B02. */
    0, /* Empty native storage. */
    /* Root 84; ROM 083F7B04. */
    0, /* Empty native storage. */
    /* Root 85; ROM 083F7B06. */
    0, /* Empty native storage. */
    /* Root 86; ROM 083F7B08. */
    0, /* Empty native storage. */
    /* Root 87; ROM 083F7B0A. */
    0, /* Empty native storage. */
    /* Root 88; ROM 083F7B0C. */
    0, /* Empty native storage. */
    /* Root 89; ROM 083F7B0E. */
    0, /* Empty native storage. */
    /* Root 90; ROM 083F7B10. */
    0, /* Empty native storage. */
    /* Root 91; ROM 083F7B12. */
    0, /* Empty native storage. */
    /* Root 92; ROM 083F7B14. */
    0, /* Empty native storage. */
    /* Root 93; ROM 083F7B16. */
    0, /* Empty native storage. */
    /* Root 94; ROM 083F7B18. */
    0, /* Empty native storage. */
    /* Root 95; ROM 083F7B1A. */
    0, /* Empty native storage. */
    /* Root 96; ROM 083F7B1C. */
    ANIMATION_FRAME(0xFFFA, 0x0000, 0x0008, 0x0000),
    ANIMATION_FRAME(0xFFFA, 0x0000, 0x0008, 0x0003),
    ANIMATION_FRAME(0xFFFA, 0x0000, 0x0008, 0x0006),
    ANIMATION_FRAME(0xFFFA, 0x0000, 0x0008, 0x0009),
    ANIMATION_LOOP(0),
    /* Root 97; ROM 083F7B40. */
    0, /* Empty native storage. */
    /* Root 98; ROM 083F7B42. */
    0, /* Empty native storage. */
    /* Root 99; ROM 083F7B44. */
    0, /* Empty native storage. */
    /* Root 100; ROM 083F7B46. */
    0, /* Empty native storage. */
    /* Root 101; ROM 083F7B48. */
    0, /* Empty native storage. */
    /* Root 102; ROM 083F7B4A. */
    0, /* Empty native storage. */
    /* Root 103; ROM 083F7B4C. */
    0, /* Empty native storage. */
    /* Root 104; ROM 083F7B4E. */
    0, /* Empty native storage. */
    /* Root 105; ROM 083F7B50. */
    0, /* Empty native storage. */
    /* Root 106; ROM 083F7B52. */
    0, /* Empty native storage. */
    /* Root 107; ROM 083F7B54. */
    0, /* Empty native storage. */
    /* Root 108; ROM 083F7B56. */
    0, /* Empty native storage. */
    /* Root 109; ROM 083F7B58. */
    0, /* Empty native storage. */
    /* Root 110; ROM 083F7B5A. */
    0, /* Empty native storage. */
    /* Root 111; ROM 083F7B5C. */
    0, /* Empty native storage. */
    /* Root 112; ROM 083F7B5E. */
    0, /* Empty native storage. */
    /* Root 113; ROM 083F7B60. */
    0, /* Empty native storage. */
    /* Root 114; ROM 083F7B62. */
    0, /* Empty native storage. */
    /* Root 115; ROM 083F7B64. */
    0, /* Empty native storage. */
    /* Root 116; ROM 083F7B66. */
    0, /* Empty native storage. */
    /* Root 117; ROM 083F7B68. */
    0, /* Empty native storage. */
    /* Root 118; ROM 083F7B6A. */
    0, /* Empty native storage. */
    /* Root 119; ROM 083F7B6C. */
    0, /* Empty native storage. */
    /* Root 120; ROM 083F7B6E. */
    0, /* Empty native storage. */
    /* Root 121; ROM 083F7B70. */
    0, /* Empty native storage. */
    /* Root 122; ROM 083F7B72. */
    0, /* Empty native storage. */
    /* Root 123; ROM 083F7B74. */
    0, /* Empty native storage. */
    /* Root 124; ROM 083F7B76. */
    0, /* Empty native storage. */
    /* Root 125; ROM 083F7B78. */
    0, /* Empty native storage. */
    /* Root 126; ROM 083F7B7A. */
    0, /* Empty native storage. */
    /* Root 127; ROM 083F7B7C. */
    0, 0, /* Empty native storage. */
};

const u16 *const gUnknown_083F7B80[128] = {
    &gSceneAnimationWords_083F704C[0], /* 0 */
    &gSceneAnimationWords_083F704C[18], /* 1 */
    &gSceneAnimationWords_083F704C[36], /* 2 */
    &gSceneAnimationWords_083F704C[54], /* 3 */
    &gSceneAnimationWords_083F704C[72], /* 4 */
    &gSceneAnimationWords_083F704C[90], /* 5 */
    &gSceneAnimationWords_083F704C[108], /* 6 */
    &gSceneAnimationWords_083F704C[126], /* 7 */
    &gSceneAnimationWords_083F704C[144], /* 8 */
    &gSceneAnimationWords_083F704C[162], /* 9 */
    &gSceneAnimationWords_083F704C[180], /* 10 */
    &gSceneAnimationWords_083F704C[198], /* 11 */
    &gSceneAnimationWords_083F704C[216], /* 12 */
    &gSceneAnimationWords_083F704C[234], /* 13 */
    &gSceneAnimationWords_083F704C[252], /* 14 */
    &gSceneAnimationWords_083F704C[270], /* 15 */
    &gSceneAnimationWords_083F704C[288], /* 16 */
    &gSceneAnimationWords_083F704C[306], /* 17 */
    &gSceneAnimationWords_083F704C[324], /* 18 */
    &gSceneAnimationWords_083F704C[342], /* 19 */
    &gSceneAnimationWords_083F704C[360], /* 20 */
    &gSceneAnimationWords_083F704C[378], /* 21 */
    &gSceneAnimationWords_083F704C[396], /* 22 */
    &gSceneAnimationWords_083F704C[414], /* 23 */
    &gSceneAnimationWords_083F704C[432], /* 24 */
    &gSceneAnimationWords_083F704C[450], /* 25 */
    &gSceneAnimationWords_083F704C[468], /* 26 */
    &gSceneAnimationWords_083F704C[486], /* 27 */
    &gSceneAnimationWords_083F704C[504], /* 28 */
    &gSceneAnimationWords_083F704C[522], /* 29 */
    &gSceneAnimationWords_083F704C[540], /* 30 */
    &gSceneAnimationWords_083F704C[558], /* 31 */
    &gSceneAnimationWords_083F704C[576], /* 32 */
    &gSceneAnimationWords_083F704C[594], /* 33 */
    &gSceneAnimationWords_083F704C[612], /* 34 */
    &gSceneAnimationWords_083F704C[630], /* 35 */
    &gSceneAnimationWords_083F704C[648], /* 36 */
    &gSceneAnimationWords_083F704C[666], /* 37 */
    &gSceneAnimationWords_083F704C[684], /* 38 */
    &gSceneAnimationWords_083F704C[702], /* 39 */
    &gSceneAnimationWords_083F704C[720], /* 40 */
    &gSceneAnimationWords_083F704C[738], /* 41 */
    &gSceneAnimationWords_083F704C[756], /* 42 */
    &gSceneAnimationWords_083F704C[774], /* 43 */
    &gSceneAnimationWords_083F704C[792], /* 44 */
    &gSceneAnimationWords_083F704C[810], /* 45 */
    &gSceneAnimationWords_083F704C[828], /* 46 */
    &gSceneAnimationWords_083F704C[846], /* 47 */
    &gSceneAnimationWords_083F704C[864], /* 48 */
    &gSceneAnimationWords_083F704C[884], /* 49 */
    &gSceneAnimationWords_083F704C[904], /* 50 */
    &gSceneAnimationWords_083F704C[912], /* 51 */
    &gSceneAnimationWords_083F704C[913], /* 52 */
    &gSceneAnimationWords_083F704C[914], /* 53 */
    &gSceneAnimationWords_083F704C[915], /* 54 */
    &gSceneAnimationWords_083F704C[1047], /* 55 */
    &gSceneAnimationWords_083F704C[1067], /* 56 */
    &gSceneAnimationWords_083F704C[1087], /* 57 */
    &gSceneAnimationWords_083F704C[1107], /* 58 */
    &gSceneAnimationWords_083F704C[1127], /* 59 */
    &gSceneAnimationWords_083F704C[1151], /* 60 */
    &gSceneAnimationWords_083F704C[1171], /* 61 */
    &gSceneAnimationWords_083F704C[1191], /* 62 */
    &gSceneAnimationWords_083F704C[1199], /* 63 */
    &gSceneAnimationWords_083F704C[1207], /* 64 */
    &gSceneAnimationWords_083F704C[1215], /* 65 */
    &gSceneAnimationWords_083F704C[1251], /* 66 */
    &gSceneAnimationWords_083F704C[1279], /* 67 */
    &gSceneAnimationWords_083F704C[1299], /* 68 */
    &gSceneAnimationWords_083F704C[1300], /* 69 */
    &gSceneAnimationWords_083F704C[1301], /* 70 */
    &gSceneAnimationWords_083F704C[1302], /* 71 */
    &gSceneAnimationWords_083F704C[1326], /* 72 */
    &gSceneAnimationWords_083F704C[1334], /* 73 */
    &gSceneAnimationWords_083F704C[1362], /* 74 */
    &gSceneAnimationWords_083F704C[1363], /* 75 */
    &gSceneAnimationWords_083F704C[1364], /* 76 */
    &gSceneAnimationWords_083F704C[1365], /* 77 */
    &gSceneAnimationWords_083F704C[1366], /* 78 */
    &gSceneAnimationWords_083F704C[1367], /* 79 */
    &gSceneAnimationWords_083F704C[1368], /* 80 */
    &gSceneAnimationWords_083F704C[1369], /* 81 */
    &gSceneAnimationWords_083F704C[1370], /* 82 */
    &gSceneAnimationWords_083F704C[1371], /* 83 */
    &gSceneAnimationWords_083F704C[1372], /* 84 */
    &gSceneAnimationWords_083F704C[1373], /* 85 */
    &gSceneAnimationWords_083F704C[1374], /* 86 */
    &gSceneAnimationWords_083F704C[1375], /* 87 */
    &gSceneAnimationWords_083F704C[1376], /* 88 */
    &gSceneAnimationWords_083F704C[1377], /* 89 */
    &gSceneAnimationWords_083F704C[1378], /* 90 */
    &gSceneAnimationWords_083F704C[1379], /* 91 */
    &gSceneAnimationWords_083F704C[1380], /* 92 */
    &gSceneAnimationWords_083F704C[1381], /* 93 */
    &gSceneAnimationWords_083F704C[1382], /* 94 */
    &gSceneAnimationWords_083F704C[1383], /* 95 */
    &gSceneAnimationWords_083F704C[1384], /* 96 */
    &gSceneAnimationWords_083F704C[1402], /* 97 */
    &gSceneAnimationWords_083F704C[1403], /* 98 */
    &gSceneAnimationWords_083F704C[1404], /* 99 */
    &gSceneAnimationWords_083F704C[1405], /* 100 */
    &gSceneAnimationWords_083F704C[1406], /* 101 */
    &gSceneAnimationWords_083F704C[1407], /* 102 */
    &gSceneAnimationWords_083F704C[1408], /* 103 */
    &gSceneAnimationWords_083F704C[1409], /* 104 */
    &gSceneAnimationWords_083F704C[1410], /* 105 */
    &gSceneAnimationWords_083F704C[1411], /* 106 */
    &gSceneAnimationWords_083F704C[1412], /* 107 */
    &gSceneAnimationWords_083F704C[1413], /* 108 */
    &gSceneAnimationWords_083F704C[1414], /* 109 */
    &gSceneAnimationWords_083F704C[1415], /* 110 */
    &gSceneAnimationWords_083F704C[1416], /* 111 */
    &gSceneAnimationWords_083F704C[1417], /* 112 */
    &gSceneAnimationWords_083F704C[1418], /* 113 */
    &gSceneAnimationWords_083F704C[1419], /* 114 */
    &gSceneAnimationWords_083F704C[1420], /* 115 */
    &gSceneAnimationWords_083F704C[1421], /* 116 */
    &gSceneAnimationWords_083F704C[1422], /* 117 */
    &gSceneAnimationWords_083F704C[1423], /* 118 */
    &gSceneAnimationWords_083F704C[1424], /* 119 */
    &gSceneAnimationWords_083F704C[1425], /* 120 */
    &gSceneAnimationWords_083F704C[1426], /* 121 */
    &gSceneAnimationWords_083F704C[1427], /* 122 */
    &gSceneAnimationWords_083F704C[1428], /* 123 */
    &gSceneAnimationWords_083F704C[1429], /* 124 */
    &gSceneAnimationWords_083F704C[1430], /* 125 */
    &gSceneAnimationWords_083F704C[1431], /* 126 */
    &gSceneAnimationWords_083F704C[1432], /* 127 */
};

#undef ANIMATION_FRAME
#undef ANIMATION_LOOP
#undef ANIMATION_STOP
