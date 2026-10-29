#include "sound_samples.h"

/* Sample frames are signed decimal PCM values, without alignment padding. */

typedef char SoundPcmSize_080B18E4[(sizeof(struct SoundPcm_080B18E4) == 24) ? 1 : -1];
const struct SoundPcm_080B18E4 gSoundPcm_080B18E4 __attribute__((aligned(1))) = {
    {8, 44100, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080B18E4.inc"
    }
};

typedef char SoundPcmSize_080C5040[(sizeof(struct SoundPcm_080C5040) == 2856) ? 1 : -1];
const struct SoundPcm_080C5040 gSoundPcm_080C5040 __attribute__((aligned(1))) = {
    {2840, 24000, 0, 35, 0x0, 0},
    {
#include "data/audio/pcm_080C5040.inc"
    }
};

typedef char SoundPcmSize_080C5B70[(sizeof(struct SoundPcm_080C5B70) == 3344) ? 1 : -1];
const struct SoundPcm_080C5B70 gSoundPcm_080C5B70 __attribute__((aligned(1))) = {
    {3328, 22050, 0, 36, 0x0, 0},
    {
#include "data/audio/pcm_080C5B70.inc"
    }
};

typedef char SoundPcmSize_080C6880[(sizeof(struct SoundPcm_080C6880) == 2216) ? 1 : -1];
const struct SoundPcm_080C6880 gSoundPcm_080C6880 __attribute__((aligned(1))) = {
    {2200, 22000, 0, 42, 0x0, 0},
    {
#include "data/audio/pcm_080C6880.inc"
    }
};

typedef char SoundPcmSize_080C7130[(sizeof(struct SoundPcm_080C7130) == 2216) ? 1 : -1];
const struct SoundPcm_080C7130 gSoundPcm_080C7130 __attribute__((aligned(1))) = {
    {2200, 22000, 0, 44, 0x0, 0},
    {
#include "data/audio/pcm_080C7130.inc"
    }
};

typedef char SoundPcmSize_080C79E0[(sizeof(struct SoundPcm_080C79E0) == 10516) ? 1 : -1];
const struct SoundPcm_080C79E0 gSoundPcm_080C79E0 __attribute__((aligned(1))) = {
    {10500, 16000, 0, 46, 0x0, 0},
    {
#include "data/audio/pcm_080C79E0.inc"
    }
};

typedef char SoundPcmSize_080CA300[(sizeof(struct SoundPcm_080CA300) == 6716) ? 1 : -1];
const struct SoundPcm_080CA300 gSoundPcm_080CA300 __attribute__((aligned(1))) = {
    {6700, 18000, 0, 38, 0x0, 0},
    {
#include "data/audio/pcm_080CA300.inc"
    }
};

typedef char SoundPcmSize_080CBD40[(sizeof(struct SoundPcm_080CBD40) == 7216) ? 1 : -1];
const struct SoundPcm_080CBD40 gSoundPcm_080CBD40 __attribute__((aligned(1))) = {
    {7200, 18000, 0, 40, 0x0, 0},
    {
#include "data/audio/pcm_080CBD40.inc"
    }
};

typedef char SoundPcmSize_080CD970[(sizeof(struct SoundPcm_080CD970) == 8804) ? 1 : -1];
const struct SoundPcm_080CD970 gSoundPcm_080CD970 __attribute__((aligned(1))) = {
    {8788, 20000, 0, 50, 0x0, 0},
    {
#include "data/audio/pcm_080CD970.inc"
    }
};

typedef char SoundPcmSize_080CFBE0[(sizeof(struct SoundPcm_080CFBE0) == 80) ? 1 : -1];
const struct SoundPcm_080CFBE0 gSoundPcm_080CFBE0 __attribute__((aligned(1))) = {
    {64, 10000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080CFBE0.inc"
    }
};

typedef char SoundPcmSize_080CFC30[(sizeof(struct SoundPcm_080CFC30) == 16736) ? 1 : -1];
const struct SoundPcm_080CFC30 gSoundPcm_080CFC30 __attribute__((aligned(1))) = {
    {16720, 17000, 0, 69, 0x0, 0},
    {
#include "data/audio/pcm_080CFC30.inc"
    }
};

typedef char SoundPcmSize_080D3D90[(sizeof(struct SoundPcm_080D3D90) == 13296) ? 1 : -1];
const struct SoundPcm_080D3D90 gSoundPcm_080D3D90 __attribute__((aligned(1))) = {
    {13280, 20000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080D3D90.inc"
    }
};

typedef char SoundPcmSize_080D7180[(sizeof(struct SoundPcm_080D7180) == 7324) ? 1 : -1];
const struct SoundPcm_080D7180 gSoundPcm_080D7180 __attribute__((aligned(1))) = {
    {7308, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080D7180.inc"
    }
};

typedef char SoundPcmSize_080D8E20[(sizeof(struct SoundPcm_080D8E20) == 2616) ? 1 : -1];
const struct SoundPcm_080D8E20 gSoundPcm_080D8E20 __attribute__((aligned(1))) = {
    {2600, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080D8E20.inc"
    }
};

typedef char SoundPcmSize_080D9860[(sizeof(struct SoundPcm_080D9860) == 6908) ? 1 : -1];
const struct SoundPcm_080D9860 gSoundPcm_080D9860 __attribute__((aligned(1))) = {
    {6892, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080D9860.inc"
    }
};

typedef char SoundPcmSize_080DB360[(sizeof(struct SoundPcm_080DB360) == 20012) ? 1 : -1];
const struct SoundPcm_080DB360 gSoundPcm_080DB360 __attribute__((aligned(1))) = {
    {19996, 20000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080DB360.inc"
    }
};

typedef char SoundPcmSize_080E0190[(sizeof(struct SoundPcm_080E0190) == 7524) ? 1 : -1];
const struct SoundPcm_080E0190 gSoundPcm_080E0190 __attribute__((aligned(1))) = {
    {7508, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080E0190.inc"
    }
};

typedef char SoundPcmSize_080E1F00[(sizeof(struct SoundPcm_080E1F00) == 1916) ? 1 : -1];
const struct SoundPcm_080E1F00 gSoundPcm_080E1F00 __attribute__((aligned(1))) = {
    {1900, 14000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080E1F00.inc"
    }
};

typedef char SoundPcmSize_080E2680[(sizeof(struct SoundPcm_080E2680) == 11836) ? 1 : -1];
const struct SoundPcm_080E2680 gSoundPcm_080E2680 __attribute__((aligned(1))) = {
    {11820, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080E2680.inc"
    }
};

typedef char SoundPcmSize_080E54C0[(sizeof(struct SoundPcm_080E54C0) == 4444) ? 1 : -1];
const struct SoundPcm_080E54C0 gSoundPcm_080E54C0 __attribute__((aligned(1))) = {
    {4428, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080E54C0.inc"
    }
};

typedef char SoundPcmSize_080E6620[(sizeof(struct SoundPcm_080E6620) == 14080) ? 1 : -1];
const struct SoundPcm_080E6620 gSoundPcm_080E6620 __attribute__((aligned(1))) = {
    {14064, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080E6620.inc"
    }
};

typedef char SoundPcmSize_080E9D20[(sizeof(struct SoundPcm_080E9D20) == 12384) ? 1 : -1];
const struct SoundPcm_080E9D20 gSoundPcm_080E9D20 __attribute__((aligned(1))) = {
    {12368, 20000, 0, 60, 0x1, 0},
    {
#include "data/audio/pcm_080E9D20.inc"
    }
};

typedef char SoundPcmSize_080ECD80[(sizeof(struct SoundPcm_080ECD80) == 3524) ? 1 : -1];
const struct SoundPcm_080ECD80 gSoundPcm_080ECD80 __attribute__((aligned(1))) = {
    {3508, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080ECD80.inc"
    }
};

typedef char SoundPcmSize_080EDB50[(sizeof(struct SoundPcm_080EDB50) == 8020) ? 1 : -1];
const struct SoundPcm_080EDB50 gSoundPcm_080EDB50 __attribute__((aligned(1))) = {
    {8004, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_080EDB50.inc"
    }
};

typedef char SoundPcmSize_080EFAB0[(sizeof(struct SoundPcm_080EFAB0) == 13164) ? 1 : -1];
const struct SoundPcm_080EFAB0 gSoundPcm_080EFAB0 __attribute__((aligned(1))) = {
    {13148, 20000, 0, 49, 0x0, 0},
    {
#include "data/audio/pcm_080EFAB0.inc"
    }
};

typedef char SoundPcmSize_080F2E20[(sizeof(struct SoundPcm_080F2E20) == 21392) ? 1 : -1];
const struct SoundPcm_080F2E20 gSoundPcm_080F2E20 __attribute__((aligned(1))) = {
    {21376, 17000, 0, 69, 0x1, 9204},
    {
#include "data/audio/pcm_080F2E20.inc"
    }
};

typedef char SoundPcmSize_080F81B0[(sizeof(struct SoundPcm_080F81B0) == 40780) ? 1 : -1];
const struct SoundPcm_080F81B0 gSoundPcm_080F81B0 __attribute__((aligned(1))) = {
    {40764, 22050, 0, 69, 0x1, 22756},
    {
#include "data/audio/pcm_080F81B0.inc"
    }
};

typedef char SoundPcmSize_08102110[(sizeof(struct SoundPcm_08102110) == 6680) ? 1 : -1];
const struct SoundPcm_08102110 gSoundPcm_08102110 __attribute__((aligned(1))) = {
    {6664, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08102110.inc"
    }
};

typedef char SoundPcmSize_08103B30[(sizeof(struct SoundPcm_08103B30) == 11388) ? 1 : -1];
const struct SoundPcm_08103B30 gSoundPcm_08103B30 __attribute__((aligned(1))) = {
    {11372, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08103B30.inc"
    }
};

typedef char SoundPcmSize_081067B0[(sizeof(struct SoundPcm_081067B0) == 17720) ? 1 : -1];
const struct SoundPcm_081067B0 gSoundPcm_081067B0 __attribute__((aligned(1))) = {
    {17704, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081067B0.inc"
    }
};

typedef char SoundPcmSize_0810ACF0[(sizeof(struct SoundPcm_0810ACF0) == 12000) ? 1 : -1];
const struct SoundPcm_0810ACF0 gSoundPcm_0810ACF0 __attribute__((aligned(1))) = {
    {11984, 8000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0810ACF0.inc"
    }
};

typedef char SoundPcmSize_0810DBD0[(sizeof(struct SoundPcm_0810DBD0) == 16904) ? 1 : -1];
const struct SoundPcm_0810DBD0 gSoundPcm_0810DBD0 __attribute__((aligned(1))) = {
    {16888, 8000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0810DBD0.inc"
    }
};

typedef char SoundPcmSize_08111DE0[(sizeof(struct SoundPcm_08111DE0) == 16588) ? 1 : -1];
const struct SoundPcm_08111DE0 gSoundPcm_08111DE0 __attribute__((aligned(1))) = {
    {16572, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08111DE0.inc"
    }
};

typedef char SoundPcmSize_08115EB0[(sizeof(struct SoundPcm_08115EB0) == 16468) ? 1 : -1];
const struct SoundPcm_08115EB0 gSoundPcm_08115EB0 __attribute__((aligned(1))) = {
    {16452, 17000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08115EB0.inc"
    }
};

typedef char SoundPcmSize_08119F10[(sizeof(struct SoundPcm_08119F10) == 10992) ? 1 : -1];
const struct SoundPcm_08119F10 gSoundPcm_08119F10 __attribute__((aligned(1))) = {
    {10976, 20000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08119F10.inc"
    }
};

typedef char SoundPcmSize_0811CA00[(sizeof(struct SoundPcm_0811CA00) == 24080) ? 1 : -1];
const struct SoundPcm_0811CA00 gSoundPcm_0811CA00 __attribute__((aligned(1))) = {
    {24064, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0811CA00.inc"
    }
};

typedef char SoundPcmSize_08122810[(sizeof(struct SoundPcm_08122810) == 22196) ? 1 : -1];
const struct SoundPcm_08122810 gSoundPcm_08122810 __attribute__((aligned(1))) = {
    {22180, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08122810.inc"
    }
};

typedef char SoundPcmSize_08127ED0[(sizeof(struct SoundPcm_08127ED0) == 19768) ? 1 : -1];
const struct SoundPcm_08127ED0 gSoundPcm_08127ED0 __attribute__((aligned(1))) = {
    {19752, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08127ED0.inc"
    }
};

typedef char SoundPcmSize_0812CC10[(sizeof(struct SoundPcm_0812CC10) == 18164) ? 1 : -1];
const struct SoundPcm_0812CC10 gSoundPcm_0812CC10 __attribute__((aligned(1))) = {
    {18148, 16000, 0, 69, 0x1, 9297},
    {
#include "data/audio/pcm_0812CC10.inc"
    }
};

typedef char SoundPcmSize_08131310[(sizeof(struct SoundPcm_08131310) == 10516) ? 1 : -1];
const struct SoundPcm_08131310 gSoundPcm_08131310 __attribute__((aligned(1))) = {
    {10500, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08131310.inc"
    }
};

typedef char SoundPcmSize_08133C30[(sizeof(struct SoundPcm_08133C30) == 27136) ? 1 : -1];
const struct SoundPcm_08133C30 gSoundPcm_08133C30 __attribute__((aligned(1))) = {
    {27120, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08133C30.inc"
    }
};

typedef char SoundPcmSize_0813A630[(sizeof(struct SoundPcm_0813A630) == 12196) ? 1 : -1];
const struct SoundPcm_0813A630 gSoundPcm_0813A630 __attribute__((aligned(1))) = {
    {12180, 12000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0813A630.inc"
    }
};

typedef char SoundPcmSize_0813D5E0[(sizeof(struct SoundPcm_0813D5E0) == 11568) ? 1 : -1];
const struct SoundPcm_0813D5E0 gSoundPcm_0813D5E0 __attribute__((aligned(1))) = {
    {11552, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0813D5E0.inc"
    }
};

typedef char SoundPcmSize_08140310[(sizeof(struct SoundPcm_08140310) == 18576) ? 1 : -1];
const struct SoundPcm_08140310 gSoundPcm_08140310 __attribute__((aligned(1))) = {
    {18560, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08140310.inc"
    }
};

typedef char SoundPcmSize_08144BA0[(sizeof(struct SoundPcm_08144BA0) == 11988) ? 1 : -1];
const struct SoundPcm_08144BA0 gSoundPcm_08144BA0 __attribute__((aligned(1))) = {
    {11972, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08144BA0.inc"
    }
};

typedef char SoundPcmSize_08147A80[(sizeof(struct SoundPcm_08147A80) == 14088) ? 1 : -1];
const struct SoundPcm_08147A80 gSoundPcm_08147A80 __attribute__((aligned(1))) = {
    {14072, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08147A80.inc"
    }
};

typedef char SoundPcmSize_0814B190[(sizeof(struct SoundPcm_0814B190) == 18756) ? 1 : -1];
const struct SoundPcm_0814B190 gSoundPcm_0814B190 __attribute__((aligned(1))) = {
    {18740, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0814B190.inc"
    }
};

typedef char SoundPcmSize_0814FAE0[(sizeof(struct SoundPcm_0814FAE0) == 15568) ? 1 : -1];
const struct SoundPcm_0814FAE0 gSoundPcm_0814FAE0 __attribute__((aligned(1))) = {
    {15552, 10000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0814FAE0.inc"
    }
};

typedef char SoundPcmSize_081537B0[(sizeof(struct SoundPcm_081537B0) == 14168) ? 1 : -1];
const struct SoundPcm_081537B0 gSoundPcm_081537B0 __attribute__((aligned(1))) = {
    {14152, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081537B0.inc"
    }
};

typedef char SoundPcmSize_08156F10[(sizeof(struct SoundPcm_08156F10) == 14176) ? 1 : -1];
const struct SoundPcm_08156F10 gSoundPcm_08156F10 __attribute__((aligned(1))) = {
    {14160, 12000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08156F10.inc"
    }
};

typedef char SoundPcmSize_0815A670[(sizeof(struct SoundPcm_0815A670) == 16336) ? 1 : -1];
const struct SoundPcm_0815A670 gSoundPcm_0815A670 __attribute__((aligned(1))) = {
    {16320, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0815A670.inc"
    }
};

typedef char SoundPcmSize_0815E640[(sizeof(struct SoundPcm_0815E640) == 13944) ? 1 : -1];
const struct SoundPcm_0815E640 gSoundPcm_0815E640 __attribute__((aligned(1))) = {
    {13928, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0815E640.inc"
    }
};

typedef char SoundPcmSize_08161CC0[(sizeof(struct SoundPcm_08161CC0) == 7540) ? 1 : -1];
const struct SoundPcm_08161CC0 gSoundPcm_08161CC0 __attribute__((aligned(1))) = {
    {7524, 16000, 0, 51, 0x0, 0},
    {
#include "data/audio/pcm_08161CC0.inc"
    }
};

typedef char SoundPcmSize_08163A40[(sizeof(struct SoundPcm_08163A40) == 12064) ? 1 : -1];
const struct SoundPcm_08163A40 gSoundPcm_08163A40 __attribute__((aligned(1))) = {
    {12048, 14000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08163A40.inc"
    }
};

typedef char SoundPcmSize_08166960[(sizeof(struct SoundPcm_08166960) == 22952) ? 1 : -1];
const struct SoundPcm_08166960 gSoundPcm_08166960 __attribute__((aligned(1))) = {
    {22936, 16000, 0, 59, 0x0, 0},
    {
#include "data/audio/pcm_08166960.inc"
    }
};

typedef char SoundPcmSize_0816C310[(sizeof(struct SoundPcm_0816C310) == 22300) ? 1 : -1];
const struct SoundPcm_0816C310 gSoundPcm_0816C310 __attribute__((aligned(1))) = {
    {22284, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0816C310.inc"
    }
};

typedef char SoundPcmSize_08171A30[(sizeof(struct SoundPcm_08171A30) == 4864) ? 1 : -1];
const struct SoundPcm_08171A30 gSoundPcm_08171A30 __attribute__((aligned(1))) = {
    {4848, 7000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08171A30.inc"
    }
};

typedef char SoundPcmSize_08172D30[(sizeof(struct SoundPcm_08172D30) == 15316) ? 1 : -1];
const struct SoundPcm_08172D30 gSoundPcm_08172D30 __attribute__((aligned(1))) = {
    {15300, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08172D30.inc"
    }
};

typedef char SoundPcmSize_08176910[(sizeof(struct SoundPcm_08176910) == 9920) ? 1 : -1];
const struct SoundPcm_08176910 gSoundPcm_08176910 __attribute__((aligned(1))) = {
    {9904, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08176910.inc"
    }
};

typedef char SoundPcmSize_08178FD0[(sizeof(struct SoundPcm_08178FD0) == 11856) ? 1 : -1];
const struct SoundPcm_08178FD0 gSoundPcm_08178FD0 __attribute__((aligned(1))) = {
    {11840, 8000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08178FD0.inc"
    }
};

typedef char SoundPcmSize_0817BE20[(sizeof(struct SoundPcm_0817BE20) == 4880) ? 1 : -1];
const struct SoundPcm_0817BE20 gSoundPcm_0817BE20 __attribute__((aligned(1))) = {
    {4864, 12000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0817BE20.inc"
    }
};

typedef char SoundPcmSize_0817D130[(sizeof(struct SoundPcm_0817D130) == 7216) ? 1 : -1];
const struct SoundPcm_0817D130 gSoundPcm_0817D130 __attribute__((aligned(1))) = {
    {7200, 10000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0817D130.inc"
    }
};

typedef char SoundPcmSize_0817ED60[(sizeof(struct SoundPcm_0817ED60) == 7528) ? 1 : -1];
const struct SoundPcm_0817ED60 gSoundPcm_0817ED60 __attribute__((aligned(1))) = {
    {7512, 17000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0817ED60.inc"
    }
};

typedef char SoundPcmSize_08180AD0[(sizeof(struct SoundPcm_08180AD0) == 28268) ? 1 : -1];
const struct SoundPcm_08180AD0 gSoundPcm_08180AD0 __attribute__((aligned(1))) = {
    {28252, 17000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08180AD0.inc"
    }
};

typedef char SoundPcmSize_08187940[(sizeof(struct SoundPcm_08187940) == 36016) ? 1 : -1];
const struct SoundPcm_08187940 gSoundPcm_08187940 __attribute__((aligned(1))) = {
    {36000, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08187940.inc"
    }
};

typedef char SoundPcmSize_081905F0[(sizeof(struct SoundPcm_081905F0) == 13024) ? 1 : -1];
const struct SoundPcm_081905F0 gSoundPcm_081905F0 __attribute__((aligned(1))) = {
    {13008, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081905F0.inc"
    }
};

typedef char SoundPcmSize_081938D0[(sizeof(struct SoundPcm_081938D0) == 13016) ? 1 : -1];
const struct SoundPcm_081938D0 gSoundPcm_081938D0 __attribute__((aligned(1))) = {
    {13000, 12000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081938D0.inc"
    }
};

typedef char SoundPcmSize_08196BB0[(sizeof(struct SoundPcm_08196BB0) == 13376) ? 1 : -1];
const struct SoundPcm_08196BB0 gSoundPcm_08196BB0 __attribute__((aligned(1))) = {
    {13360, 17000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08196BB0.inc"
    }
};

typedef char SoundPcmSize_08199FF0[(sizeof(struct SoundPcm_08199FF0) == 19180) ? 1 : -1];
const struct SoundPcm_08199FF0 gSoundPcm_08199FF0 __attribute__((aligned(1))) = {
    {19164, 16000, 0, 72, 0x1, 10880},
    {
#include "data/audio/pcm_08199FF0.inc"
    }
};

typedef char SoundPcmSize_0819EAE0[(sizeof(struct SoundPcm_0819EAE0) == 20272) ? 1 : -1];
const struct SoundPcm_0819EAE0 gSoundPcm_0819EAE0 __attribute__((aligned(1))) = {
    {20256, 16000, 0, 69, 0x1, 14436},
    {
#include "data/audio/pcm_0819EAE0.inc"
    }
};

typedef char SoundPcmSize_081A3A20[(sizeof(struct SoundPcm_081A3A20) == 11492) ? 1 : -1];
const struct SoundPcm_081A3A20 gSoundPcm_081A3A20 __attribute__((aligned(1))) = {
    {11476, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081A3A20.inc"
    }
};

typedef char SoundPcmSize_081A6710[(sizeof(struct SoundPcm_081A6710) == 16663) ? 1 : -1];
const struct SoundPcm_081A6710 gSoundPcm_081A6710 __attribute__((aligned(1))) = {
    {16647, 17000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081A6710.inc"
    }
};

typedef char SoundPcmSize_081AA830[(sizeof(struct SoundPcm_081AA830) == 15428) ? 1 : -1];
const struct SoundPcm_081AA830 gSoundPcm_081AA830 __attribute__((aligned(1))) = {
    {15412, 16000, 0, 69, 0x0, 0},
    {
#include "data/audio/pcm_081AA830.inc"
    }
};

typedef char SoundPcmSize_081AE480[(sizeof(struct SoundPcm_081AE480) == 17660) ? 1 : -1];
const struct SoundPcm_081AE480 gSoundPcm_081AE480 __attribute__((aligned(1))) = {
    {17644, 17000, 0, 76, 0x0, 0},
    {
#include "data/audio/pcm_081AE480.inc"
    }
};

typedef char SoundPcmSize_081B2980[(sizeof(struct SoundPcm_081B2980) == 15250) ? 1 : -1];
const struct SoundPcm_081B2980 gSoundPcm_081B2980 __attribute__((aligned(1))) = {
    {15234, 16000, 0, 72, 0x0, 0},
    {
#include "data/audio/pcm_081B2980.inc"
    }
};

typedef char SoundPcmSize_081B6520[(sizeof(struct SoundPcm_081B6520) == 17872) ? 1 : -1];
const struct SoundPcm_081B6520 gSoundPcm_081B6520 __attribute__((aligned(1))) = {
    {17856, 16000, 0, 70, 0x1, 8080},
    {
#include "data/audio/pcm_081B6520.inc"
    }
};

typedef char SoundPcmSize_081BAB00[(sizeof(struct SoundPcm_081BAB00) == 21644) ? 1 : -1];
const struct SoundPcm_081BAB00 gSoundPcm_081BAB00 __attribute__((aligned(1))) = {
    {21628, 18000, 0, 72, 0x1, 8684},
    {
#include "data/audio/pcm_081BAB00.inc"
    }
};

typedef char SoundPcmSize_081BFFA0[(sizeof(struct SoundPcm_081BFFA0) == 18452) ? 1 : -1];
const struct SoundPcm_081BFFA0 gSoundPcm_081BFFA0 __attribute__((aligned(1))) = {
    {18436, 16000, 0, 69, 0x1, 5736},
    {
#include "data/audio/pcm_081BFFA0.inc"
    }
};

typedef char SoundPcmSize_081C47D0[(sizeof(struct SoundPcm_081C47D0) == 17660) ? 1 : -1];
const struct SoundPcm_081C47D0 gSoundPcm_081C47D0 __attribute__((aligned(1))) = {
    {17644, 17000, 0, 76, 0x0, 0},
    {
#include "data/audio/pcm_081C47D0.inc"
    }
};

typedef char SoundPcmSize_081C8CD0[(sizeof(struct SoundPcm_081C8CD0) == 14932) ? 1 : -1];
const struct SoundPcm_081C8CD0 gSoundPcm_081C8CD0 __attribute__((aligned(1))) = {
    {14916, 15000, 0, 75, 0x0, 0},
    {
#include "data/audio/pcm_081C8CD0.inc"
    }
};

typedef char SoundPcmSize_081CC730[(sizeof(struct SoundPcm_081CC730) == 17044) ? 1 : -1];
const struct SoundPcm_081CC730 gSoundPcm_081CC730 __attribute__((aligned(1))) = {
    {17028, 16000, 0, 52, 0x0, 0},
    {
#include "data/audio/pcm_081CC730.inc"
    }
};

typedef char SoundPcmSize_081D09D0[(sizeof(struct SoundPcm_081D09D0) == 19180) ? 1 : -1];
const struct SoundPcm_081D09D0 gSoundPcm_081D09D0 __attribute__((aligned(1))) = {
    {19164, 16000, 0, 72, 0x1, 10880},
    {
#include "data/audio/pcm_081D09D0.inc"
    }
};

typedef char SoundPcmSize_081D54D0[(sizeof(struct SoundPcm_081D54D0) == 27716) ? 1 : -1];
const struct SoundPcm_081D54D0 gSoundPcm_081D54D0 __attribute__((aligned(1))) = {
    {27700, 17000, 0, 72, 0x0, 0},
    {
#include "data/audio/pcm_081D54D0.inc"
    }
};

typedef char SoundPcmSize_081DC120[(sizeof(struct SoundPcm_081DC120) == 15032) ? 1 : -1];
const struct SoundPcm_081DC120 gSoundPcm_081DC120 __attribute__((aligned(1))) = {
    {15016, 15000, 0, 53, 0x1, 8824},
    {
#include "data/audio/pcm_081DC120.inc"
    }
};

typedef char SoundPcmSize_081DFBF0[(sizeof(struct SoundPcm_081DFBF0) == 16056) ? 1 : -1];
const struct SoundPcm_081DFBF0 gSoundPcm_081DFBF0 __attribute__((aligned(1))) = {
    {16040, 16000, 0, 71, 0x1, 1848},
    {
#include "data/audio/pcm_081DFBF0.inc"
    }
};

typedef char SoundPcmSize_081E3AC0[(sizeof(struct SoundPcm_081E3AC0) == 11768) ? 1 : -1];
const struct SoundPcm_081E3AC0 gSoundPcm_081E3AC0 __attribute__((aligned(1))) = {
    {11752, 17000, 0, 39, 0x0, 0},
    {
#include "data/audio/pcm_081E3AC0.inc"
    }
};

typedef char SoundPcmSize_081E68C0[(sizeof(struct SoundPcm_081E68C0) == 18164) ? 1 : -1];
const struct SoundPcm_081E68C0 gSoundPcm_081E68C0 __attribute__((aligned(1))) = {
    {18148, 16000, 0, 69, 0x1, 9297},
    {
#include "data/audio/pcm_081E68C0.inc"
    }
};

typedef char SoundPcmSize_081EAFD0[(sizeof(struct SoundPcm_081EAFD0) == 8708) ? 1 : -1];
const struct SoundPcm_081EAFD0 gSoundPcm_081EAFD0 __attribute__((aligned(1))) = {
    {8692, 16000, 0, 53, 0x0, 0},
    {
#include "data/audio/pcm_081EAFD0.inc"
    }
};

typedef char SoundPcmSize_081ED1E0[(sizeof(struct SoundPcm_081ED1E0) == 964528) ? 1 : -1];
const struct SoundPcm_081ED1E0 gSoundPcm_081ED1E0 __attribute__((aligned(1))) = {
    {964512, 20000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_081ED1E0.inc"
    }
};

typedef char SoundPcmSize_082D8990[(sizeof(struct SoundPcm_082D8990) == 9172) ? 1 : -1];
const struct SoundPcm_082D8990 gSoundPcm_082D8990 __attribute__((aligned(1))) = {
    {9156, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_082D8990.inc"
    }
};

typedef char SoundPcmSize_082DAD70[(sizeof(struct SoundPcm_082DAD70) == 466376) ? 1 : -1];
const struct SoundPcm_082DAD70 gSoundPcm_082DAD70 __attribute__((aligned(1))) = {
    {466360, 20000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_082DAD70.inc"
    }
};

typedef char SoundPcmSize_0834CB40[(sizeof(struct SoundPcm_0834CB40) == 8051) ? 1 : -1];
const struct SoundPcm_0834CB40 gSoundPcm_0834CB40 __attribute__((aligned(1))) = {
    {8035, 17000, 0, 54, 0x0, 0},
    {
#include "data/audio/pcm_0834CB40.inc"
    }
};

typedef char SoundPcmSize_0834EAC0[(sizeof(struct SoundPcm_0834EAC0) == 11792) ? 1 : -1];
const struct SoundPcm_0834EAC0 gSoundPcm_0834EAC0 __attribute__((aligned(1))) = {
    {11776, 16000, 0, 69, 0x0, 0},
    {
#include "data/audio/pcm_0834EAC0.inc"
    }
};

typedef char SoundPcmSize_083518D0[(sizeof(struct SoundPcm_083518D0) == 30560) ? 1 : -1];
const struct SoundPcm_083518D0 gSoundPcm_083518D0 __attribute__((aligned(1))) = {
    {30544, 16000, 0, 76, 0x1, 11316},
    {
#include "data/audio/pcm_083518D0.inc"
    }
};

typedef char SoundPcmSize_08359040[(sizeof(struct SoundPcm_08359040) == 15880) ? 1 : -1];
const struct SoundPcm_08359040 gSoundPcm_08359040 __attribute__((aligned(1))) = {
    {15864, 16000, 0, 70, 0x0, 0},
    {
#include "data/audio/pcm_08359040.inc"
    }
};

typedef char SoundPcmSize_0835CE50[(sizeof(struct SoundPcm_0835CE50) == 14976) ? 1 : -1];
const struct SoundPcm_0835CE50 gSoundPcm_0835CE50 __attribute__((aligned(1))) = {
    {14960, 16000, 0, 62, 0x0, 0},
    {
#include "data/audio/pcm_0835CE50.inc"
    }
};

typedef char SoundPcmSize_083608D0[(sizeof(struct SoundPcm_083608D0) == 8500) ? 1 : -1];
const struct SoundPcm_083608D0 gSoundPcm_083608D0 __attribute__((aligned(1))) = {
    {8484, 15000, 0, 62, 0x0, 0},
    {
#include "data/audio/pcm_083608D0.inc"
    }
};

typedef char SoundPcmSize_08362A10[(sizeof(struct SoundPcm_08362A10) == 20484) ? 1 : -1];
const struct SoundPcm_08362A10 gSoundPcm_08362A10 __attribute__((aligned(1))) = {
    {20468, 17000, 0, 60, 0x1, 7100},
    {
#include "data/audio/pcm_08362A10.inc"
    }
};

typedef char SoundPcmSize_08367A20[(sizeof(struct SoundPcm_08367A20) == 14188) ? 1 : -1];
const struct SoundPcm_08367A20 gSoundPcm_08367A20 __attribute__((aligned(1))) = {
    {14172, 16000, 0, 69, 0x0, 0},
    {
#include "data/audio/pcm_08367A20.inc"
    }
};

typedef char SoundPcmSize_0836B190[(sizeof(struct SoundPcm_0836B190) == 6980) ? 1 : -1];
const struct SoundPcm_0836B190 gSoundPcm_0836B190 __attribute__((aligned(1))) = {
    {6964, 14000, 0, 60, 0x1, 0},
    {
#include "data/audio/pcm_0836B190.inc"
    }
};

typedef char SoundPcmSize_0836CCE0[(sizeof(struct SoundPcm_0836CCE0) == 6404) ? 1 : -1];
const struct SoundPcm_0836CCE0 gSoundPcm_0836CCE0 __attribute__((aligned(1))) = {
    {6388, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0836CCE0.inc"
    }
};

typedef char SoundPcmSize_0836E5F0[(sizeof(struct SoundPcm_0836E5F0) == 4816) ? 1 : -1];
const struct SoundPcm_0836E5F0 gSoundPcm_0836E5F0 __attribute__((aligned(1))) = {
    {4800, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0836E5F0.inc"
    }
};

typedef char SoundPcmSize_0836F8C0[(sizeof(struct SoundPcm_0836F8C0) == 6532) ? 1 : -1];
const struct SoundPcm_0836F8C0 gSoundPcm_0836F8C0 __attribute__((aligned(1))) = {
    {6516, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0836F8C0.inc"
    }
};

typedef char SoundPcmSize_08371250[(sizeof(struct SoundPcm_08371250) == 10176) ? 1 : -1];
const struct SoundPcm_08371250 gSoundPcm_08371250 __attribute__((aligned(1))) = {
    {10160, 14000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08371250.inc"
    }
};

typedef char SoundPcmSize_08373A10[(sizeof(struct SoundPcm_08373A10) == 18148) ? 1 : -1];
const struct SoundPcm_08373A10 gSoundPcm_08373A10 __attribute__((aligned(1))) = {
    {18132, 16000, 0, 69, 0x1, 9281},
    {
#include "data/audio/pcm_08373A10.inc"
    }
};

typedef char SoundPcmSize_08378110[(sizeof(struct SoundPcm_08378110) == 8184) ? 1 : -1];
const struct SoundPcm_08378110 gSoundPcm_08378110 __attribute__((aligned(1))) = {
    {8168, 15000, 0, 55, 0x0, 0},
    {
#include "data/audio/pcm_08378110.inc"
    }
};

typedef char SoundPcmSize_0837A110[(sizeof(struct SoundPcm_0837A110) == 8016) ? 1 : -1];
const struct SoundPcm_0837A110 gSoundPcm_0837A110 __attribute__((aligned(1))) = {
    {8000, 15000, 0, 56, 0x0, 0},
    {
#include "data/audio/pcm_0837A110.inc"
    }
};

typedef char SoundPcmSize_0837C060[(sizeof(struct SoundPcm_0837C060) == 1392) ? 1 : -1];
const struct SoundPcm_0837C060 gSoundPcm_0837C060 __attribute__((aligned(1))) = {
    {1376, 11000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0837C060.inc"
    }
};

typedef char SoundPcmSize_0837C5D0[(sizeof(struct SoundPcm_0837C5D0) == 5440) ? 1 : -1];
const struct SoundPcm_0837C5D0 gSoundPcm_0837C5D0 __attribute__((aligned(1))) = {
    {5424, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0837C5D0.inc"
    }
};

typedef char SoundPcmSize_0837DB10[(sizeof(struct SoundPcm_0837DB10) == 16408) ? 1 : -1];
const struct SoundPcm_0837DB10 gSoundPcm_0837DB10 __attribute__((aligned(1))) = {
    {16392, 17000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0837DB10.inc"
    }
};

typedef char SoundPcmSize_08381B30[(sizeof(struct SoundPcm_08381B30) == 19056) ? 1 : -1];
const struct SoundPcm_08381B30 gSoundPcm_08381B30 __attribute__((aligned(1))) = {
    {19040, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08381B30.inc"
    }
};

typedef char SoundPcmSize_083865A0[(sizeof(struct SoundPcm_083865A0) == 4676) ? 1 : -1];
const struct SoundPcm_083865A0 gSoundPcm_083865A0 __attribute__((aligned(1))) = {
    {4660, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_083865A0.inc"
    }
};

typedef char SoundPcmSize_083877F0[(sizeof(struct SoundPcm_083877F0) == 17024) ? 1 : -1];
const struct SoundPcm_083877F0 gSoundPcm_083877F0 __attribute__((aligned(1))) = {
    {17008, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_083877F0.inc"
    }
};

typedef char SoundPcmSize_0838BA70[(sizeof(struct SoundPcm_0838BA70) == 14428) ? 1 : -1];
const struct SoundPcm_0838BA70 gSoundPcm_0838BA70 __attribute__((aligned(1))) = {
    {14412, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0838BA70.inc"
    }
};

typedef char SoundPcmSize_0838F2D0[(sizeof(struct SoundPcm_0838F2D0) == 26632) ? 1 : -1];
const struct SoundPcm_0838F2D0 gSoundPcm_0838F2D0 __attribute__((aligned(1))) = {
    {26616, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0838F2D0.inc"
    }
};

typedef char SoundPcmSize_08395AE0[(sizeof(struct SoundPcm_08395AE0) == 17968) ? 1 : -1];
const struct SoundPcm_08395AE0 gSoundPcm_08395AE0 __attribute__((aligned(1))) = {
    {17952, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_08395AE0.inc"
    }
};

typedef char SoundPcmSize_0839A110[(sizeof(struct SoundPcm_0839A110) == 23972) ? 1 : -1];
const struct SoundPcm_0839A110 gSoundPcm_0839A110 __attribute__((aligned(1))) = {
    {23956, 16000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0839A110.inc"
    }
};

typedef char SoundPcmSize_0839FEC0[(sizeof(struct SoundPcm_0839FEC0) == 18624) ? 1 : -1];
const struct SoundPcm_0839FEC0 gSoundPcm_0839FEC0 __attribute__((aligned(1))) = {
    {18608, 18000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_0839FEC0.inc"
    }
};

typedef char SoundPcmSize_083A4780[(sizeof(struct SoundPcm_083A4780) == 8960) ? 1 : -1];
const struct SoundPcm_083A4780 gSoundPcm_083A4780 __attribute__((aligned(1))) = {
    {8944, 15000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_083A4780.inc"
    }
};

typedef char SoundPcmSize_083A6A80[(sizeof(struct SoundPcm_083A6A80) == 3016) ? 1 : -1];
const struct SoundPcm_083A6A80 gSoundPcm_083A6A80 __attribute__((aligned(1))) = {
    {3000, 12000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_083A6A80.inc"
    }
};

typedef char SoundPcmSize_083A7650[(sizeof(struct SoundPcm_083A7650) == 9616) ? 1 : -1];
const struct SoundPcm_083A7650 gSoundPcm_083A7650 __attribute__((aligned(1))) = {
    {9600, 13000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_083A7650.inc"
    }
};

typedef char SoundPcmSize_083A9BE0[(sizeof(struct SoundPcm_083A9BE0) == 8048) ? 1 : -1];
const struct SoundPcm_083A9BE0 gSoundPcm_083A9BE0 __attribute__((aligned(1))) = {
    {8032, 14000, 0, 60, 0x0, 0},
    {
#include "data/audio/pcm_083A9BE0.inc"
    }
};
