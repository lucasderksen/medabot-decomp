#include "sound_work.h"
#include "sound_sequences.h"

/* Headers are followed by one stream pointer per selected channel. */
struct SoundSongStreams1 { struct SoundSongHeader header; const u8 *streams[1]; };
struct SoundSongStreams2 { struct SoundSongHeader header; const u8 *streams[2]; };
struct SoundSongStreams3 { struct SoundSongHeader header; const u8 *streams[3]; };
struct SoundSongStreams6 { struct SoundSongHeader header; const u8 *streams[6]; };
struct SoundSongStreams12 { struct SoundSongHeader header; const u8 *streams[12]; };

extern const u8 gSoundStream_080B0804[];
extern const u8 gSoundStream_080B0809[];
extern const u8 gSoundStream_080B080A[];
extern const u8 gSoundStream_080B080B[];
extern const u8 gSoundStream_080B0813[];
extern const u8 gSoundStream_080B0814[];
extern const u8 gSoundStream_080B081C[];
extern const u8 gSoundStream_080B0EB0[];
extern const u8 gSoundStream_080B0EB1[];
extern const u8 gSoundStream_080B0EB7[];
extern const u8 gSoundStream_080B0EB8[];
extern const u8 gSoundStream_080B0EBE[];
extern const u8 gSoundStream_080B0EC4[];
extern const u8 gSoundStream_080B0ECA[];
extern const u8 gSoundStream_080B0ED0[];
extern const u8 gSoundStream_080B0ED6[];
extern const u8 gSoundStream_080B0EDE[];
extern const u8 gSoundStream_080B0EE4[];
extern const u8 gSoundStream_080B0EEA[];
extern const u8 gSoundStream_080B0EF0[];
extern const u8 gSoundStream_080B0F14[];
extern const u8 gSoundStream_080B0F23[];
extern const u8 gSoundStream_080B0F40[];
extern const u8 gSoundStream_080B0F5B[];
extern const u8 gSoundStream_080B0F7D[];
extern const u8 gSoundStream_080B0F8F[];
extern const u8 gSoundStream_080B0F97[];
extern const u8 gSoundStream_080B0FFB[];
extern const u8 gSoundStream_080B104D[];
extern const u8 gSoundStream_080B1053[];
extern const u8 gSoundStream_080B1059[];
extern const u8 gSoundStream_080B105F[];
extern const u8 gSoundStream_080B109C[];
extern const u8 gSoundStream_080B10B0[];
extern const u8 gSoundStream_080B10D0[];
extern const u8 gSoundStream_080B10D6[];
extern const u8 gSoundStream_080B10DC[];
extern const u8 gSoundStream_080B10E1[];
extern const u8 gSoundStream_080B10F8[];
extern const u8 gSoundStream_080B1102[];
extern const u8 gSoundStream_080B1108[];
extern const u8 gSoundStream_080B1120[];
extern const u8 gSoundStream_080B112D[];
extern const u8 gSoundStream_080B113B[];
extern const u8 gSoundStream_080B1141[];
extern const u8 gSoundStream_080B1147[];
extern const u8 gSoundStream_080B1151[];
extern const u8 gSoundStream_080B1157[];
extern const u8 gSoundStream_080B115D[];
extern const u8 gSoundStream_080B115E[];
extern const u8 gSoundStream_080B1166[];
extern const u8 gSoundStream_080B116C[];
extern const u8 gSoundStream_080B1172[];
extern const u8 gSoundStream_080B1178[];
extern const u8 gSoundStream_080B117E[];
extern const u8 gSoundStream_080B1184[];
extern const u8 gSoundStream_080B11B5[];
extern const u8 gSoundStream_080B11D0[];
extern const u8 gSoundStream_080B11D6[];
extern const u8 gSoundStream_080B11DC[];
extern const u8 gSoundStream_080B11E2[];
extern const u8 gSoundStream_080B1208[];
extern const u8 gSoundStream_080B120E[];
extern const u8 gSoundStream_080B1214[];
extern const u8 gSoundStream_080B121A[];
extern const u8 gSoundStream_080B1220[];
extern const u8 gSoundStream_080B1226[];
extern const u8 gSoundStream_080B1227[];
extern const u8 gSoundStream_080B122D[];
extern const u8 gSoundStream_080B1233[];
extern const u8 gSoundStream_080B1256[];
extern const u8 gSoundStream_080B125C[];
extern const u8 gSoundStream_080B1262[];
extern const u8 gSoundStream_080B1268[];
extern const u8 gSoundStream_080B126E[];
extern const u8 gSoundStream_080B1274[];
extern const u8 gSoundStream_080B1282[];
extern const u8 gSoundStream_080B129C[];
extern const u8 gSoundStream_080B12AC[];
extern const u8 gSoundStream_080B12C6[];
extern const u8 gSoundStream_080B12D9[];
extern const u8 gSoundStream_080B12DF[];
extern const u8 gSoundStream_080B1303[];
extern const u8 gSoundStream_080B131A[];
extern const u8 gSoundStream_080B131B[];
extern const u8 gSoundStream_080B1321[];
extern const u8 gSoundStream_080B1327[];
extern const u8 gSoundStream_080B132D[];
extern const u8 gSoundStream_080B1333[];
extern const u8 gSoundStream_080B1334[];
extern const u8 gSoundStream_080B1344[];
extern const u8 gSoundStream_080B134A[];
extern const u8 gSoundStream_080B1350[];
extern const u8 gSoundStream_080B1356[];
extern const u8 gSoundStream_080B135C[];
extern const u8 gSoundStream_080B1366[];
extern const u8 gSoundStream_080B1367[];
extern const u8 gSoundStream_080B13AA[];
extern const u8 gSoundStream_080B13B0[];
extern const u8 gSoundStream_080B13B6[];
extern const u8 gSoundStream_080B13BC[];
extern const u8 gSoundStream_080B13BD[];
extern const u8 gSoundStream_080B13FA[];
extern const u8 gSoundStream_080B140B[];
extern const u8 gSoundStream_080B140C[];
extern const u8 gSoundStream_080B140D[];
extern const u8 gSoundStream_080B1415[];
extern const u8 gSoundStream_080B141B[];
extern const u8 gSoundStream_080B1431[];
extern const u8 gSoundStream_080B1442[];
extern const u8 gSoundStream_080B1447[];
extern const u8 gSoundStream_080B145A[];
extern const u8 gSoundStream_080B1460[];
extern const u8 gSoundStream_080B147E[];
extern const u8 gSoundStream_080B149B[];
extern const u8 gSoundStream_080B14D8[];
extern const u8 gSoundStream_080B14EC[];
extern const u8 gSoundStream_080B1516[];
extern const u8 gSoundStream_080B151C[];
extern const u8 gSoundStream_080B153F[];
extern const u8 gSoundStream_080B1540[];
extern const u8 gSoundStream_080B1541[];
extern const u8 gSoundStream_080B1547[];
extern const u8 gSoundStream_080B1554[];
extern const u8 gSoundStream_080B1568[];
extern const u8 gSoundStream_080B157A[];
extern const u8 gSoundStream_080B15A4[];
extern const u8 gSoundStream_080B15C0[];
extern const u8 gSoundStream_080B15D4[];
extern const u8 gSoundStream_080B15DA[];
extern const u8 gSoundStream_080B15F0[];
extern const u8 gSoundStream_080B1608[];
extern const u8 gSoundStream_080B161C[];
extern const u8 gSoundStream_080B162E[];
extern const u8 gSoundStream_080B1643[];
extern const u8 gSoundStream_080B1649[];
extern const u8 gSoundStream_080B164F[];
extern const u8 gSoundStream_080B1655[];
extern const u8 gSoundStream_080B165B[];
extern const u8 gSoundStream_080B1661[];
extern const u8 gSoundStream_080B1667[];
extern const u8 gSoundStream_080B166D[];
extern const u8 gSoundStream_080B1673[];
extern const u8 gSoundStream_080B1681[];
extern const u8 gSoundStream_080B1687[];
extern const u8 gSoundStream_080B168D[];
extern const u8 gSoundStream_080B169B[];
extern const u8 gSoundStream_080B16A3[];
extern const u8 gSoundStream_080B16BE[];
extern const u8 gSoundStream_080B16D1[];
extern const u8 gSoundStream_080B16DC[];
extern const u8 gSoundStream_080B213B[];
extern const u8 gSoundStream_080B2574[];
extern const u8 gSoundStream_080B2F25[];
extern const u8 gSoundStream_080B313A[];
extern const u8 gSoundStream_080B313B[];
extern const u8 gSoundStream_080B3414[];
extern const u8 gSoundStream_080B3A56[];
extern const u8 gSoundStream_080B40CE[];
extern const u8 gSoundStream_080B41AC[];
extern const u8 gSoundStream_080B4764[];
extern const u8 gSoundStream_080B556A[];
extern const u8 gSoundStream_080B62A1[];
extern const u8 gSoundStream_080B63F1[];
extern const u8 gSoundStream_080B65B7[];
extern const u8 gSoundStream_080B70F6[];
extern const u8 gSoundStream_080B7BD9[];
extern const u8 gSoundStream_080B8B54[];
extern const u8 gSoundStream_080BA055[];
extern const u8 gSoundStream_080BAA44[];
extern const u8 gSoundStream_080BAD16[];
extern const u8 gSoundStream_080BB19F[];
extern const u8 gSoundStream_080BB309[];

const struct SoundSongStreams12 gSoundSong_080B0204 = {
    {0xFFF, 0xF0, 0x00},
    {
        gSoundStream_080B0809, gSoundStream_080B0809, gSoundStream_080B0809, gSoundStream_080B0809,
        gSoundStream_080B0809, gSoundStream_080B0809, gSoundStream_080B0809, gSoundStream_080B0809,
        gSoundStream_080B0804, gSoundStream_080B0804, gSoundStream_080B0804, gSoundStream_080B0804,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0238 = {
    {0xF0C, 0xF0, 0x00},
    {
        gSoundStream_080B0809, gSoundStream_080B0809, gSoundStream_080B0809, gSoundStream_080B0809,
        gSoundStream_080B0804, gSoundStream_080B0804,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0254 = {
    {0xF0C, 0xC0, 0x00},
    {
        gSoundStream_080B080A, gSoundStream_080B080A, gSoundStream_080B080A, gSoundStream_080B080A,
        gSoundStream_080B080B, gSoundStream_080B080A,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0270 = {
    {0xF0C, 0xC0, 0x00},
    {
        gSoundStream_080B0813, gSoundStream_080B0813, gSoundStream_080B0813, gSoundStream_080B0813,
        gSoundStream_080B0814, gSoundStream_080B0813,
    }
};

const struct SoundSongStreams6 gSoundSong_080B028C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B8D30 + 0x0, (const u8 *)&gSoundSequence_080B8D30 + 0x2A1, (const u8 *)&gSoundSequence_080B8D30 + 0x3B2, (const u8 *)&gSoundSequence_080B8D30 + 0x597,
        (const u8 *)&gSoundSequence_080B8D30 + 0x78D, (const u8 *)&gSoundSequence_080B8D30 + 0x95B,
    }
};

const struct SoundSongStreams6 gSoundSong_080B02A8 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BA1C0 + 0x0, (const u8 *)&gSoundSequence_080BA1C0 + 0x49F, gSoundStream_080BAA44, gSoundStream_080BAD16,
        gSoundStream_080BB19F, gSoundStream_080BB309,
    }
};

const struct SoundSongStreams6 gSoundSong_080B02C4 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BDF60 + 0x0, (const u8 *)&gSoundSequence_080BDF60 + 0xD2, (const u8 *)&gSoundSequence_080BDF60 + 0xFC, (const u8 *)&gSoundSequence_080BDF60 + 0x15F,
        (const u8 *)&gSoundSequence_080BDF60 + 0x1D2, (const u8 *)&gSoundSequence_080BDF60 + 0x287,
    }
};

const struct SoundSongStreams6 gSoundSong_080B02E0 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BDB90 + 0x0, (const u8 *)&gSoundSequence_080BDB90 + 0xC4, (const u8 *)&gSoundSequence_080BDB90 + 0x162, (const u8 *)&gSoundSequence_080BDB90 + 0x207,
        (const u8 *)&gSoundSequence_080BDB90 + 0x2B6, (const u8 *)&gSoundSequence_080BDB90 + 0x367,
    }
};

const struct SoundSongStreams6 gSoundSong_080B02FC = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B5CF0 + 0x0, (const u8 *)&gSoundSequence_080B5CF0 + 0xAB, (const u8 *)&gSoundSequence_080B5CF0 + 0x1C7, (const u8 *)&gSoundSequence_080B5CF0 + 0x30C,
        (const u8 *)&gSoundSequence_080B5CF0 + 0x355, (const u8 *)&gSoundSequence_080B5CF0 + 0x408,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0318 = {
    {0xF0C, 0xC0, 0x00},
    {
        gSoundStream_080B081C, gSoundStream_080B081C, gSoundStream_080B081C, gSoundStream_080B081C,
        gSoundStream_080B081C, gSoundStream_080B081C,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0334 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BBBD0 + 0x0, (const u8 *)&gSoundSequence_080BBBD0 + 0x273, (const u8 *)&gSoundSequence_080BBBD0 + 0x452, (const u8 *)&gSoundSequence_080BBBD0 + 0x5E8,
        (const u8 *)&gSoundSequence_080BBBD0 + 0x7D9, (const u8 *)&gSoundSequence_080BBBD0 + 0x9CC,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0350 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C1ED0 + 0x0, (const u8 *)&gSoundSequence_080C1ED0 + 0x37A, (const u8 *)&gSoundSequence_080C1ED0 + 0x7A8, (const u8 *)&gSoundSequence_080C1ED0 + 0xB5C,
        (const u8 *)&gSoundSequence_080C1ED0 + 0xD53, (const u8 *)&gSoundSequence_080C1ED0 + 0x1286,
    }
};

const struct SoundSongStreams6 gSoundSong_080B036C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BFA00 + 0x0, (const u8 *)&gSoundSequence_080BFA00 + 0x1CB, (const u8 *)&gSoundSequence_080BFA00 + 0x48E, (const u8 *)&gSoundSequence_080BFA00 + 0x5CF,
        (const u8 *)&gSoundSequence_080BFA00 + 0x703, (const u8 *)&gSoundSequence_080BFA00 + 0x975,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0388 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B5680 + 0x0, (const u8 *)&gSoundSequence_080B5680 + 0x193, (const u8 *)&gSoundSequence_080B5680 + 0x285, (const u8 *)&gSoundSequence_080B5680 + 0x367,
        (const u8 *)&gSoundSequence_080B5680 + 0x413, (const u8 *)&gSoundSequence_080B5680 + 0x578,
    }
};

const struct SoundSongStreams6 gSoundSong_080B03A4 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BB590 + 0x0, (const u8 *)&gSoundSequence_080BB590 + 0x217, (const u8 *)&gSoundSequence_080BB590 + 0x2FF, (const u8 *)&gSoundSequence_080BB590 + 0x3FF,
        (const u8 *)&gSoundSequence_080BB590 + 0x454, (const u8 *)&gSoundSequence_080BB590 + 0x5AD,
    }
};

const struct SoundSongStreams6 gSoundSong_080B03C0 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B6440 + 0x0, (const u8 *)&gSoundSequence_080B6440 + 0x9A, (const u8 *)&gSoundSequence_080B6440 + 0x102, gSoundStream_080B65B7,
        (const u8 *)&gSoundSequence_080B65B8 + 0x0, (const u8 *)&gSoundSequence_080B65B8 + 0x8B,
    }
};

const struct SoundSongStreams6 gSoundSong_080B03DC = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B7AE0 + 0x0, (const u8 *)&gSoundSequence_080B7AE0 + 0xA1, (const u8 *)&gSoundSequence_080B7AE0 + 0xCA, gSoundStream_080B7BD9,
        (const u8 *)&gSoundSequence_080B7BDA + 0x0, (const u8 *)&gSoundSequence_080B7BDA + 0x54,
    }
};

const struct SoundSongStreams6 gSoundSong_080B03F8 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B62A2 + 0xBE, (const u8 *)&gSoundSequence_080B62A2 + 0xF3, (const u8 *)&gSoundSequence_080B62A2 + 0x128, gSoundStream_080B63F1,
        (const u8 *)&gSoundSequence_080B63F2 + 0x0, (const u8 *)&gSoundSequence_080B63F2 + 0x21,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0414 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B8680 + 0x0, (const u8 *)&gSoundSequence_080B8680 + 0x1D, (const u8 *)&gSoundSequence_080B8680 + 0x3A, (const u8 *)&gSoundSequence_080B8680 + 0x53,
        (const u8 *)&gSoundSequence_080B8680 + 0x5A, (const u8 *)&gSoundSequence_080B8680 + 0x73,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0430 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B2E70 + 0x0, (const u8 *)&gSoundSequence_080B2E70 + 0x38, (const u8 *)&gSoundSequence_080B2E70 + 0x7D, gSoundStream_080B2F25,
        (const u8 *)&gSoundSequence_080B2F26 + 0x0, (const u8 *)&gSoundSequence_080B2F26 + 0x28,
    }
};

const struct SoundSongStreams6 gSoundSong_080B044C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BF5C0 + 0x0, (const u8 *)&gSoundSequence_080BF5C0 + 0x8E, (const u8 *)&gSoundSequence_080BF5C0 + 0x12C, (const u8 *)&gSoundSequence_080BF5C0 + 0x232,
        (const u8 *)&gSoundSequence_080BF5C0 + 0x335, (const u8 *)&gSoundSequence_080BF5C0 + 0x3AB,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0468 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B7F40 + 0x0, (const u8 *)&gSoundSequence_080B7F40 + 0x1A7, (const u8 *)&gSoundSequence_080B7F40 + 0x28D, (const u8 *)&gSoundSequence_080B7F40 + 0x41A,
        (const u8 *)&gSoundSequence_080B7F40 + 0x5A1, (const u8 *)&gSoundSequence_080B7F40 + 0x676,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0484 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B26C0 + 0x0, (const u8 *)&gSoundSequence_080B26C0 + 0x149, (const u8 *)&gSoundSequence_080B26C0 + 0x28F, (const u8 *)&gSoundSequence_080B26C0 + 0x3F2,
        (const u8 *)&gSoundSequence_080B26C0 + 0x483, (const u8 *)&gSoundSequence_080B26C0 + 0x6CB,
    }
};

const struct SoundSongStreams6 gSoundSong_080B04A0 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B3240 + 0x0, (const u8 *)&gSoundSequence_080B3240 + 0xFB, (const u8 *)&gSoundSequence_080B3240 + 0x1A7, gSoundStream_080B3414,
        (const u8 *)&gSoundSequence_080B3415 + 0x0, (const u8 *)&gSoundSequence_080B3415 + 0x66,
    }
};

const struct SoundSongStreams6 gSoundSong_080B04BC = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C1300 + 0x0, (const u8 *)&gSoundSequence_080C1300 + 0x13C, (const u8 *)&gSoundSequence_080C1300 + 0x288, (const u8 *)&gSoundSequence_080C1300 + 0x3E0,
        (const u8 *)&gSoundSequence_080C1300 + 0x5BB, (const u8 *)&gSoundSequence_080C1300 + 0x741,
    }
};

const struct SoundSongStreams6 gSoundSong_080B04D8 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B7C90 + 0x0, (const u8 *)&gSoundSequence_080B7C90 + 0x7A, (const u8 *)&gSoundSequence_080B7C90 + 0xEE, (const u8 *)&gSoundSequence_080B7C90 + 0x171,
        (const u8 *)&gSoundSequence_080B7C90 + 0x1D8, (const u8 *)&gSoundSequence_080B7C90 + 0x222,
    }
};

const struct SoundSongStreams6 gSoundSong_080B04F4 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B97D0 + 0x0, (const u8 *)&gSoundSequence_080B97D0 + 0xB1, (const u8 *)&gSoundSequence_080B97D0 + 0x162, (const u8 *)&gSoundSequence_080B97D0 + 0x194,
        (const u8 *)&gSoundSequence_080B97D0 + 0x194, (const u8 *)&gSoundSequence_080B97D0 + 0x1C9,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0510 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B9EC0 + 0x0, (const u8 *)&gSoundSequence_080B9EC0 + 0xBF, (const u8 *)&gSoundSequence_080B9EC0 + 0x11B, gSoundStream_080BA055,
        (const u8 *)&gSoundSequence_080BA056 + 0x0, (const u8 *)&gSoundSequence_080BA056 + 0xBD,
    }
};

const struct SoundSongStreams6 gSoundSong_080B052C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C3170 + 0x0, (const u8 *)&gSoundSequence_080C3170 + 0x168, (const u8 *)&gSoundSequence_080C3170 + 0x21E, (const u8 *)&gSoundSequence_080C3170 + 0x309,
        (const u8 *)&gSoundSequence_080C3170 + 0x3DC, (const u8 *)&gSoundSequence_080C3170 + 0x50F,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0548 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C1300 + 0x890, (const u8 *)&gSoundSequence_080C1300 + 0x93E, (const u8 *)&gSoundSequence_080C1300 + 0x99A, (const u8 *)&gSoundSequence_080C1300 + 0xA49,
        (const u8 *)&gSoundSequence_080C1300 + 0xAD0, (const u8 *)&gSoundSequence_080C1300 + 0xB5D,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0564 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B6690 + 0x0, (const u8 *)&gSoundSequence_080B6690 + 0x34E, (const u8 *)&gSoundSequence_080B6690 + 0x6B9, gSoundStream_080B70F6,
        (const u8 *)&gSoundSequence_080B70F7 + 0x0, (const u8 *)&gSoundSequence_080B70F7 + 0x5A3,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0580 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B3D30 + 0x0, (const u8 *)&gSoundSequence_080B3D30 + 0x104, gSoundStream_080B40CE, gSoundStream_080B41AC,
        (const u8 *)&gSoundSequence_080B41AD + 0x0, (const u8 *)&gSoundSequence_080B41AD + 0xA4,
    }
};

const struct SoundSongStreams6 gSoundSong_080B059C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C06B0 + 0x0, (const u8 *)&gSoundSequence_080C06B0 + 0x25B, (const u8 *)&gSoundSequence_080C06B0 + 0x329, (const u8 *)&gSoundSequence_080C06B0 + 0x45D,
        (const u8 *)&gSoundSequence_080C06B0 + 0x5E8, (const u8 *)&gSoundSequence_080C06B0 + 0x83A,
    }
};

const struct SoundSongStreams6 gSoundSong_080B05B8 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B4380 + 0x0, (const u8 *)&gSoundSequence_080B4380 + 0x170, (const u8 *)&gSoundSequence_080B4380 + 0x276, gSoundStream_080B4764,
        (const u8 *)&gSoundSequence_080B4765 + 0x0, (const u8 *)&gSoundSequence_080B4765 + 0x167,
    }
};

const struct SoundSongStreams6 gSoundSong_080B05D4 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C0FA0 + 0x0, (const u8 *)&gSoundSequence_080C0FA0 + 0x137, (const u8 *)&gSoundSequence_080C0FA0 + 0x1E8, (const u8 *)&gSoundSequence_080C0FA0 + 0x255,
        (const u8 *)&gSoundSequence_080C0FA0 + 0x2B6, (const u8 *)&gSoundSequence_080C0FA0 + 0x304,
    }
};

const struct SoundSongStreams6 gSoundSong_080B05F0 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B2F90 + 0x0, (const u8 *)&gSoundSequence_080B313C + 0xD4, gSoundStream_080B313A, gSoundStream_080B313B,
        (const u8 *)&gSoundSequence_080B313C + 0x0, (const u8 *)&gSoundSequence_080B2F90 + 0xD6,
    }
};

const struct SoundSongStreams6 gSoundSong_080B060C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BC720 + 0x0, (const u8 *)&gSoundSequence_080BC720 + 0x25B, (const u8 *)&gSoundSequence_080BC720 + 0x3F3, (const u8 *)&gSoundSequence_080BC720 + 0x577,
        (const u8 *)&gSoundSequence_080BC720 + 0x7D6, (const u8 *)&gSoundSequence_080BC720 + 0x9D2,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0628 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B8700 + 0x0, (const u8 *)&gSoundSequence_080B8700 + 0x279, (const u8 *)&gSoundSequence_080B8700 + 0x374, gSoundStream_080B8B54,
        (const u8 *)&gSoundSequence_080B8BD0 + 0x0, (const u8 *)&gSoundSequence_080B8BD0 + 0x96,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0644 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B49D0 + 0x0, (const u8 *)&gSoundSequence_080B49D0 + 0x123, (const u8 *)&gSoundSequence_080B49D0 + 0x1EF, (const u8 *)&gSoundSequence_080B49D0 + 0x283,
        (const u8 *)&gSoundSequence_080B49D0 + 0x2B4, (const u8 *)&gSoundSequence_080B49D0 + 0x3B6,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0660 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BE210 + 0x0, (const u8 *)&gSoundSequence_080BE210 + 0x245, (const u8 *)&gSoundSequence_080BE210 + 0x46D, (const u8 *)&gSoundSequence_080BE210 + 0x58B,
        (const u8 *)&gSoundSequence_080BE210 + 0x5BE, (const u8 *)&gSoundSequence_080BE210 + 0x8CD,
    }
};

const struct SoundSongStreams6 gSoundSong_080B067C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BF130 + 0x0, (const u8 *)&gSoundSequence_080BF130 + 0x96, (const u8 *)&gSoundSequence_080BF130 + 0x13C, (const u8 *)&gSoundSequence_080BF130 + 0x230,
        (const u8 *)&gSoundSequence_080BF130 + 0x339, (const u8 *)&gSoundSequence_080BF130 + 0x400,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0698 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B4E30 + 0x0, (const u8 *)&gSoundSequence_080B4E30 + 0xD0, (const u8 *)&gSoundSequence_080B4E30 + 0x1BC, (const u8 *)&gSoundSequence_080B4E30 + 0x290,
        (const u8 *)&gSoundSequence_080B5214 + 0x0, (const u8 *)&gSoundSequence_080B5214 + 0x7F,
    }
};

const struct SoundSongStreams6 gSoundSong_080B06B4 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B99E0 + 0x0, (const u8 *)&gSoundSequence_080B99E0 + 0xF8, (const u8 *)&gSoundSequence_080B99E0 + 0x1B6, (const u8 *)&gSoundSequence_080B99E0 + 0x2B1,
        (const u8 *)&gSoundSequence_080B99E0 + 0x3B8, (const u8 *)&gSoundSequence_080B99E0 + 0x422,
    }
};

const struct SoundSongStreams6 gSoundSong_080B06D0 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B19E0 + 0x0, (const u8 *)&gSoundSequence_080B19E0 + 0xB0, (const u8 *)&gSoundSequence_080B19E0 + 0x1CE, (const u8 *)&gSoundSequence_080B19E0 + 0x287,
        (const u8 *)&gSoundSequence_080B19E0 + 0x3E0, (const u8 *)&gSoundSequence_080B19E0 + 0x49B,
    }
};

const struct SoundSongStreams6 gSoundSong_080B06EC = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B1F20 + 0x0, (const u8 *)&gSoundSequence_080B1F20 + 0xBD, (const u8 *)&gSoundSequence_080B1F20 + 0x171, gSoundStream_080B213B,
        (const u8 *)&gSoundSequence_080B213C + 0x0, (const u8 *)&gSoundSequence_080B213C + 0xFC,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0708 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B6180 + 0x0, (const u8 *)&gSoundSequence_080B6180 + 0x73, (const u8 *)&gSoundSequence_080B6180 + 0xF3, gSoundStream_080B62A1,
        (const u8 *)&gSoundSequence_080B62A2 + 0x0, (const u8 *)&gSoundSequence_080B62A2 + 0x6E,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0724 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B22E0 + 0x0, (const u8 *)&gSoundSequence_080B22E0 + 0xA7, (const u8 *)&gSoundSequence_080B22E0 + 0x19D, gSoundStream_080B2574,
        (const u8 *)&gSoundSequence_080B2575 + 0x0, (const u8 *)&gSoundSequence_080B2575 + 0xB2,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0740 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BEB20 + 0x0, (const u8 *)&gSoundSequence_080BEB20 + 0x191, (const u8 *)&gSoundSequence_080BEB20 + 0x266, (const u8 *)&gSoundSequence_080BEB20 + 0x3A5,
        (const u8 *)&gSoundSequence_080BEB20 + 0x44C, (const u8 *)&gSoundSequence_080BEB20 + 0x537,
    }
};

const struct SoundSongStreams6 gSoundSong_080B075C = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B34F0 + 0x0, (const u8 *)&gSoundSequence_080B34F0 + 0x1D9, (const u8 *)&gSoundSequence_080B34F0 + 0x341, gSoundStream_080B3A56,
        (const u8 *)&gSoundSequence_080B3A57 + 0x0, (const u8 *)&gSoundSequence_080B3A57 + 0x197,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0778 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080B5340 + 0x0, (const u8 *)&gSoundSequence_080B5340 + 0xC8, (const u8 *)&gSoundSequence_080B5340 + 0x1C4, gSoundStream_080B556A,
        (const u8 *)&gSoundSequence_080B556B + 0x0, (const u8 *)&gSoundSequence_080B556B + 0x80,
    }
};

const struct SoundSongStreams6 gSoundSong_080B0794 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080BD280 + 0x0, (const u8 *)&gSoundSequence_080BD280 + 0x18C, (const u8 *)&gSoundSequence_080BD280 + 0x2F4, (const u8 *)&gSoundSequence_080BD280 + 0x439,
        (const u8 *)&gSoundSequence_080BD280 + 0x460, (const u8 *)&gSoundSequence_080BD280 + 0x778,
    }
};

const struct SoundSongStreams6 gSoundSong_080B07B0 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C3720 + 0x0, (const u8 *)&gSoundSequence_080C3720 + 0xC2, (const u8 *)&gSoundSequence_080C3720 + 0x14C, (const u8 *)&gSoundSequence_080C3720 + 0x1A0,
        (const u8 *)&gSoundSequence_080C3720 + 0x259, (const u8 *)&gSoundSequence_080C3720 + 0x2FE,
    }
};

const struct SoundSongStreams6 gSoundSong_080B07CC = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C3AA0 + 0xD20, (const u8 *)&gSoundSequence_080C3AA0 + 0xE7C, (const u8 *)&gSoundSequence_080C3AA0 + 0x121C, (const u8 *)&gSoundSequence_080C3AA0 + 0x136B,
        (const u8 *)&gSoundSequence_080C3AA0 + 0x13B2, (const u8 *)&gSoundSequence_080C3AA0 + 0x1498,
    }
};

const struct SoundSongStreams6 gSoundSong_080B07E8 = {
    {0xF0C, 0xC0, 0x00},
    {
        (const u8 *)&gSoundSequence_080C3AA0 + 0x0, (const u8 *)&gSoundSequence_080C3AA0 + 0x2FB, (const u8 *)&gSoundSequence_080C3AA0 + 0x51D, (const u8 *)&gSoundSequence_080C3AA0 + 0x742,
        (const u8 *)&gSoundSequence_080C3AA0 + 0x9E8, (const u8 *)&gSoundSequence_080C3AA0 + 0xBEC,
    }
};

const struct SoundSongStreams3 gSoundSong_080B0A60 = {
    {0x091, 0xFF, 0x00},
    {
        gSoundStream_080B0EB0, gSoundStream_080B0EB0, gSoundStream_080B0EB0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0A70 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0EB1,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0A78 = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B0EB0, gSoundStream_080B0EB0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0A84 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0EB7,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0A8C = {
    {0x001, 0x20, 0x00},
    {
        gSoundStream_080B0EB8,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0A94 = {
    {0x001, 0x20, 0x00},
    {
        gSoundStream_080B0EBE,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0A9C = {
    {0x001, 0x20, 0x00},
    {
        gSoundStream_080B0EC4,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AA4 = {
    {0x001, 0x20, 0x00},
    {
        gSoundStream_080B0ECA,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AAC = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0ED0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AB4 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0ED6,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0ABC = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0EDE,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AC4 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0EE4,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0ACC = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0EEA,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AD4 = {
    {0x010, 0x10, 0x00},
    {
        gSoundStream_080B0EF0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0ADC = {
    {0x080, 0x07, 0x00},
    {
        gSoundStream_080B0F14,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AE4 = {
    {0x080, 0x30, 0x00},
    {
        gSoundStream_080B0F23,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AEC = {
    {0x080, 0x30, 0x00},
    {
        gSoundStream_080B0F40,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AF4 = {
    {0x080, 0x30, 0x00},
    {
        gSoundStream_080B0F5B,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0AFC = {
    {0x010, 0x30, 0x00},
    {
        gSoundStream_080B0F7D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B04 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B0F8F,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B0C = {
    {0x010, 0x40, 0x00},
    {
        gSoundStream_080B0F97,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B14 = {
    {0x010, 0x40, 0x00},
    {
        gSoundStream_080B0FFB,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B1C = {
    {0x001, 0x30, 0x00},
    {
        gSoundStream_080B104D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B24 = {
    {0x001, 0x30, 0x00},
    {
        gSoundStream_080B1053,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B2C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1059,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B34 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B105F,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B3C = {
    {0x010, 0x20, 0x00},
    {
        gSoundStream_080B109C,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B44 = {
    {0x080, 0x50, 0x00},
    {
        gSoundStream_080B10B0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B4C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B10D0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B54 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B10D6,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B5C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B10DC,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B64 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B10E1,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B6C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B10F8,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B74 = {
    {0x001, 0x20, 0x00},
    {
        gSoundStream_080B1102,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0B7C = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B1108, gSoundStream_080B1120,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B88 = {
    {0x010, 0x10, 0x00},
    {
        gSoundStream_080B112D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B90 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B113B,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0B98 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1141,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BA0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1147,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BA8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1151,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BB0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1157,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BB8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B115D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BC0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B115E,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BC8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1166,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BD0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B116C,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BD8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1172,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BE0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1178,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BE8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B117E,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BF0 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B1184,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0BF8 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B11B5,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C00 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B11D0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C08 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B11D6,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C10 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B11DC,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0C18 = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B11E2, gSoundStream_080B1208,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C24 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B120E,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C2C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1214,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C34 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B121A,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C3C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1220,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C44 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1226,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C4C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1227,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C54 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B122D,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0C5C = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B1233, gSoundStream_080B1256,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C68 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B125C,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C70 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1262,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C78 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1268,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C80 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B126E,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0C88 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1274,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0C90 = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B1282, gSoundStream_080B129C,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0C9C = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B12AC, gSoundStream_080B12C6,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CA8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B12D9,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CB0 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B12DF,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CB8 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B1303,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CC0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B131A,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CC8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B131B,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CD0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1321,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CD8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1327,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CE0 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B132D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CE8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1333,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0CF0 = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B1334, gSoundStream_080B1344,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0CFC = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B134A,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D04 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1350,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D0C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1356,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D14 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B135C,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D1C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1366,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D24 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B1367,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D2C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B13AA,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D34 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B13B0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D3C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B13B6,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D44 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B13BC,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0D4C = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B13BD, gSoundStream_080B13FA,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0D58 = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B140B, gSoundStream_080B140C,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D64 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B140D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D6C = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1415,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D74 = {
    {0x010, 0x10, 0x00},
    {
        gSoundStream_080B141B,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0D7C = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B1431, gSoundStream_080B1442,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0D88 = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B1447, gSoundStream_080B145A,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D94 = {
    {0x010, 0x30, 0x00},
    {
        gSoundStream_080B1460,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0D9C = {
    {0x080, 0x50, 0x00},
    {
        gSoundStream_080B147E,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DA4 = {
    {0x080, 0x30, 0x00},
    {
        gSoundStream_080B149B,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DAC = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B14D8,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0DB4 = {
    {0x081, 0x10, 0x00},
    {
        gSoundStream_080B14EC, gSoundStream_080B1516,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DC0 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B151C,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0DC8 = {
    {0x090, 0x10, 0x00},
    {
        gSoundStream_080B153F, gSoundStream_080B1540,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DD4 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1541,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DDC = {
    {0x010, 0x30, 0x00},
    {
        gSoundStream_080B1547,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DE4 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B1554,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DEC = {
    {0x080, 0x30, 0x00},
    {
        gSoundStream_080B1568,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0DF4 = {
    {0x080, 0x30, 0x00},
    {
        gSoundStream_080B157A,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0DFC = {
    {0x090, 0x30, 0x00},
    {
        gSoundStream_080B15A4, gSoundStream_080B15C0,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E08 = {
    {0x001, 0x20, 0x00},
    {
        gSoundStream_080B15D4,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E10 = {
    {0x010, 0x10, 0x00},
    {
        gSoundStream_080B15DA,
    }
};

const struct SoundSongStreams3 gSoundSong_080B0E18 = {
    {0x083, 0x50, 0x00},
    {
        gSoundStream_080B15F0, gSoundStream_080B1608, gSoundStream_080B161C,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E28 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B162E,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E30 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1643,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E38 = {
    {0x001, 0x05, 0x00},
    {
        gSoundStream_080B1649,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E40 = {
    {0x001, 0x05, 0x00},
    {
        gSoundStream_080B164F,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E48 = {
    {0x001, 0x05, 0x00},
    {
        gSoundStream_080B1655,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E50 = {
    {0x001, 0x05, 0x00},
    {
        gSoundStream_080B165B,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E58 = {
    {0x001, 0x07, 0x00},
    {
        gSoundStream_080B1661,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E60 = {
    {0x001, 0x50, 0x00},
    {
        gSoundStream_080B1667,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E68 = {
    {0x001, 0x50, 0x00},
    {
        gSoundStream_080B166D,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E70 = {
    {0x080, 0x07, 0x00},
    {
        gSoundStream_080B1673,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E78 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1681,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E80 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B1687,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0E88 = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B168D, gSoundStream_080B169B,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0E94 = {
    {0x080, 0x10, 0x00},
    {
        gSoundStream_080B16A3,
    }
};

const struct SoundSongStreams2 gSoundSong_080B0E9C = {
    {0x011, 0x10, 0x00},
    {
        gSoundStream_080B16BE, gSoundStream_080B16D1,
    }
};

const struct SoundSongStreams1 gSoundSong_080B0EA8 = {
    {0x001, 0x10, 0x00},
    {
        gSoundStream_080B16DC,
    }
};

const struct SoundSongHeader *const gSoundMusicBank[54] = {
    &gSoundSong_080B0204.header, &gSoundSong_080B0238.header, &gSoundSong_080B0254.header, &gSoundSong_080B0270.header,
    &gSoundSong_080B028C.header, &gSoundSong_080B02A8.header, &gSoundSong_080B02C4.header, &gSoundSong_080B02E0.header,
    &gSoundSong_080B02FC.header, &gSoundSong_080B0334.header, &gSoundSong_080B0350.header, &gSoundSong_080B036C.header,
    &gSoundSong_080B0388.header, &gSoundSong_080B03A4.header, &gSoundSong_080B03C0.header, &gSoundSong_080B03DC.header,
    &gSoundSong_080B03F8.header, &gSoundSong_080B0414.header, &gSoundSong_080B0430.header, &gSoundSong_080B044C.header,
    &gSoundSong_080B0468.header, &gSoundSong_080B0484.header, &gSoundSong_080B04A0.header, &gSoundSong_080B04BC.header,
    &gSoundSong_080B04D8.header, &gSoundSong_080B04F4.header, &gSoundSong_080B0510.header, &gSoundSong_080B052C.header,
    &gSoundSong_080B0548.header, &gSoundSong_080B0564.header, &gSoundSong_080B0580.header, &gSoundSong_080B059C.header,
    &gSoundSong_080B05B8.header, &gSoundSong_080B05D4.header, &gSoundSong_080B05F0.header, &gSoundSong_080B060C.header,
    &gSoundSong_080B0628.header, &gSoundSong_080B0644.header, &gSoundSong_080B0660.header, &gSoundSong_080B067C.header,
    &gSoundSong_080B0698.header, &gSoundSong_080B06B4.header, &gSoundSong_080B06D0.header, &gSoundSong_080B06EC.header,
    &gSoundSong_080B0708.header, &gSoundSong_080B0724.header, &gSoundSong_080B0740.header, &gSoundSong_080B075C.header,
    &gSoundSong_080B0778.header, &gSoundSong_080B0794.header, &gSoundSong_080B07B0.header, &gSoundSong_080B07CC.header,
    &gSoundSong_080B07E8.header, &gSoundSong_080B0318.header,
};

const struct SoundSongHeader *const gSoundEffectBank[128] = {
    &gSoundSong_080B0A60.header, &gSoundSong_080B0A78.header, &gSoundSong_080B0A70.header, &gSoundSong_080B0A8C.header,
    &gSoundSong_080B0A94.header, &gSoundSong_080B0A9C.header, &gSoundSong_080B0AA4.header, &gSoundSong_080B0AAC.header,
    &gSoundSong_080B0AB4.header, &gSoundSong_080B0ABC.header, &gSoundSong_080B0AC4.header, &gSoundSong_080B0ACC.header,
    &gSoundSong_080B0AD4.header, &gSoundSong_080B0ADC.header, &gSoundSong_080B0AE4.header, &gSoundSong_080B0AEC.header,
    &gSoundSong_080B0AF4.header, &gSoundSong_080B0AFC.header, &gSoundSong_080B0B04.header, &gSoundSong_080B0B0C.header,
    &gSoundSong_080B0B14.header, &gSoundSong_080B0B1C.header, &gSoundSong_080B0B24.header, &gSoundSong_080B0B2C.header,
    &gSoundSong_080B0B34.header, &gSoundSong_080B0B3C.header, &gSoundSong_080B0B44.header, &gSoundSong_080B0B4C.header,
    &gSoundSong_080B0B54.header, &gSoundSong_080B0B5C.header, &gSoundSong_080B0B64.header, &gSoundSong_080B0B6C.header,
    &gSoundSong_080B0B74.header, &gSoundSong_080B0B7C.header, &gSoundSong_080B0B88.header, &gSoundSong_080B0B90.header,
    &gSoundSong_080B0B98.header, &gSoundSong_080B0BA0.header, &gSoundSong_080B0BA8.header, &gSoundSong_080B0BB0.header,
    &gSoundSong_080B0BC0.header, &gSoundSong_080B0BC8.header, &gSoundSong_080B0BD0.header, &gSoundSong_080B0BD8.header,
    &gSoundSong_080B0BE0.header, &gSoundSong_080B0BE8.header, &gSoundSong_080B0BF0.header, &gSoundSong_080B0BF8.header,
    &gSoundSong_080B0C00.header, &gSoundSong_080B0C08.header, &gSoundSong_080B0C10.header, &gSoundSong_080B0C18.header,
    &gSoundSong_080B0C24.header, &gSoundSong_080B0C2C.header, &gSoundSong_080B0C34.header, &gSoundSong_080B0C3C.header,
    &gSoundSong_080B0C4C.header, &gSoundSong_080B0C54.header, &gSoundSong_080B0C5C.header, &gSoundSong_080B0C68.header,
    &gSoundSong_080B0C70.header, &gSoundSong_080B0C78.header, &gSoundSong_080B0C80.header, &gSoundSong_080B0C88.header,
    &gSoundSong_080B0C90.header, &gSoundSong_080B0C9C.header, &gSoundSong_080B0CA8.header, &gSoundSong_080B0CB0.header,
    &gSoundSong_080B0CB8.header, &gSoundSong_080B0CC8.header, &gSoundSong_080B0CD0.header, &gSoundSong_080B0CD8.header,
    &gSoundSong_080B0CE0.header, &gSoundSong_080B0CF0.header, &gSoundSong_080B0CFC.header, &gSoundSong_080B0D04.header,
    &gSoundSong_080B0D0C.header, &gSoundSong_080B0D14.header, &gSoundSong_080B0D24.header, &gSoundSong_080B0D2C.header,
    &gSoundSong_080B0D34.header, &gSoundSong_080B0D3C.header, &gSoundSong_080B0D4C.header, &gSoundSong_080B0D64.header,
    &gSoundSong_080B0D6C.header, &gSoundSong_080B0D74.header, &gSoundSong_080B0D7C.header, &gSoundSong_080B0D88.header,
    &gSoundSong_080B0D94.header, &gSoundSong_080B0D9C.header, &gSoundSong_080B0DA4.header, &gSoundSong_080B0DAC.header,
    &gSoundSong_080B0DB4.header, &gSoundSong_080B0DC0.header, &gSoundSong_080B0DD4.header, &gSoundSong_080B0DDC.header,
    &gSoundSong_080B0DE4.header, &gSoundSong_080B0DEC.header, &gSoundSong_080B0DF4.header, &gSoundSong_080B0DFC.header,
    &gSoundSong_080B0E08.header, &gSoundSong_080B0E10.header, &gSoundSong_080B0E18.header, &gSoundSong_080B0E28.header,
    &gSoundSong_080B0E30.header, &gSoundSong_080B0E38.header, &gSoundSong_080B0E40.header, &gSoundSong_080B0E48.header,
    &gSoundSong_080B0E50.header, &gSoundSong_080B0E58.header, &gSoundSong_080B0E60.header, &gSoundSong_080B0E68.header,
    &gSoundSong_080B0E70.header, &gSoundSong_080B0E78.header, &gSoundSong_080B0E80.header, &gSoundSong_080B0E88.header,
    &gSoundSong_080B0E94.header, &gSoundSong_080B0E9C.header, &gSoundSong_080B0EA8.header, &gSoundSong_080B0A84.header,
    &gSoundSong_080B0BB8.header, &gSoundSong_080B0C44.header, &gSoundSong_080B0CC0.header, &gSoundSong_080B0CE8.header,
    &gSoundSong_080B0D1C.header, &gSoundSong_080B0D44.header, &gSoundSong_080B0D58.header, &gSoundSong_080B0DC8.header,
};
