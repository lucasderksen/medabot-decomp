#include "continued_map_data.h"
#include "bios_lz77_streams.h"

/* Native map dimensions and symbolic roots for reconstructed BIOS LZ77 payloads. */

const u8 gContinuedMapDimensions_083F8900[CONTINUED_MAP_COUNT][2] =
{
    { 58, 56 }, /* 0 */
    { 42, 32 }, /* 1 */
    { 56, 30 }, /* 2 */
    { 24, 22 }, /* 3 */
    { 24, 22 }, /* 4 */
    { 24, 22 }, /* 5 */
    { 24, 22 }, /* 6 */
    { 20, 18 }, /* 7 */
    { 24, 26 }, /* 8 */
    { 56, 30 }, /* 9 */
    { 24, 22 }, /* 10 */
    { 24, 22 }, /* 11 */
    { 24, 22 }, /* 12 */
    { 24, 22 }, /* 13 */
    { 26, 32 }, /* 14 */
    { 20, 18 }, /* 15 */
    { 20, 18 }, /* 16 */
    { 20, 18 }, /* 17 */
    { 20, 18 }, /* 18 */
    { 20, 18 }, /* 19 */
    { 20, 18 }, /* 20 */
    { 20, 18 }, /* 21 */
    { 20, 18 }, /* 22 */
    { 58, 32 }, /* 23 */
    { 40, 32 }, /* 24 */
    { 20, 32 }, /* 25 */
    { 28, 28 }, /* 26 */
    { 20, 18 }, /* 27 */
    { 32, 40 }, /* 28 */
    { 46, 46 }, /* 29 */
    { 20, 18 }, /* 30 */
    { 28, 30 }, /* 31 */
    { 20, 18 }, /* 32 */
    { 56, 54 }, /* 33 */
    { 48, 54 }, /* 34 */
    { 20, 18 }, /* 35 */
    { 44, 48 }, /* 36 */
    { 46, 44 }, /* 37 */
    { 30, 32 }, /* 38 */
    { 20, 18 }, /* 39 */
    { 32, 32 }, /* 40 */
    { 20, 18 }, /* 41 */
    { 48, 56 }, /* 42 */
    { 20, 18 }, /* 43 */
    { 28, 30 }, /* 44 */
    { 20, 18 }, /* 45 */
    { 28, 52 }, /* 46 */
    { 20, 18 }, /* 47 */
    { 20, 18 }, /* 48 */
    { 20, 18 }, /* 49 */
    { 20, 18 }, /* 50 */
    { 20, 18 }, /* 51 */
    { 20, 18 }, /* 52 */
    { 20, 18 }, /* 53 */
    { 20, 18 }, /* 54 */
    { 20, 18 }, /* 55 */
    { 26, 32 }, /* 56 */
    { 62, 56 }, /* 57 */
    { 20, 18 }, /* 58 */
    { 32, 40 }, /* 59 */
    { 20, 18 }, /* 60 */
    { 20, 18 }, /* 61 */
    { 28, 52 }, /* 62 */
    { 38, 28 }, /* 63 */
    { 38, 30 }, /* 64 */
    { 20, 32 }, /* 65 */
    { 20, 32 }, /* 66 */
    { 62, 64 }, /* 67 */
    { 30, 28 }, /* 68 */
    { 20, 18 }, /* 69 */
    { 50, 28 }, /* 70 */
    { 26, 32 }, /* 71 */
    { 26, 32 }, /* 72 */
    { 50, 28 }, /* 73 */
    { 26, 32 }, /* 74 */
    { 26, 32 }, /* 75 */
    { 50, 28 }, /* 76 */
    { 26, 32 }, /* 77 */
    { 26, 32 }, /* 78 */
    { 20, 18 }, /* 79 */
    { 54, 54 }, /* 80 */
    { 54, 54 }, /* 81 */
    { 30, 20 }, /* 82 */
    { 42, 54 }, /* 83 */
    { 32, 64 }, /* 84 */
    { 50, 52 }, /* 85 */
    { 20, 18 }, /* 86 */
    { 32, 32 }, /* 87 */
    { 32, 32 }, /* 88 */
    { 32, 32 }, /* 89 */
    { 32, 28 }, /* 90 */
    { 20, 18 }, /* 91 */
    { 20, 18 }, /* 92 */
    { 20, 18 }, /* 93 */
    { 20, 18 }, /* 94 */
    { 50, 50 }, /* 95 */
    { 32, 32 }, /* 96 */
    { 32, 32 }, /* 97 */
    { 20, 18 }, /* 98 */
    { 20, 18 }, /* 99 */
    { 20, 18 }, /* 100 */
    { 56, 52 }, /* 101 */
    { 48, 44 }, /* 102 */
    { 32, 32 }, /* 103 */
    { 32, 32 }, /* 104 */
    { 32, 32 }, /* 105 */
    { 32, 32 }, /* 106 */
    { 32, 32 }, /* 107 */
    { 20, 18 }, /* 108 */
    { 26, 32 }, /* 109 */
    { 20, 18 }, /* 110 */
    { 24, 24 }, /* 111 */
    { 48, 44 }, /* 112 */
    { 32, 32 }, /* 113 */
    { 20, 18 }, /* 114 */
    { 24, 26 }, /* 115 */
    { 32, 32 }, /* 116 */
    { 32, 32 }, /* 117 */
    { 32, 32 }, /* 118 */
    { 32, 32 }, /* 119 */
    { 20, 18 }, /* 120 */
    { 38, 36 }, /* 121 */
    { 46, 48 }, /* 122 */
    { 32, 28 }, /* 123 */
    { 20, 18 }, /* 124 */
    { 20, 18 }, /* 125 */
    { 20, 18 }, /* 126 */
    { 20, 18 }, /* 127 */
    { 56, 50 }, /* 128 */
    { 20, 18 }, /* 129 */
    { 20, 18 }, /* 130 */
    { 20, 18 }, /* 131 */
    { 20, 18 }, /* 132 */
    { 20, 18 }, /* 133 */
    { 20, 18 }, /* 134 */
    { 32, 60 }, /* 135 */
    { 32, 46 }, /* 136 */
    { 38, 46 }, /* 137 */
    { 32, 40 }, /* 138 */
    { 20, 18 }, /* 139 */
    { 20, 18 }, /* 140 */
    { 20, 18 }, /* 141 */
    { 46, 58 }, /* 142 */
    { 32, 40 }, /* 143 */
    { 32, 30 }, /* 144 */
    { 20, 18 }, /* 145 */
    { 30, 40 }, /* 146 */
    { 46, 42 }, /* 147 */
    { 20, 18 }, /* 148 */
    { 46, 60 }, /* 149 */
    { 30, 32 }, /* 150 */
    { 62, 40 }, /* 151 */
    { 42, 32 }, /* 152 */
    { 38, 30 }, /* 153 */
    { 38, 24 }, /* 154 */
    { 20, 18 }, /* 155 */
    { 20, 18 }, /* 156 */
    { 20, 18 }, /* 157 */
    { 20, 18 }, /* 158 */
    { 20, 18 }, /* 159 */
    { 20, 18 }, /* 160 */
    { 32, 32 }, /* 161 */
    { 56, 64 }, /* 162 */
    { 20, 18 }, /* 163 */
    { 20, 18 }, /* 164 */
    { 52, 42 }, /* 165 */
    { 58, 32 }, /* 166 */
    { 32, 44 }, /* 167 */
    { 32, 44 }, /* 168 */
    { 52, 42 }, /* 169 */
    { 38, 36 }, /* 170 */
    { 38, 36 }, /* 171 */
    { 30, 32 }, /* 172 */
    { 50, 56 }, /* 173 */
    { 32, 18 }, /* 174 */
    { 32, 30 }, /* 175 */
    { 32, 30 }, /* 176 */
    { 22, 28 }, /* 177 */
    { 20, 18 }, /* 178 */
    { 20, 18 }, /* 179 */
    { 20, 18 }, /* 180 */
    { 20, 18 }, /* 181 */
    { 20, 18 }, /* 182 */
    { 20, 18 }, /* 183 */
    { 32, 44 }, /* 184 */
    { 32, 44 }, /* 185 */
    { 42, 44 }, /* 186 */
    { 62, 28 }, /* 187 */
    { 28, 30 }, /* 188 */
    { 28, 30 }, /* 189 */
    { 30, 28 }, /* 190 */
    { 30, 28 }, /* 191 */
};

const void *const gContinuedMapTiles_083F8A80[CONTINUED_MAP_COUNT] =
{
    gBiosLz77Stream_085FC6AC, /* 0 */
    gBiosLz77Stream_086019D8, /* 1 */
    gBiosLz77Stream_086042EC, /* 2 */
    gBiosLz77Stream_08606430, /* 3 */
    gBiosLz77Stream_08606430, /* 4 */
    gBiosLz77Stream_08606430, /* 5 */
    gBiosLz77Stream_08606430, /* 6 */
    gBiosLz77Stream_08607CF4, /* 7 */
    gBiosLz77Stream_08608DEC, /* 8 */
    gBiosLz77Stream_0860ADF4, /* 9 */
    gBiosLz77Stream_08606430, /* 10 */
    gBiosLz77Stream_08606430, /* 11 */
    gBiosLz77Stream_08606430, /* 12 */
    gBiosLz77Stream_08606430, /* 13 */
    gBiosLz77Stream_0860CD0C, /* 14 */
    gBiosLz77Stream_0860E8BC, /* 15 */
    gBiosLz77Stream_0860F84C, /* 16 */
    gBiosLz77Stream_0861124C, /* 17 */
    gBiosLz77Stream_086124B8, /* 18 */
    gBiosLz77Stream_086124B8, /* 19 */
    gBiosLz77Stream_086124B8, /* 20 */
    gBiosLz77Stream_086124B8, /* 21 */
    gBiosLz77Stream_086124B8, /* 22 */
    gBiosLz77Stream_08614250, /* 23 */
    gBiosLz77Stream_08618068, /* 24 */
    gBiosLz77Stream_0861A69C, /* 25 */
    gBiosLz77Stream_0861C210, /* 26 */
    gBiosLz77Stream_0861DDE0, /* 27 */
    gBiosLz77Stream_0861EC60, /* 28 */
    gBiosLz77Stream_08620A44, /* 29 */
    gBiosLz77Stream_086248E8, /* 30 */
    gBiosLz77Stream_08626944, /* 31 */
    gBiosLz77Stream_086289E8, /* 32 */
    gBiosLz77Stream_08629EA0, /* 33 */
    gBiosLz77Stream_0862F2FC, /* 34 */
    gBiosLz77Stream_0863495C, /* 35 */
    gBiosLz77Stream_08636428, /* 36 */
    gBiosLz77Stream_0863AB1C, /* 37 */
    gBiosLz77Stream_0863E228, /* 38 */
    gBiosLz77Stream_08640518, /* 39 */
    gBiosLz77Stream_086424C8, /* 40 */
    gBiosLz77Stream_0863495C, /* 41 */
    gBiosLz77Stream_08645CA8, /* 42 */
    gBiosLz77Stream_0864AE78, /* 43 */
    gBiosLz77Stream_0864D560, /* 44 */
    gBiosLz77Stream_0864FA84, /* 45 */
    gBiosLz77Stream_08651380, /* 46 */
    gBiosLz77Stream_0865405C, /* 47 */
    gBiosLz77Stream_0865540C, /* 48 */
    gBiosLz77Stream_08657078, /* 49 */
    gBiosLz77Stream_086583E8, /* 50 */
    gBiosLz77Stream_08658874, /* 51 */
    gBiosLz77Stream_0865A30C, /* 52 */
    gBiosLz77Stream_0865AA04, /* 53 */
    gBiosLz77Stream_0865B7EC, /* 54 */
    gBiosLz77Stream_0865C4D4, /* 55 */
    gBiosLz77Stream_0865D70C, /* 56 */
    gBiosLz77Stream_0865FD88, /* 57 */
    gBiosLz77Stream_08665078, /* 58 */
    gBiosLz77Stream_086667C8, /* 59 */
    gBiosLz77Stream_08669EEC, /* 60 */
    gBiosLz77Stream_0866B154, /* 61 */
    gBiosLz77Stream_0866C204, /* 62 */
    gBiosLz77Stream_0866F2FC, /* 63 */
    gBiosLz77Stream_086715E4, /* 64 */
    gBiosLz77Stream_08673A54, /* 65 */
    gBiosLz77Stream_0867550C, /* 66 */
    gBiosLz77Stream_08677008, /* 67 */
    gBiosLz77Stream_0867BAB8, /* 68 */
    gBiosLz77Stream_0867DD18, /* 69 */
    gBiosLz77Stream_0867F0E8, /* 70 */
    gBiosLz77Stream_08680830, /* 71 */
    gBiosLz77Stream_08681D24, /* 72 */
    gBiosLz77Stream_0868300C, /* 73 */
    gBiosLz77Stream_0868439C, /* 74 */
    gBiosLz77Stream_08685768, /* 75 */
    gBiosLz77Stream_08686AC0, /* 76 */
    gBiosLz77Stream_08687F1C, /* 77 */
    gBiosLz77Stream_086892F0, /* 78 */
    gBiosLz77Stream_0868A644, /* 79 */
    gBiosLz77Stream_0868B228, /* 80 */
    gBiosLz77Stream_0868DFD4, /* 81 */
    gBiosLz77Stream_08690BE0, /* 82 */
    gBiosLz77Stream_086917B4, /* 83 */
    gBiosLz77Stream_08693A7C, /* 84 */
    gBiosLz77Stream_08697C18, /* 85 */
    gBiosLz77Stream_0869C9AC, /* 86 */
    gBiosLz77Stream_0869E17C, /* 87 */
    gBiosLz77Stream_086A0210, /* 88 */
    gBiosLz77Stream_086A1BD4, /* 89 */
    gBiosLz77Stream_086A3454, /* 90 */
    gBiosLz77Stream_0866B154, /* 91 */
    gBiosLz77Stream_086A5B58, /* 92 */
    gBiosLz77Stream_086A5B58, /* 93 */
    gBiosLz77Stream_086A5B58, /* 94 */
    gBiosLz77Stream_086A7330, /* 95 */
    gBiosLz77Stream_086ABE74, /* 96 */
    gBiosLz77Stream_086ADDB0, /* 97 */
    gBiosLz77Stream_086A5B58, /* 98 */
    gBiosLz77Stream_086A5B58, /* 99 */
    gBiosLz77Stream_086A5B58, /* 100 */
    gBiosLz77Stream_086AFF84, /* 101 */
    gBiosLz77Stream_086B5700, /* 102 */
    gBiosLz77Stream_086B9B98, /* 103 */
    gBiosLz77Stream_086B9B98, /* 104 */
    gBiosLz77Stream_086BB330, /* 105 */
    gBiosLz77Stream_086BB330, /* 106 */
    gBiosLz77Stream_086BCBFC, /* 107 */
    gBiosLz77Stream_086BE310, /* 108 */
    gBiosLz77Stream_086BF6A0, /* 109 */
    gBiosLz77Stream_086C129C, /* 110 */
    gBiosLz77Stream_086C2694, /* 111 */
    gBiosLz77Stream_086C5414, /* 112 */
    gBiosLz77Stream_086C985C, /* 113 */
    gBiosLz77Stream_086CBDC4, /* 114 */
    gBiosLz77Stream_086CD108, /* 115 */
    gBiosLz77Stream_086CF140, /* 116 */
    gBiosLz77Stream_086CF140, /* 117 */
    gBiosLz77Stream_086CF140, /* 118 */
    gBiosLz77Stream_086D0978, /* 119 */
    gBiosLz77Stream_086D392C, /* 120 */
    gBiosLz77Stream_086D50E4, /* 121 */
    gBiosLz77Stream_086D90B4, /* 122 */
    gBiosLz77Stream_086DDB10, /* 123 */
    gBiosLz77Stream_086248E8, /* 124 */
    gBiosLz77Stream_086124B8, /* 125 */
    gBiosLz77Stream_086124B8, /* 126 */
    gBiosLz77Stream_086124B8, /* 127 */
    gBiosLz77Stream_086DFA70, /* 128 */
    gBiosLz77Stream_086E47B4, /* 129 */
    gBiosLz77Stream_086E591C, /* 130 */
    gBiosLz77Stream_086E6A6C, /* 131 */
    gBiosLz77Stream_086E6A6C, /* 132 */
    gBiosLz77Stream_086E6A6C, /* 133 */
    gBiosLz77Stream_086E6A6C, /* 134 */
    gBiosLz77Stream_086E8628, /* 135 */
    gBiosLz77Stream_086EC290, /* 136 */
    gBiosLz77Stream_086EF314, /* 137 */
    gBiosLz77Stream_086667C8, /* 138 */
    gBiosLz77Stream_086A5B58, /* 139 */
    gBiosLz77Stream_086A5B58, /* 140 */
    gBiosLz77Stream_086A5B58, /* 141 */
    gBiosLz77Stream_086F4190, /* 142 */
    gBiosLz77Stream_086F82C4, /* 143 */
    gBiosLz77Stream_086FAE7C, /* 144 */
    gBiosLz77Stream_086FD144, /* 145 */
    gBiosLz77Stream_086FE464, /* 146 */
    gBiosLz77Stream_0870202C, /* 147 */
    gBiosLz77Stream_08706A84, /* 148 */
    gBiosLz77Stream_087084D4, /* 149 */
    gBiosLz77Stream_0870D088, /* 150 */
    gBiosLz77Stream_087100A4, /* 151 */
    gBiosLz77Stream_087149FC, /* 152 */
    gBiosLz77Stream_0871831C, /* 153 */
    gBiosLz77Stream_0871BCFC, /* 154 */
    gBiosLz77Stream_0871EFAC, /* 155 */
    gBiosLz77Stream_087214E0, /* 156 */
    gBiosLz77Stream_08722AE4, /* 157 */
    gBiosLz77Stream_08724944, /* 158 */
    gBiosLz77Stream_08724944, /* 159 */
    gBiosLz77Stream_08724944, /* 160 */
    gBiosLz77Stream_08726A5C, /* 161 */
    gBiosLz77Stream_0872AAE4, /* 162 */
    gBiosLz77Stream_0872E720, /* 163 */
    gBiosLz77Stream_087300A8, /* 164 */
    gBiosLz77Stream_08731A0C, /* 165 */
    gBiosLz77Stream_08735254, /* 166 */
    gBiosLz77Stream_08737494, /* 167 */
    gBiosLz77Stream_0873989C, /* 168 */
    gBiosLz77Stream_0873BA20, /* 169 */
    gBiosLz77Stream_0873E4EC, /* 170 */
    gBiosLz77Stream_08740B58, /* 171 */
    gBiosLz77Stream_08743914, /* 172 */
    gBiosLz77Stream_087452A0, /* 173 */
    gBiosLz77Stream_08749FB8, /* 174 */
    gBiosLz77Stream_0874B31C, /* 175 */
    gBiosLz77Stream_0874D264, /* 176 */
    gBiosLz77Stream_0874ED28, /* 177 */
    gBiosLz77Stream_0863495C, /* 178 */
    gBiosLz77Stream_0863495C, /* 179 */
    gBiosLz77Stream_0863495C, /* 180 */
    gBiosLz77Stream_087504A4, /* 181 */
    gBiosLz77Stream_087512CC, /* 182 */
    gBiosLz77Stream_087526C8, /* 183 */
    gBiosLz77Stream_08754424, /* 184 */
    gBiosLz77Stream_08755AEC, /* 185 */
    gBiosLz77Stream_08757230, /* 186 */
    gBiosLz77Stream_08758A5C, /* 187 */
    gBiosLz77Stream_0875CB00, /* 188 */
    gBiosLz77Stream_0875FD50, /* 189 */
    gBiosLz77Stream_0867BAB8, /* 190 */
    gBiosLz77Stream_0867BAB8, /* 191 */
};

const void *const gContinuedMapExtra_083F8D80[CONTINUED_MAP_COUNT] =
{
    gBiosLz77Stream_085FC23C, /* 0 */
    gBiosLz77Stream_086019CC, /* 1 */
    gBiosLz77Stream_086042E0, /* 2 */
    gBiosLz77Stream_08606424, /* 3 */
    gBiosLz77Stream_08606424, /* 4 */
    gBiosLz77Stream_08606424, /* 5 */
    gBiosLz77Stream_08606424, /* 6 */
    gBiosLz77Stream_08607CE8, /* 7 */
    gBiosLz77Stream_08608DE0, /* 8 */
    gBiosLz77Stream_0860ADE8, /* 9 */
    gBiosLz77Stream_08606424, /* 10 */
    gBiosLz77Stream_08606424, /* 11 */
    gBiosLz77Stream_08606424, /* 12 */
    gBiosLz77Stream_08606424, /* 13 */
    gBiosLz77Stream_0860CD00, /* 14 */
    gBiosLz77Stream_0860E8B0, /* 15 */
    gBiosLz77Stream_0860F840, /* 16 */
    gBiosLz77Stream_086111C4, /* 17 */
    gBiosLz77Stream_086124AC, /* 18 */
    gBiosLz77Stream_086124AC, /* 19 */
    gBiosLz77Stream_086124AC, /* 20 */
    gBiosLz77Stream_086124AC, /* 21 */
    gBiosLz77Stream_086124AC, /* 22 */
    gBiosLz77Stream_08614090, /* 23 */
    gBiosLz77Stream_08617D5C, /* 24 */
    gBiosLz77Stream_0861A50C, /* 25 */
    gBiosLz77Stream_0861BFD0, /* 26 */
    gBiosLz77Stream_0861DDD4, /* 27 */
    gBiosLz77Stream_0861EC54, /* 28 */
    gBiosLz77Stream_08620A38, /* 29 */
    gBiosLz77Stream_086248DC, /* 30 */
    gBiosLz77Stream_08626170, /* 31 */
    gBiosLz77Stream_086289DC, /* 32 */
    gBiosLz77Stream_08629784, /* 33 */
    gBiosLz77Stream_0862EC24, /* 34 */
    gBiosLz77Stream_08634950, /* 35 */
    gBiosLz77Stream_08635DCC, /* 36 */
    gBiosLz77Stream_0863A4F4, /* 37 */
    gBiosLz77Stream_0863E21C, /* 38 */
    gBiosLz77Stream_0864050C, /* 39 */
    gBiosLz77Stream_086422E8, /* 40 */
    gBiosLz77Stream_08634950, /* 41 */
    gBiosLz77Stream_0864579C, /* 42 */
    gBiosLz77Stream_0864AC98, /* 43 */
    gBiosLz77Stream_0864CF70, /* 44 */
    gBiosLz77Stream_0864F404, /* 45 */
    gBiosLz77Stream_0865120C, /* 46 */
    gBiosLz77Stream_08653E64, /* 47 */
    gBiosLz77Stream_08655400, /* 48 */
    gBiosLz77Stream_08656E04, /* 49 */
    gBiosLz77Stream_086583DC, /* 50 */
    gBiosLz77Stream_08658868, /* 51 */
    gBiosLz77Stream_0865A300, /* 52 */
    gBiosLz77Stream_0865A790, /* 53 */
    gBiosLz77Stream_0865B5F4, /* 54 */
    gBiosLz77Stream_0865C2DC, /* 55 */
    gBiosLz77Stream_0865D700, /* 56 */
    gBiosLz77Stream_0865F540, /* 57 */
    gBiosLz77Stream_0866506C, /* 58 */
    gBiosLz77Stream_086667BC, /* 59 */
    gBiosLz77Stream_08669EE0, /* 60 */
    gBiosLz77Stream_0866B148, /* 61 */
    gBiosLz77Stream_0866C1F8, /* 62 */
    gBiosLz77Stream_0866F2F0, /* 63 */
    gBiosLz77Stream_086715D8, /* 64 */
    gBiosLz77Stream_08673A48, /* 65 */
    gBiosLz77Stream_08675500, /* 66 */
    gBiosLz77Stream_08676FFC, /* 67 */
    gBiosLz77Stream_0867BAAC, /* 68 */
    gBiosLz77Stream_0867D930, /* 69 */
    gBiosLz77Stream_0867F0DC, /* 70 */
    gBiosLz77Stream_0868045C, /* 71 */
    gBiosLz77Stream_08681950, /* 72 */
    gBiosLz77Stream_08683000, /* 73 */
    gBiosLz77Stream_08684390, /* 74 */
    gBiosLz77Stream_0868575C, /* 75 */
    gBiosLz77Stream_08686AB4, /* 76 */
    gBiosLz77Stream_08687F10, /* 77 */
    gBiosLz77Stream_086892E4, /* 78 */
    gBiosLz77Stream_0868A638, /* 79 */
    gBiosLz77Stream_0868B21C, /* 80 */
    gBiosLz77Stream_0868DFC8, /* 81 */
    gBiosLz77Stream_08690BD4, /* 82 */
    gBiosLz77Stream_08691598, /* 83 */
    gBiosLz77Stream_08693668, /* 84 */
    gBiosLz77Stream_08697BC0, /* 85 */
    gBiosLz77Stream_0869C9A0, /* 86 */
    gBiosLz77Stream_0869E170, /* 87 */
    gBiosLz77Stream_086A0000, /* 88 */
    gBiosLz77Stream_086A1BC8, /* 89 */
    gBiosLz77Stream_086A341C, /* 90 */
    gBiosLz77Stream_0866B148, /* 91 */
    gBiosLz77Stream_086A5B4C, /* 92 */
    gBiosLz77Stream_086A5B4C, /* 93 */
    gBiosLz77Stream_086A5B4C, /* 94 */
    gBiosLz77Stream_086A718C, /* 95 */
    gBiosLz77Stream_086ABD8C, /* 96 */
    gBiosLz77Stream_086ADCF8, /* 97 */
    gBiosLz77Stream_086A5B4C, /* 98 */
    gBiosLz77Stream_086A5B4C, /* 99 */
    gBiosLz77Stream_086A5B4C, /* 100 */
    gBiosLz77Stream_086AFAD0, /* 101 */
    gBiosLz77Stream_086B56F4, /* 102 */
    gBiosLz77Stream_086B9B8C, /* 103 */
    gBiosLz77Stream_086B9B8C, /* 104 */
    gBiosLz77Stream_086BB324, /* 105 */
    gBiosLz77Stream_086BB324, /* 106 */
    gBiosLz77Stream_086BCBF0, /* 107 */
    gBiosLz77Stream_086BE304, /* 108 */
    gBiosLz77Stream_086BF694, /* 109 */
    gBiosLz77Stream_086C1290, /* 110 */
    gBiosLz77Stream_086C2688, /* 111 */
    gBiosLz77Stream_086C5408, /* 112 */
    gBiosLz77Stream_086C9850, /* 113 */
    gBiosLz77Stream_086CBDB8, /* 114 */
    gBiosLz77Stream_086CD0FC, /* 115 */
    gBiosLz77Stream_086CF134, /* 116 */
    gBiosLz77Stream_086CF134, /* 117 */
    gBiosLz77Stream_086CF134, /* 118 */
    gBiosLz77Stream_086D096C, /* 119 */
    gBiosLz77Stream_086D3920, /* 120 */
    gBiosLz77Stream_086D50D8, /* 121 */
    gBiosLz77Stream_086D8CB8, /* 122 */
    gBiosLz77Stream_086DDB04, /* 123 */
    gBiosLz77Stream_086248DC, /* 124 */
    gBiosLz77Stream_086124AC, /* 125 */
    gBiosLz77Stream_086124AC, /* 126 */
    gBiosLz77Stream_086124AC, /* 127 */
    gBiosLz77Stream_086DFA64, /* 128 */
    gBiosLz77Stream_086E47A8, /* 129 */
    gBiosLz77Stream_086E5910, /* 130 */
    gBiosLz77Stream_086E6A60, /* 131 */
    gBiosLz77Stream_086E6A60, /* 132 */
    gBiosLz77Stream_086E6A60, /* 133 */
    gBiosLz77Stream_086E6A60, /* 134 */
    gBiosLz77Stream_086E83DC, /* 135 */
    gBiosLz77Stream_086EBFA0, /* 136 */
    gBiosLz77Stream_086EEF78, /* 137 */
    gBiosLz77Stream_086667BC, /* 138 */
    gBiosLz77Stream_086A5B4C, /* 139 */
    gBiosLz77Stream_086A5B4C, /* 140 */
    gBiosLz77Stream_086A5B4C, /* 141 */
    gBiosLz77Stream_086F3B28, /* 142 */
    gBiosLz77Stream_086F8124, /* 143 */
    gBiosLz77Stream_086FAE70, /* 144 */
    gBiosLz77Stream_086FD138, /* 145 */
    gBiosLz77Stream_086FE458, /* 146 */
    gBiosLz77Stream_08702020, /* 147 */
    gBiosLz77Stream_08706A78, /* 148 */
    gBiosLz77Stream_08708374, /* 149 */
    gBiosLz77Stream_0870CF28, /* 150 */
    gBiosLz77Stream_0870FD9C, /* 151 */
    gBiosLz77Stream_08714480, /* 152 */
    gBiosLz77Stream_08717D4C, /* 153 */
    gBiosLz77Stream_0871BA14, /* 154 */
    gBiosLz77Stream_0871EB88, /* 155 */
    gBiosLz77Stream_08720D24, /* 156 */
    gBiosLz77Stream_08722AD8, /* 157 */
    gBiosLz77Stream_08724938, /* 158 */
    gBiosLz77Stream_08724938, /* 159 */
    gBiosLz77Stream_08724938, /* 160 */
    gBiosLz77Stream_0872672C, /* 161 */
    gBiosLz77Stream_08729E6C, /* 162 */
    gBiosLz77Stream_0872DDC4, /* 163 */
    gBiosLz77Stream_0872F84C, /* 164 */
    gBiosLz77Stream_08731A00, /* 165 */
    gBiosLz77Stream_08735248, /* 166 */
    gBiosLz77Stream_08736FA0, /* 167 */
    gBiosLz77Stream_087393A8, /* 168 */
    gBiosLz77Stream_0873B52C, /* 169 */
    gBiosLz77Stream_0873DFF8, /* 170 */
    gBiosLz77Stream_087409B0, /* 171 */
    gBiosLz77Stream_0874369C, /* 172 */
    gBiosLz77Stream_08745294, /* 173 */
    gBiosLz77Stream_08749EE4, /* 174 */
    gBiosLz77Stream_0874B310, /* 175 */
    gBiosLz77Stream_0874CFD8, /* 176 */
    gBiosLz77Stream_0874EBBC, /* 177 */
    gBiosLz77Stream_08634950, /* 178 */
    gBiosLz77Stream_08634950, /* 179 */
    gBiosLz77Stream_08634950, /* 180 */
    gBiosLz77Stream_08750498, /* 181 */
    gBiosLz77Stream_087511F0, /* 182 */
    gBiosLz77Stream_087526BC, /* 183 */
    gBiosLz77Stream_08753F30, /* 184 */
    gBiosLz77Stream_087555F8, /* 185 */
    gBiosLz77Stream_08756D3C, /* 186 */
    gBiosLz77Stream_08758A50, /* 187 */
    gBiosLz77Stream_0875C32C, /* 188 */
    gBiosLz77Stream_0875F760, /* 189 */
    gBiosLz77Stream_0867BAAC, /* 190 */
    gBiosLz77Stream_0867BAAC, /* 191 */
};

const void *const gContinuedMapData_083F9080[CONTINUED_MAP_COUNT][3] =
{
    { gBiosLz77Stream_08600058, gBiosLz77Stream_08600570, gBiosLz77Stream_08600F50 }, /* 0 */
    { gBiosLz77Stream_086037B0, gBiosLz77Stream_0860393C, gBiosLz77Stream_08603D48 }, /* 1 */
    { gBiosLz77Stream_086058DC, gBiosLz77Stream_08605AD4, gBiosLz77Stream_08605F10 }, /* 2 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 3 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 4 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 5 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 6 */
    { gBiosLz77Stream_086087A8, gBiosLz77Stream_086088D0, gBiosLz77Stream_08608AA8 }, /* 7 */
    { gBiosLz77Stream_0860A64C, gBiosLz77Stream_0860A75C, gBiosLz77Stream_0860AA64 }, /* 8 */
    { gBiosLz77Stream_0860C248, gBiosLz77Stream_0860C404, gBiosLz77Stream_0860C7FC }, /* 9 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 10 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 11 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 12 */
    { gBiosLz77Stream_08607660, gBiosLz77Stream_08607740, gBiosLz77Stream_08607930 }, /* 13 */
    { gBiosLz77Stream_0860E0F4, gBiosLz77Stream_0860E24C, gBiosLz77Stream_0860E4CC }, /* 14 */
    { gBiosLz77Stream_0860F1FC, gBiosLz77Stream_0860F338, gBiosLz77Stream_0860F4FC }, /* 15 */
    { gBiosLz77Stream_08610AA0, gBiosLz77Stream_08610BCC, gBiosLz77Stream_08610DE0 }, /* 16 */
    { gBiosLz77Stream_08611E04, gBiosLz77Stream_08611F24, gBiosLz77Stream_08612148 }, /* 17 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 18 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 19 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 20 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 21 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 22 */
    { gBiosLz77Stream_08616DB8, gBiosLz77Stream_08617028, gBiosLz77Stream_08617654 }, /* 23 */
    { gBiosLz77Stream_08619A6C, gBiosLz77Stream_08619C28, gBiosLz77Stream_08619FF0 }, /* 24 */
    { gBiosLz77Stream_0861B7C4, gBiosLz77Stream_0861B908, gBiosLz77Stream_0861BBE4 }, /* 25 */
    { gBiosLz77Stream_0861D5F0, gBiosLz77Stream_0861D748, gBiosLz77Stream_0861D9F4 }, /* 26 */
    { gBiosLz77Stream_0861E664, gBiosLz77Stream_0861E75C, gBiosLz77Stream_0861E924 }, /* 27 */
    { gBiosLz77Stream_08620114, gBiosLz77Stream_086202EC, gBiosLz77Stream_086205B4 }, /* 28 */
    { gBiosLz77Stream_086237B0, gBiosLz77Stream_08623B44, gBiosLz77Stream_08624258 }, /* 29 */
    { gBiosLz77Stream_08625A74, gBiosLz77Stream_08625B94, gBiosLz77Stream_08625DDC }, /* 30 */
    { gBiosLz77Stream_08628164, gBiosLz77Stream_086282C4, gBiosLz77Stream_086285A4 }, /* 31 */
    { gBiosLz77Stream_08629198, gBiosLz77Stream_0862929C, gBiosLz77Stream_08629468 }, /* 32 */
    { gBiosLz77Stream_0862D294, gBiosLz77Stream_0862D68C, gBiosLz77Stream_0862DE1C }, /* 33 */
    { gBiosLz77Stream_08633108, gBiosLz77Stream_086334A0, gBiosLz77Stream_08633B90 }, /* 34 */
    { gBiosLz77Stream_086356FC, gBiosLz77Stream_0863581C, gBiosLz77Stream_08635A54 }, /* 35 */
    { gBiosLz77Stream_086392BC, gBiosLz77Stream_08639590, gBiosLz77Stream_08639CB8 }, /* 36 */
    { gBiosLz77Stream_0863D0CC, gBiosLz77Stream_0863D398, gBiosLz77Stream_0863D9E4 }, /* 37 */
    { gBiosLz77Stream_0863FC18, gBiosLz77Stream_0863FD8C, gBiosLz77Stream_086400E0 }, /* 38 */
    { gBiosLz77Stream_08641B34, gBiosLz77Stream_08641CB4, gBiosLz77Stream_08641F50 }, /* 39 */
    { gBiosLz77Stream_08644C00, gBiosLz77Stream_08644D88, gBiosLz77Stream_086450E4 }, /* 40 */
    { gBiosLz77Stream_086356FC, gBiosLz77Stream_0863581C, gBiosLz77Stream_08635A54 }, /* 41 */
    { gBiosLz77Stream_08649478, gBiosLz77Stream_086497B8, gBiosLz77Stream_08649F10 }, /* 42 */
    { gBiosLz77Stream_0864C818, gBiosLz77Stream_0864C958, gBiosLz77Stream_0864CB48 }, /* 43 */
    { gBiosLz77Stream_0864EBA4, gBiosLz77Stream_0864ED74, gBiosLz77Stream_0864EFE8 }, /* 44 */
    { gBiosLz77Stream_08650A88, gBiosLz77Stream_08650B88, gBiosLz77Stream_08650DA8 }, /* 45 */
    { gBiosLz77Stream_08653248, gBiosLz77Stream_08653580, gBiosLz77Stream_08653914 }, /* 46 */
    { gBiosLz77Stream_08654D74, gBiosLz77Stream_08654EA4, gBiosLz77Stream_086550A0 }, /* 47 */
    { gBiosLz77Stream_08656714, gBiosLz77Stream_0865683C, gBiosLz77Stream_08656A24 }, /* 48 */
    { gBiosLz77Stream_08657D8C, gBiosLz77Stream_08657EBC, gBiosLz77Stream_086580A8 }, /* 49 */
    { gBiosLz77Stream_08658408, gBiosLz77Stream_086584F0, gBiosLz77Stream_086585D8 }, /* 50 */
    { gBiosLz77Stream_08659BE4, gBiosLz77Stream_08659D04, gBiosLz77Stream_08659EBC }, /* 51 */
    { gBiosLz77Stream_0865A32C, gBiosLz77Stream_0865A414, gBiosLz77Stream_0865A4FC }, /* 52 */
    { gBiosLz77Stream_0865B04C, gBiosLz77Stream_0865B174, gBiosLz77Stream_0865B2D8 }, /* 53 */
    { gBiosLz77Stream_0865BD90, gBiosLz77Stream_0865BE8C, gBiosLz77Stream_0865BFD0 }, /* 54 */
    { gBiosLz77Stream_0865D0C4, gBiosLz77Stream_0865D1EC, gBiosLz77Stream_0865D3BC }, /* 55 */
    { gBiosLz77Stream_0865ED04, gBiosLz77Stream_0865EE54, gBiosLz77Stream_0865F158 }, /* 56 */
    { gBiosLz77Stream_086638C4, gBiosLz77Stream_08663DDC, gBiosLz77Stream_086646B8 }, /* 57 */
    { gBiosLz77Stream_08666074, gBiosLz77Stream_0866618C, gBiosLz77Stream_086663D4 }, /* 58 */
    { gBiosLz77Stream_08669270, gBiosLz77Stream_086694B4, gBiosLz77Stream_086698CC }, /* 59 */
    { gBiosLz77Stream_0866AAE4, gBiosLz77Stream_0866AC18, gBiosLz77Stream_0866ADCC }, /* 60 */
    { gBiosLz77Stream_0866BB80, gBiosLz77Stream_0866BCA4, gBiosLz77Stream_0866BE70 }, /* 61 */
    { gBiosLz77Stream_0866E680, gBiosLz77Stream_0866E930, gBiosLz77Stream_0866EDE0 }, /* 62 */
    { gBiosLz77Stream_08670C4C, gBiosLz77Stream_08670DB4, gBiosLz77Stream_0867103C }, /* 63 */
    { gBiosLz77Stream_08673008, gBiosLz77Stream_086731AC, gBiosLz77Stream_08673480 }, /* 64 */
    { gBiosLz77Stream_08674D74, gBiosLz77Stream_08674EA4, gBiosLz77Stream_086750D4 }, /* 65 */
    { gBiosLz77Stream_08676850, gBiosLz77Stream_08676964, gBiosLz77Stream_08676B94 }, /* 66 */
    { gBiosLz77Stream_0867A024, gBiosLz77Stream_0867A51C, gBiosLz77Stream_0867AF70 }, /* 67 */
    { gBiosLz77Stream_0867D0B0, gBiosLz77Stream_0867D1F4, gBiosLz77Stream_0867D410 }, /* 68 */
    { gBiosLz77Stream_0867EAEC, gBiosLz77Stream_0867EC20, gBiosLz77Stream_0867ED58 }, /* 69 */
    { gBiosLz77Stream_0867FBCC, gBiosLz77Stream_0867FD8C, gBiosLz77Stream_0867FFE0 }, /* 70 */
    { gBiosLz77Stream_086812C0, gBiosLz77Stream_086813E8, gBiosLz77Stream_0868151C }, /* 71 */
    { gBiosLz77Stream_08682968, gBiosLz77Stream_08682A88, gBiosLz77Stream_08682BE0 }, /* 72 */
    { gBiosLz77Stream_08683B48, gBiosLz77Stream_08683CCC, gBiosLz77Stream_08683EE0 }, /* 73 */
    { gBiosLz77Stream_0868507C, gBiosLz77Stream_086851C0, gBiosLz77Stream_08685378 }, /* 74 */
    { gBiosLz77Stream_086863C0, gBiosLz77Stream_0868650C, gBiosLz77Stream_086866B4 }, /* 75 */
    { gBiosLz77Stream_08687694, gBiosLz77Stream_08687820, gBiosLz77Stream_08687A48 }, /* 76 */
    { gBiosLz77Stream_08688BFC, gBiosLz77Stream_08688D48, gBiosLz77Stream_08688F00 }, /* 77 */
    { gBiosLz77Stream_08689F48, gBiosLz77Stream_0868A090, gBiosLz77Stream_0868A238 }, /* 78 */
    { gBiosLz77Stream_0868AC80, gBiosLz77Stream_0868AD84, gBiosLz77Stream_0868AEA4 }, /* 79 */
    { gBiosLz77Stream_0868CF74, gBiosLz77Stream_0868D2B8, gBiosLz77Stream_0868D82C }, /* 80 */
    { gBiosLz77Stream_0868FAD4, gBiosLz77Stream_0868FE3C, gBiosLz77Stream_08690480 }, /* 81 */
    { gBiosLz77Stream_0869110C, gBiosLz77Stream_086911C0, gBiosLz77Stream_08691270 }, /* 82 */
    { gBiosLz77Stream_08692990, gBiosLz77Stream_08692C34, gBiosLz77Stream_08692F6C }, /* 83 */
    { gBiosLz77Stream_08696B1C, gBiosLz77Stream_08696E74, gBiosLz77Stream_08697448 }, /* 84 */
    { gBiosLz77Stream_0869B3BC, gBiosLz77Stream_0869B8C0, gBiosLz77Stream_0869C288 }, /* 85 */
    { gBiosLz77Stream_0869DA70, gBiosLz77Stream_0869DB88, gBiosLz77Stream_0869DD30 }, /* 86 */
    { gBiosLz77Stream_0869F754, gBiosLz77Stream_0869F8AC, gBiosLz77Stream_0869FB48 }, /* 87 */
    { gBiosLz77Stream_086A1440, gBiosLz77Stream_086A1574, gBiosLz77Stream_086A17C4 }, /* 88 */
    { gBiosLz77Stream_086A2C14, gBiosLz77Stream_086A2D5C, gBiosLz77Stream_086A2F6C }, /* 89 */
    { gBiosLz77Stream_086A519C, gBiosLz77Stream_086A52EC, gBiosLz77Stream_086A55B4 }, /* 90 */
    { gBiosLz77Stream_0866BB80, gBiosLz77Stream_0866BCA4, gBiosLz77Stream_0866BE70 }, /* 91 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 92 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 93 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 94 */
    { gBiosLz77Stream_086AA840, gBiosLz77Stream_086AAD18, gBiosLz77Stream_086AB6B0 }, /* 95 */
    { gBiosLz77Stream_086AD36C, gBiosLz77Stream_086AD4E4, gBiosLz77Stream_086AD798 }, /* 96 */
    { gBiosLz77Stream_086AF1D8, gBiosLz77Stream_086AF330, gBiosLz77Stream_086AF5B8 }, /* 97 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 98 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 99 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 100 */
    { gBiosLz77Stream_086B3BB0, gBiosLz77Stream_086B41EC, gBiosLz77Stream_086B4D74 }, /* 101 */
    { gBiosLz77Stream_086B8B34, gBiosLz77Stream_086B8E5C, gBiosLz77Stream_086B92B8 }, /* 102 */
    { gBiosLz77Stream_086BABAC, gBiosLz77Stream_086BACE0, gBiosLz77Stream_086BAF14 }, /* 103 */
    { gBiosLz77Stream_086BABAC, gBiosLz77Stream_086BACE0, gBiosLz77Stream_086BAF14 }, /* 104 */
    { gBiosLz77Stream_086BC40C, gBiosLz77Stream_086BC564, gBiosLz77Stream_086BC7BC }, /* 105 */
    { gBiosLz77Stream_086BC40C, gBiosLz77Stream_086BC564, gBiosLz77Stream_086BC7BC }, /* 106 */
    { gBiosLz77Stream_086BDBD0, gBiosLz77Stream_086BDCF0, gBiosLz77Stream_086BDF24 }, /* 107 */
    { gBiosLz77Stream_086BF02C, gBiosLz77Stream_086BF170, gBiosLz77Stream_086BF30C }, /* 108 */
    { gBiosLz77Stream_086C0A7C, gBiosLz77Stream_086C0BD4, gBiosLz77Stream_086C0E80 }, /* 109 */
    { gBiosLz77Stream_086C1FF8, gBiosLz77Stream_086C215C, gBiosLz77Stream_086C2300 }, /* 110 */
    { gBiosLz77Stream_086C4BA4, gBiosLz77Stream_086C4CE8, gBiosLz77Stream_086C4F80 }, /* 111 */
    { gBiosLz77Stream_086C8714, gBiosLz77Stream_086C89F0, gBiosLz77Stream_086C8E04 }, /* 112 */
    { gBiosLz77Stream_086CB464, gBiosLz77Stream_086CB5B4, gBiosLz77Stream_086CB874 }, /* 113 */
    { gBiosLz77Stream_086CCADC, gBiosLz77Stream_086CCBDC, gBiosLz77Stream_086CCD60 }, /* 114 */
    { gBiosLz77Stream_086CE9A8, gBiosLz77Stream_086CEAA0, gBiosLz77Stream_086CED08 }, /* 115 */
    { gBiosLz77Stream_086D0228, gBiosLz77Stream_086D0348, gBiosLz77Stream_086D057C }, /* 116 */
    { gBiosLz77Stream_086D0228, gBiosLz77Stream_086D0348, gBiosLz77Stream_086D057C }, /* 117 */
    { gBiosLz77Stream_086D0228, gBiosLz77Stream_086D0348, gBiosLz77Stream_086D057C }, /* 118 */
    { gBiosLz77Stream_086D2E1C, gBiosLz77Stream_086D2F94, gBiosLz77Stream_086D331C }, /* 119 */
    { gBiosLz77Stream_086D4A18, gBiosLz77Stream_086D4B38, gBiosLz77Stream_086D4CFC }, /* 120 */
    { gBiosLz77Stream_086D7FB0, gBiosLz77Stream_086D8168, gBiosLz77Stream_086D8594 }, /* 121 */
    { gBiosLz77Stream_086DC908, gBiosLz77Stream_086DCC44, gBiosLz77Stream_086DD178 }, /* 122 */
    { gBiosLz77Stream_086DF220, gBiosLz77Stream_086DF32C, gBiosLz77Stream_086DF54C }, /* 123 */
    { gBiosLz77Stream_08625A74, gBiosLz77Stream_08625B94, gBiosLz77Stream_08625DDC }, /* 124 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 125 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 126 */
    { gBiosLz77Stream_086138F8, gBiosLz77Stream_08613A54, gBiosLz77Stream_08613CE4 }, /* 127 */
    { gBiosLz77Stream_086E3068, gBiosLz77Stream_086E35F8, gBiosLz77Stream_086E40C4 }, /* 128 */
    { gBiosLz77Stream_086E5314, gBiosLz77Stream_086E5418, gBiosLz77Stream_086E55B4 }, /* 129 */
    { gBiosLz77Stream_086E6470, gBiosLz77Stream_086E6568, gBiosLz77Stream_086E670C }, /* 130 */
    { gBiosLz77Stream_086E7D24, gBiosLz77Stream_086E7E40, gBiosLz77Stream_086E7FB8 }, /* 131 */
    { gBiosLz77Stream_086E7D24, gBiosLz77Stream_086E7E40, gBiosLz77Stream_086E7FB8 }, /* 132 */
    { gBiosLz77Stream_086E7D24, gBiosLz77Stream_086E7E40, gBiosLz77Stream_086E7FB8 }, /* 133 */
    { gBiosLz77Stream_086E7D24, gBiosLz77Stream_086E7E40, gBiosLz77Stream_086E7FB8 }, /* 134 */
    { gBiosLz77Stream_086EB0BC, gBiosLz77Stream_086EB374, gBiosLz77Stream_086EB758 }, /* 135 */
    { gBiosLz77Stream_086EE414, gBiosLz77Stream_086EE614, gBiosLz77Stream_086EE928 }, /* 136 */
    { gBiosLz77Stream_086F2AAC, gBiosLz77Stream_086F2D8C, gBiosLz77Stream_086F327C }, /* 137 */
    { gBiosLz77Stream_08669270, gBiosLz77Stream_086694B4, gBiosLz77Stream_086698CC }, /* 138 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 139 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 140 */
    { gBiosLz77Stream_086A6AB4, gBiosLz77Stream_086A6BDC, gBiosLz77Stream_086A6DA0 }, /* 141 */
    { gBiosLz77Stream_086F6F70, gBiosLz77Stream_086F7220, gBiosLz77Stream_086F7650 }, /* 142 */
    { gBiosLz77Stream_086FA320, gBiosLz77Stream_086FA4E4, gBiosLz77Stream_086FA7B0 }, /* 143 */
    { gBiosLz77Stream_086FC7B8, gBiosLz77Stream_086FC940, gBiosLz77Stream_086FCBC4 }, /* 144 */
    { gBiosLz77Stream_086FDE38, gBiosLz77Stream_086FDF2C, gBiosLz77Stream_086FE078 }, /* 145 */
    { gBiosLz77Stream_0870134C, gBiosLz77Stream_08701504, gBiosLz77Stream_0870184C }, /* 146 */
    { gBiosLz77Stream_0870587C, gBiosLz77Stream_08705B08, gBiosLz77Stream_087061D4 }, /* 147 */
    { gBiosLz77Stream_08707CA4, gBiosLz77Stream_08707DD0, gBiosLz77Stream_08707FC4 }, /* 148 */
    { gBiosLz77Stream_0870B754, gBiosLz77Stream_0870BB14, gBiosLz77Stream_0870C3BC }, /* 149 */
    { gBiosLz77Stream_0870F444, gBiosLz77Stream_0870F570, gBiosLz77Stream_0870F868 }, /* 150 */
    { gBiosLz77Stream_08713024, gBiosLz77Stream_0871330C, gBiosLz77Stream_08713B5C }, /* 151 */
    { gBiosLz77Stream_08717224, gBiosLz77Stream_087173F8, gBiosLz77Stream_087177B8 }, /* 152 */
    { gBiosLz77Stream_0871AE0C, gBiosLz77Stream_0871AFE8, gBiosLz77Stream_0871B4D8 }, /* 153 */
    { gBiosLz77Stream_0871E188, gBiosLz77Stream_0871E344, gBiosLz77Stream_0871E69C }, /* 154 */
    { gBiosLz77Stream_087205BC, gBiosLz77Stream_0872070C, gBiosLz77Stream_0872098C }, /* 155 */
    { gBiosLz77Stream_08722468, gBiosLz77Stream_08722574, gBiosLz77Stream_08722788 }, /* 156 */
    { gBiosLz77Stream_087241A8, gBiosLz77Stream_08724310, gBiosLz77Stream_0872454C }, /* 157 */
    { gBiosLz77Stream_08725FB0, gBiosLz77Stream_087260F0, gBiosLz77Stream_087262EC }, /* 158 */
    { gBiosLz77Stream_08725FB0, gBiosLz77Stream_087260F0, gBiosLz77Stream_087262EC }, /* 159 */
    { gBiosLz77Stream_08725FB0, gBiosLz77Stream_087260F0, gBiosLz77Stream_087262EC }, /* 160 */
    { gBiosLz77Stream_087290E4, gBiosLz77Stream_087292E8, gBiosLz77Stream_08729744 }, /* 161 */
    { gBiosLz77Stream_0872C9F4, gBiosLz77Stream_0872CE18, gBiosLz77Stream_0872D448 }, /* 162 */
    { gBiosLz77Stream_0872F298, gBiosLz77Stream_0872F420, gBiosLz77Stream_0872F59C }, /* 163 */
    { gBiosLz77Stream_08731378, gBiosLz77Stream_0873151C, gBiosLz77Stream_08731650 }, /* 164 */
    { gBiosLz77Stream_087341A8, gBiosLz77Stream_087344A8, gBiosLz77Stream_08734B88 }, /* 165 */
    { gBiosLz77Stream_08736550, gBiosLz77Stream_087367A4, gBiosLz77Stream_08736A40 }, /* 166 */
    { gBiosLz77Stream_087389EC, gBiosLz77Stream_08738B74, gBiosLz77Stream_08738D48 }, /* 167 */
    { gBiosLz77Stream_0873AB8C, gBiosLz77Stream_0873AD44, gBiosLz77Stream_0873AFE0 }, /* 168 */
    { gBiosLz77Stream_0873D21C, gBiosLz77Stream_0873D4A4, gBiosLz77Stream_0873D980 }, /* 169 */
    { gBiosLz77Stream_0873FEF4, gBiosLz77Stream_087400D0, gBiosLz77Stream_087403A4 }, /* 170 */
    { gBiosLz77Stream_08742ADC, gBiosLz77Stream_08742C5C, gBiosLz77Stream_08743078 }, /* 171 */
    { gBiosLz77Stream_08744ADC, gBiosLz77Stream_08744C3C, gBiosLz77Stream_08744E5C }, /* 172 */
    { gBiosLz77Stream_087484B0, gBiosLz77Stream_08748BA0, gBiosLz77Stream_08749310 }, /* 173 */
    { gBiosLz77Stream_0874AC14, gBiosLz77Stream_0874AD8C, gBiosLz77Stream_0874AFAC }, /* 174 */
    { gBiosLz77Stream_0874C6AC, gBiosLz77Stream_0874C848, gBiosLz77Stream_0874CAF8 }, /* 175 */
    { gBiosLz77Stream_0874E3C4, gBiosLz77Stream_0874E510, gBiosLz77Stream_0874E754 }, /* 176 */
    { gBiosLz77Stream_0874FD94, gBiosLz77Stream_0874FED4, gBiosLz77Stream_08750064 }, /* 177 */
    { gBiosLz77Stream_086356FC, gBiosLz77Stream_0863581C, gBiosLz77Stream_08635A54 }, /* 178 */
    { gBiosLz77Stream_086356FC, gBiosLz77Stream_0863581C, gBiosLz77Stream_08635A54 }, /* 179 */
    { gBiosLz77Stream_086356FC, gBiosLz77Stream_0863581C, gBiosLz77Stream_08635A54 }, /* 180 */
    { gBiosLz77Stream_08750C30, gBiosLz77Stream_08750D38, gBiosLz77Stream_08750E48 }, /* 181 */
    { gBiosLz77Stream_0875203C, gBiosLz77Stream_08752160, gBiosLz77Stream_087522FC }, /* 182 */
    { gBiosLz77Stream_08753814, gBiosLz77Stream_0875395C, gBiosLz77Stream_08753B48 }, /* 183 */
    { gBiosLz77Stream_08754D3C, gBiosLz77Stream_08754EC0, gBiosLz77Stream_087550B8 }, /* 184 */
    { gBiosLz77Stream_08756428, gBiosLz77Stream_087565B0, gBiosLz77Stream_087567C4 }, /* 185 */
    { gBiosLz77Stream_08758038, gBiosLz77Stream_0875825C, gBiosLz77Stream_08758490 }, /* 186 */
    { gBiosLz77Stream_0875B20C, gBiosLz77Stream_0875B688, gBiosLz77Stream_0875BA3C }, /* 187 */
    { gBiosLz77Stream_0875EDEC, gBiosLz77Stream_0875F044, gBiosLz77Stream_0875F334 }, /* 188 */
    { gBiosLz77Stream_08761E34, gBiosLz77Stream_08762100, gBiosLz77Stream_08762378 }, /* 189 */
    { gBiosLz77Stream_0867D0B0, gBiosLz77Stream_0867D1F4, gBiosLz77Stream_0867D410 }, /* 190 */
    { gBiosLz77Stream_0867D0B0, gBiosLz77Stream_0867D1F4, gBiosLz77Stream_0867D410 }, /* 191 */
};
