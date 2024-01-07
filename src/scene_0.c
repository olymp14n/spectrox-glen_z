#include "scene_0.h"
#include <math.h>
#include "config/config.h"
#include "fw/types.h"
#include "fw/render.h"
#include "fw/lut.h"
#include "fw/easing.h"
#include "fw/animation.h"
#include "fw/font.h"
#include "fw/projection.h"
#include "resource.h"
#include "fx/anim_text.h"
#include "fx/glenz.h"

#define KEYFRAME_INDEX_COLOR 0

enum anim_names_enum {
    ANIM_DELAY,
    ANIM_TEXT_LOGO,
    ANIM_TEXT_LOGO_LOOP,
    ANIM_TEXT1,
    ANIM_TEXT2,
    ANIM_TEXT3,
    ANIM_TEXT3B,
    ANIM_TEXT4,
    ANIM_GLENZ0,
    ANIM_GLENZ1,
    ANIM_GLENZ1B,
    ANIM_GLENZ2,
    ANIM_GLENZ3,
    ANIM_GLENZ4,
};

static BOOL _isLogoLoopEnabled = FALSE;
static BOOL _isText1Enabled = FALSE;
static BOOL _isText2Enabled = FALSE;
static BOOL _isText3Enabled = FALSE;
static BOOL _isText3BEnabled = FALSE;
static BOOL _isText4Enabled = FALSE;

static fx_anim_text_meta _metaLogo;
static fx_anim_text_meta _metaLogoLoop;
static fx_anim_text_meta _meta1;
static fx_anim_text_meta _meta2;
static fx_anim_text_meta _meta3;
static fx_anim_text_meta _meta3B;
static fx_anim_text_meta _meta4;

static const fw_vec4f _glenzColors[] = {
    {.85f,0,0,.7f},
    {0,.55f,0,.701f},
    {0.65f,0,0.65f,.702f},
    {0,.65f,.85f,.703f},
};
static const int _numGlenzColors = LEN(_glenzColors);

static const fw_vec4f _clearColor = {60/255.f,62/255.f,87/255.f,1};
static const fw_vec4f _bgTwirlColor = {35/255.f,62/255.f,87/255.f,1};

///////////////////////////////////////////////////////////////////////////////
// STRINGS
///////////////////////////////////////////////////////////////////////////////

static char *_textLogo[] = {
    "      U        U        U         U        U         U         U         U",
    "     F \\____  F \\____  F \\_____  F \\____  F \\_____  F \\____   F \\___    F \\ U__",
    "    /   U___)/       \\/    U___)/       \\(__    U_)/       \\ /      \\  /   Y   \\",
    "  U(___    \\/     B :.\\     U_)/     B___)/      \\/     B U_)     B  \\(_       U)U",
    "UF/   /   :.\\       U__)     :.\\     F :.\\      :.\\        \\        :.\\       :.\\B\\_",
    " (___________)U______)U_________)U________)U_______)UF    :.\\__________)U__E_____)\\",
    "  M M- M--------------------------------------------(________)MoLYXM---------- M- M'",
};
static int _numLinesLogo = LEN(_textLogo);

static char *_text1[] = {
    "       ~S~P~E~C~T~R~O~X~",
    "",
    " iS BACK FOR NO PARTiCULAR REASON",
    "      WiTH A LiTTLE iNTRO",
    "",
    "             CALLED",
    "",
    "      .-------------------.",
    "      |  \" G L E N - Z \"  |",
    "      `-------------------'",
    "",
    "",
    "    CODE, GRAPHiCS AND MUSiC",
    "",
    "               BY",
    "",
    "            OLYMPiAN",
};
static int _numLines1 = LEN(_text1);

static char *_text2[] = {
    "      HERE WE GO AGAiN!",
    "",
    "THE DAYS ARE GETTiNG SHORTER",
    "AND  THE NiGHTS  ARE GETTiNG",
    "COLDER...",
    "",
    "  iT'S  DECEMBER   2023  AND",
    "WE  ARE  BACK WiTH  A  SMALL",
    "ONE-SCREEN iNTRO  / CRACKTRO",
    "JUST  BEFORE  THE NEW  YEAR,",
    "FEATURiNG   SOME  GOOD   OLD",
    "GLENZ VECTOR ACTiON.",
    "",
    "  AS  USUAL  THiS iNTRO  HAS",
    "BEEN iMPLEMENTED  iN HEAViLY",
    "OUTDATED LEGACY OPENGL :)",
};
static int _numLines2 = LEN(_text2);

static char *_text3[] = {
    "  SOME PERSONAL GREETiNGS:",
    "",
    "i  FELT REALLY  HONORED WHEN",
    "MOTiON/ARTSTATE  RELEASED AN",
    "AWESOME AMiGA \"REMiX\" OF OUR",
    "DEADLiNE 2023 WiNDOWS iNTRO.",
    "BEST OF LUCK  ON YOUR FUTURE",
    "SCENE ACTiViTiES, MATE!",
    "",
    "  THANKS  TO   PS/TPOLM  FOR",
    "KEEPiNG  US UP-TO-DATE  WiTH",
    "HiS MONTHLY NEWS SHOW.",
    "",
    "  A    BiG   THANK-YOU    TO",
    "ViRGiLL / ATZ^HJB^MON    FOR",
    "APPRECiATiNG THE  SUPER FAST",
    "SPACECUT VECTORS iN OUR LAST",
    "iNTRO ;)",
};
static int _numLines3 = LEN(_text3);

static char *_text3B[] = {
    "FOR  THE   MiRACLE  THAT  iS",
    "\"SQUiSHY\",  A BiG  SHOUT-OUT",
    "TO FERRiS/LOGiCOMA!",
    "",
    "  THANKS   TO   ARPS/MOSTLY,",
    "TMB/SCOOPEX AND RUDi/SSR FOR",
    "PROViDiNG COUNTLESS HOURS OF",
    "RETRO DEMO  ENTERTAiNMENT ON",
    "THEiR  YOUTUBE  CHANNELS.  i",
    "SPEND  WAY   TOO  MUCH  TiME",
    "THERE!",
    "",
    "  AND  LAST  BUT NOT  LEAST,",
    "WHAT'S UP ZAK/FROZAK?",
};
static int _numLines3B = LEN(_text3B);

static char *_text4[] = {
    "           MUCH LOVE TO:",
    "",
    "             ALCATRAZ",
    "       ANARCHY ~ ANDROMEDA",
    "     ARTSTATE ~ ASD ~ CALODOX",
    " COMPLEX ~ FAiRLiGHT ~ FARBRAUSCH",
    "    FROZAK ~ HAUJOBB ~ KEFRENS",
    "     LOGiCOMA ~ MELON DEZiGN",
    "    MOODS PLATEAU ~ NORTH STAR",
    "        PARADOX ~ QUARTEX",
    "   RAZOR 1911 ~ REBELS ~ SANiTY",
    "       SCOOPEX ~ SPACEBALLS",
    "           SPREADPOiNT",
    "    SWiSS CRACKiNG ASSOCiATiON",
    "    THE SiLENTS ~ TRBL ~ TRSi",
    "             VANTAGE",
};
static int _numLines4 = LEN(_text4);

///////////////////////////////////////////////////////////////////////////////
// INITIAL KEYFRAME VARIABLES
///////////////////////////////////////////////////////////////////////////////
static const fw_vec4f _glenzPosInit = {70,-10};
static const fw_vec4f _glenzRotInit = {0};
static const fw_vec4f _twistFactorInit = {0};
static const fw_vec4f _glenzScaleInit = {1,1,1};
static const fw_vec4f _glenzBounceAmountInit = {1};
static const fw_vec4f _glenzBounceBaseInit = {-.5f};
static const fw_vec4f _glenzDistortInit = {1};
static const fw_vec4f _glenzPyramidFactorInit = {0};
static const fw_vec4f _glenzShadowScaleInit = {1};

///////////////////////////////////////////////////////////////////////////////
// KEY FRAME VARIABLES
///////////////////////////////////////////////////////////////////////////////
static fw_vec4f _glenzPos = _glenzPosInit;
static fw_vec4f _glenzRot = _glenzRotInit;
static fw_vec4f _twistFactor = _twistFactorInit;
static fw_vec4f _glenzScale = _glenzScaleInit;
static fw_vec4f _glenzBounceAmount = _glenzBounceAmountInit;
static fw_vec4f _glenzBounceBase = _glenzBounceBaseInit;
static fw_vec4f _glenzDistort = _glenzDistortInit;
static fw_vec4f _glenzPyramidFactor = _glenzPyramidFactorInit;
static fw_vec4f _glenzShadowScale = _glenzShadowScaleInit;

static fw_vec4f _glenzColor = _glenzColors[0];

///////////////////////////////////////////////////////////////////////////////
// ANIM START / STOP DECLARATIONS
///////////////////////////////////////////////////////////////////////////////
static void animStartedDelay(fw_animation *anim, fw_timer_data *time);
static void animCompletedDelay(fw_animation *anim, fw_timer_data *time);

static void animStartedTextLogo(fw_animation *anim, fw_timer_data *time);
static void animCompletedTextLogo(fw_animation *anim, fw_timer_data *time);

static void animStartedTextLogoLoop(fw_animation *anim, fw_timer_data *time);
static void animCompletedTextLogoLoop(fw_animation *anim, fw_timer_data *time);

static void animStartedText1(fw_animation *anim, fw_timer_data *time);
static void animCompletedText1(fw_animation *anim, fw_timer_data *time);

static void animStartedText2(fw_animation *anim, fw_timer_data *time);
static void animCompletedText2(fw_animation *anim, fw_timer_data *time);

static void animStartedText3(fw_animation *anim, fw_timer_data *time);
static void animCompletedText3(fw_animation *anim, fw_timer_data *time);

static void animStartedText3B(fw_animation *anim, fw_timer_data *time);
static void animCompletedText3B(fw_animation *anim, fw_timer_data *time);

static void animStartedText4(fw_animation *anim, fw_timer_data *time);
static void animCompletedText4(fw_animation *anim, fw_timer_data *time);

static void animStartedGlenz0(fw_animation *anim, fw_timer_data *time);
static void animCompletedGlenz0(fw_animation *anim, fw_timer_data *time);

static void animStartedGlenz1(fw_animation *anim, fw_timer_data *time);
static void animCompletedGlenz1(fw_animation *anim, fw_timer_data *time);

static void animStartedGlenz1B(fw_animation *anim, fw_timer_data *time);
static void animCompletedGlenz1B(fw_animation *anim, fw_timer_data *time);

static void animStartedGlenz2(fw_animation *anim, fw_timer_data *time);
static void animCompletedGlenz2(fw_animation *anim, fw_timer_data *time);

static void animStartedGlenz3(fw_animation *anim, fw_timer_data *time);
static void animCompletedGlenz3(fw_animation *anim, fw_timer_data *time);

static void animStartedGlenz4(fw_animation *anim, fw_timer_data *time);
static void animCompletedGlenz4(fw_animation *anim, fw_timer_data *time);

///////////////////////////////////////////////////////////////////////////////
// KEY FRAMES
///////////////////////////////////////////////////////////////////////////////
static fw_keyframe _keysDelay[] = {
    {0, 7, _glenzRotInit, {360}, LinearInterpolation, &_glenzRot},
    {0, 2, {70,-285}, _glenzPosInit, QuadraticEaseInOut, &_glenzPos},
};

static fw_keyframe _keysGlenz0[] = {
    {0, 28, _glenzRotInit, {4*360}, LinearInterpolation, &_glenzRot},
};

static fw_keyframe _keysGlenz1[] = {
    {0, 29, _glenzRotInit, {2*360}, LinearInterpolation, &_glenzRot},
    {0, 3, _glenzPosInit, {-70,-10}, QuadraticEaseInOut, &_glenzPos},

    {2, 6, _twistFactorInit, {200}, QuadraticEaseInOut, &_twistFactor},
    {7, 11, {200}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},

    {11, 13, _twistFactorInit, {200}, QuadraticEaseInOut, &_twistFactor},
    {14, 16, {200}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},

    {16, 20, _twistFactorInit, {200}, QuadraticEaseInOut, &_twistFactor},
    {21, 25, {200}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},
};

static fw_keyframe _keysGlenz1B[] = {
    {0, 29, _glenzRotInit, {2*360}, LinearInterpolation, &_glenzRot},
    {0, 3, _glenzPosInit, {-70,-10}, QuadraticEaseInOut, &_glenzPos},

    {5, 9, _twistFactorInit, {200}, QuadraticEaseInOut, &_twistFactor},
    {10, 14, {200}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},

    {14, 16, _twistFactorInit, {200}, QuadraticEaseInOut, &_twistFactor},
    {17, 19, {200}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},

    {19, 23, _twistFactorInit, {200}, QuadraticEaseInOut, &_twistFactor},
    {24, 28, {200}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},
};

static fw_keyframe _keysGlenz2[] = {
    {0, 48, _glenzRotInit, {10*360}, LinearInterpolation, &_glenzRot},
    {0, 3, {-70,-10}, _glenzPosInit, QuadraticEaseInOut, &_glenzPos},

    {4, 9, {0}, {1}, QuadraticEaseInOut, &_glenzPyramidFactor},
    {4, 9, _glenzScaleInit, {.5f,.8f,.5f}, QuadraticEaseInOut, &_glenzScale},

    {16, 21, {1}, {0}, QuadraticEaseInOut, &_glenzPyramidFactor},
    {16, 21, {.5f,.8f,.5f}, _glenzScaleInit, QuadraticEaseInOut, &_glenzScale},

    {21, 26, _glenzDistortInit, {1.6f}, QuadraticEaseInOut, &_glenzDistort},

    {32, 36, {1.6f}, {1.2f}, QuadraticEaseInOut, &_glenzDistort},
    {32, 36, _glenzScaleInit, {1.f,1.5f,.2f}, QuadraticEaseInOut, &_glenzScale},

    {43, 46, {1.2f}, _glenzDistortInit, QuadraticEaseInOut, &_glenzDistort},
    {43, 46, {1.f,1.5f,.2f}, _glenzScaleInit, QuadraticEaseInOut, &_glenzScale},
};

static fw_keyframe _keysGlenz3[] = {
    {0, 5, _glenzRotInit, {360}, QuadraticEaseOut, &_glenzRot},
    {28, 30, _glenzRotInit, {360}, QuadraticEaseInOut, &_glenzRot},

    {0, 3, _glenzPosInit, {-70,-10}, QuadraticEaseInOut, &_glenzPos},

    {6, 9, _twistFactorInit, {500}, QuadraticEaseInOut, &_twistFactor},
    {6, 9, {-70,-10}, {-70,0}, QuadraticEaseInOut, &_glenzPos},
    {6, 10, _glenzBounceAmountInit, {0}, QuadraticEaseInOut, &_glenzBounceAmount},
    {6, 10, _glenzBounceBaseInit, {0}, QuadraticEaseInOut, &_glenzBounceBase},

    {6, 8, _glenzScaleInit, {.8f,3.2f,.8f}, QuadraticEaseInOut, &_glenzScale},
    {6, 9, _glenzShadowScaleInit, {0}, QuadraticEaseInOut, &_glenzShadowScale},

    {12, 15, _glenzDistortInit, {2.5f}, QuadraticEaseInOut, &_glenzDistort},
    {19, 22, {2.5f}, _glenzDistortInit, QuadraticEaseInOut, &_glenzDistort},
    {23, 24, _glenzDistortInit, {2.5f}, QuadraticEaseInOut, &_glenzDistort},
    {26, 28, {2.5f}, _glenzDistortInit, QuadraticEaseInOut, &_glenzDistort},

    {27, 30, {.8f,3.2f,.8f}, _glenzScaleInit, QuadraticEaseInOut, &_glenzScale},
    {27, 30, {-70,0}, {-70,-10}, QuadraticEaseInOut, &_glenzPos},
    {27, 30, {0}, _glenzShadowScaleInit, QuadraticEaseInOut, &_glenzShadowScale},
    {27, 29, {500}, _twistFactorInit, QuadraticEaseInOut, &_twistFactor},
    {27, 30, {0}, _glenzBounceAmountInit, QuadraticEaseInOut, &_glenzBounceAmount},
    {27, 30, {0}, _glenzBounceBaseInit, QuadraticEaseInOut, &_glenzBounceBase},
};

static fw_keyframe _keysGlenz4[] = {
    [KEYFRAME_INDEX_COLOR] = {1, 2, _glenzColors[0], _glenzColors[1], QuadraticEaseInOut, &_glenzColor},
    {0, 3, {-70,-10}, _glenzPosInit, QuadraticEaseInOut, &_glenzPos},
};


///////////////////////////////////////////////////////////////////////////////
// ANIMS
///////////////////////////////////////////////////////////////////////////////

static fw_animation _anims[] = {
    [ANIM_DELAY] = {
        .isAutostart = TRUE,
        .keyframes = _keysDelay,
        .numKeyframes = LEN(_keysDelay),
        .started_proc = animStartedDelay,
        .completed_proc = animCompletedDelay,
    },
    [ANIM_TEXT_LOGO] = {
        .isAutostart = TRUE,
        .started_proc = animStartedTextLogo,
        .completed_proc = animCompletedTextLogo,
    },
    [ANIM_TEXT_LOGO_LOOP] = {
        .isAutostart = FALSE,
        .started_proc = animStartedTextLogoLoop,
        .completed_proc = animCompletedTextLogoLoop,
    },
    [ANIM_TEXT1] = {
        .isAutostart = FALSE,
        .started_proc = animStartedText1,
        .completed_proc = animCompletedText1,
    },
    [ANIM_TEXT2] = {
        .isAutostart = FALSE,
        .started_proc = animStartedText2,
        .completed_proc = animCompletedText2,
    },
    [ANIM_TEXT3] = {
        .isAutostart = FALSE,
        .started_proc = animStartedText3,
        .completed_proc = animCompletedText3,
    },
    [ANIM_TEXT3B] = {
        .isAutostart = FALSE,
        .started_proc = animStartedText3B,
        .completed_proc = animCompletedText3B,
    },
    [ANIM_TEXT4] = {
        .isAutostart = FALSE,
        .started_proc = animStartedText4,
        .completed_proc = animCompletedText4,
    },
    [ANIM_GLENZ0] = {
        .isAutostart = FALSE,
        .keyframes = _keysGlenz0,
        .numKeyframes = LEN(_keysGlenz0),
        .started_proc = animStartedGlenz0,
        .completed_proc = animCompletedGlenz0,
    },
    [ANIM_GLENZ1] = {
        .isAutostart = FALSE,
        .keyframes = _keysGlenz1,
        .numKeyframes = LEN(_keysGlenz1),
        .started_proc = animStartedGlenz1,
        .completed_proc = animCompletedGlenz1,
    },
    [ANIM_GLENZ1B] = {
        .isAutostart = FALSE,
        .keyframes = _keysGlenz1B,
        .numKeyframes = LEN(_keysGlenz1B),
        .started_proc = animStartedGlenz1B,
        .completed_proc = animCompletedGlenz1B,
    },
    [ANIM_GLENZ2] = {
        .isAutostart = FALSE,
        .keyframes = _keysGlenz2,
        .numKeyframes = LEN(_keysGlenz2),
        .started_proc = animStartedGlenz2,
        .completed_proc = animCompletedGlenz2,
    },
    [ANIM_GLENZ3] = {
        .isAutostart = FALSE,
        .keyframes = _keysGlenz3,
        .numKeyframes = LEN(_keysGlenz3),
        .started_proc = animStartedGlenz3,
        .completed_proc = animCompletedGlenz3,
    },
    [ANIM_GLENZ4] = {
        .isAutostart = FALSE,
        .keyframes = _keysGlenz4,
        .numKeyframes = LEN(_keysGlenz4),
        .started_proc = animStartedGlenz4,
        .completed_proc = animCompletedGlenz4,
    },
};

static fw_animation_schedule _animSchedule = {
    _anims,
    LEN(_anims)
};

///////////////////////////////////////////////////////////////////////////////
// ANIM START / STOP IMPLEMENTATIONS
///////////////////////////////////////////////////////////////////////////////
static void animStartedDelay(fw_animation *anim, fw_timer_data *time) {
}

static void animCompletedDelay(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_GLENZ0], time);
}

static void animStartedTextLogo(fw_animation *anim, fw_timer_data *time) {
}

static void animCompletedTextLogo(fw_animation *anim, fw_timer_data *time) {
}

static void animStartedTextLogoLoop(fw_animation *anim, fw_timer_data *time) {
    _isLogoLoopEnabled = TRUE;
}

static void animCompletedTextLogoLoop(fw_animation *anim, fw_timer_data *time) {
}

static void animStartedText1(fw_animation *anim, fw_timer_data *time) {
    _isText1Enabled = TRUE;
}

static void animCompletedText1(fw_animation *anim, fw_timer_data *time) {
    _isText1Enabled = FALSE;
}

static void animStartedText2(fw_animation *anim, fw_timer_data *time) {
    _isText2Enabled = TRUE;
}

static void animCompletedText2(fw_animation *anim, fw_timer_data *time) {
    _isText2Enabled = FALSE;
}

static void animStartedText3(fw_animation *anim, fw_timer_data *time) {
    _isText3Enabled = TRUE;
}

static void animCompletedText3(fw_animation *anim, fw_timer_data *time) {
    _isText3Enabled = FALSE;
}

static void animStartedText3B(fw_animation *anim, fw_timer_data *time) {
    _isText3BEnabled = TRUE;
}

static void animCompletedText3B(fw_animation *anim, fw_timer_data *time) {
    _isText3BEnabled = FALSE;
}

static void animStartedText4(fw_animation *anim, fw_timer_data *time) {
    _isText4Enabled = TRUE;
}

static void animCompletedText4(fw_animation *anim, fw_timer_data *time) {
    _isText4Enabled = FALSE;
}

static void animStartedGlenz0(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_TEXT1], time);
}

static void animCompletedGlenz0(fw_animation *anim, fw_timer_data *time) {
    static int first = 1;
    if (first) {
        first = 0;
        fw_animation_start(&_anims[ANIM_GLENZ1], time);
    } else {
        fw_animation_start(&_anims[ANIM_GLENZ1B], time);
    }
}

static void animStartedGlenz1(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_TEXT2], time);
    fw_animation_start(&_anims[ANIM_TEXT_LOGO_LOOP], time);
}

static void animCompletedGlenz1(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_GLENZ2], time);
}

static void animStartedGlenz1B(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_TEXT2], time);
    fw_animation_start(&_anims[ANIM_TEXT_LOGO_LOOP], time);
}

static void animCompletedGlenz1B(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_GLENZ2], time);
}

static void animStartedGlenz2(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_TEXT3], time);
    fw_animation_start(&_anims[ANIM_TEXT3B], time);
    fw_animation_start(&_anims[ANIM_TEXT_LOGO_LOOP], time);
}

static void animCompletedGlenz2(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_GLENZ3], time);
}

static void animStartedGlenz3(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_TEXT4], time);
    fw_animation_start(&_anims[ANIM_TEXT_LOGO_LOOP], time);
}

static void animCompletedGlenz3(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_GLENZ4], time);
}

static void animStartedGlenz4(fw_animation *anim, fw_timer_data *time) {
    fw_animation_start(&_anims[ANIM_GLENZ0], time);
    fw_animation_start(&_anims[ANIM_TEXT_LOGO_LOOP], time);
}

static void animCompletedGlenz4(fw_animation *anim, fw_timer_data *time) {
    static int colorIdx = 1;
    _keysGlenz4[KEYFRAME_INDEX_COLOR].from = _glenzColors[colorIdx%_numGlenzColors];
    _keysGlenz4[KEYFRAME_INDEX_COLOR].to = _glenzColors[(colorIdx+1)%_numGlenzColors];
    colorIdx++;
}

///////////////////////////////////////////////////////////////////////////////
// INIT
///////////////////////////////////////////////////////////////////////////////
fw_keyframe createAnimTextLogoKey(fx_anim_text_meta *meta, int keyType, int totalKeyIdx, int totalCharIdx, int lineIdx, int charIdx) {
    const float delay = meta->delay;
    const float timeOffset = .5f*lineIdx + .095*charIdx;
    fw_keyframe key = {0};

    switch(keyType) {
    case 0:
        // Color.
        key.from = (fw_vec4f) {
            1,1,1,0
        };
        key.to = (fw_vec4f) {
            1,1,1,1
        };
        key.timeStart = delay+0.f+timeOffset;
        key.timeEnd = delay+.75f+timeOffset;
        key.easing_func = LinearInterpolation;
        key.value = &meta->modifiers[lineIdx][charIdx].color;
        break;
    case 1:
        // Translate.
        key.from = (fw_vec4f) {
            0,150
        };
        key.to = (fw_vec4f) {
            0,0
        };
        key.timeStart = delay+0.f+timeOffset;
        key.timeEnd = delay+2.5f+timeOffset;
        key.easing_func = BounceEaseOut;
        key.value = &meta->modifiers[lineIdx][charIdx].translate;
        break;
    }

    return key;
}

fw_keyframe createAnimTextLogoLoopKey(fx_anim_text_meta *meta, int keyType, int totalKeyIdx, int totalCharIdx, int lineIdx, int charIdx) {
    const float delay = meta->delay;
    const float duration = meta->duration;
    const float timeOffset = .035*charIdx  + .1*lineIdx;

    fw_keyframe key = {0};

    switch(keyType) {
    case 0:
        key.from = (fw_vec4f) {
            1,1,1,1
        };
        key.to = (fw_vec4f) {
            0,1,1
        };
        key.timeStart = delay+timeOffset;
        key.timeEnd = delay+.2f+timeOffset;
        key.easing_func = LinearInterpolation;
        key.value = &meta->modifiers[lineIdx][charIdx].scale;
        break;
    case 1:
        key.from = (fw_vec4f) {
            0,1,1
        };
        key.to = (fw_vec4f) {
            1,1,1,1
        };
        key.timeStart = delay+duration+timeOffset;
        key.timeEnd = delay+duration+.2f+timeOffset;
        key.easing_func = LinearInterpolation;
        key.value = &meta->modifiers[lineIdx][charIdx].scale;
        break;
    }

    return key;
}


fw_keyframe createAnimTextKey(fx_anim_text_meta *meta, int keyType, int totalKeyIdx, int totalCharIdx, int lineIdx, int charIdx) {
    const float delay = meta->delay;
    const float duration = meta->duration;
    const float timeOffset = .5f*lineIdx + .095*charIdx;
    fw_keyframe key = {0};

    switch(keyType) {
    case 0:
        // Color.
        key.from = (fw_vec4f) {
            1,1,1,0
        };
        key.to = (fw_vec4f) {
            1,1,1,1
        };
        key.timeStart = delay+0.f+timeOffset;
        key.timeEnd = delay+.75f+timeOffset;
        key.easing_func = LinearInterpolation;
        key.value = &meta->modifiers[lineIdx][charIdx].color;
        break;
    case 1:
        // Translate.
        key.from = (fw_vec4f) {
            0,150
        };
        key.to = (fw_vec4f) {
            0,0
        };
        key.timeStart = delay+0.f+timeOffset;
        key.timeEnd = delay+2.5f+timeOffset;
        key.easing_func = BounceEaseOut;
        key.value = &meta->modifiers[lineIdx][charIdx].translate;
        break;
    case 2:
        // Color.
        key.from = (fw_vec4f) {
            1,1,1,1
        };
        key.to = (fw_vec4f) {
            1,1,1,0
        };
        key.timeStart = delay+duration+.5f+timeOffset;
        key.timeEnd = delay+duration+1.f+timeOffset;
        key.easing_func = LinearInterpolation;
        key.value = &meta->modifiers[lineIdx][charIdx].color;
        break;
    case 3:
        // Translate.
        key.from = (fw_vec4f) {
            0,0
        };
        key.to = (fw_vec4f) {
            0,-100
        };
        key.timeStart = delay+duration+timeOffset;
        key.timeEnd = delay+duration+2.5f+timeOffset;
        key.easing_func = BounceEaseIn;
        key.value = &meta->modifiers[lineIdx][charIdx].translate;
        break;
    }

    return key;
}

static void colorizeChars(fx_anim_text_meta *meta, int line, int charFrom, int charTo, fw_vec4f color) {
    int keyIdx = 0;
    for (int i=0; i<meta->numLines; i++) {
        for (int j=0; j<strlen(meta->strings[i]); j++) {

            // Modify keyframe of the given line and its characters from `charFrom` to `charTo` (zero-based).
            if (i==line && j >= charFrom && j<=charTo) {
                // Keyframe 0 holds the color `to` value. See `createKey` callback function.
                meta->keys[keyIdx+0].to = color;
                // Keyframe 2 holds the color `from` value. See `createKey` callback function.
                meta->keys[keyIdx+2].from = color;
            }

            // Every character has `numKeysPerChar` keyframes.
            keyIdx += meta->numKeysPerChar;
        }
    }
}

void scene_0_init() {
    fw_animation_resetAnimationSchedule(&_animSchedule);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Lighting.
    glShadeModel(GL_FLAT);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[]) {
        0, 0, 5, 0
    });

    srand(1);

    _metaLogo.strings = _textLogo;
    _metaLogo.numLines = _numLinesLogo;
    _metaLogo.numKeysPerChar = 2;
    _metaLogo.createKey = createAnimTextLogoKey;
    fx_anim_text_init_meta(&_metaLogo);
    _anims[ANIM_TEXT_LOGO].keyframes = _metaLogo.keys;
    _anims[ANIM_TEXT_LOGO].numKeyframes = _metaLogo.numKeys;

    _metaLogoLoop.strings = _textLogo;
    _metaLogoLoop.numLines = _numLinesLogo;
    _metaLogoLoop.numKeysPerChar = 2;
    _metaLogoLoop.delay = 0;
    _metaLogoLoop.duration = .3f;
    _metaLogoLoop.createKey = createAnimTextLogoLoopKey;
    fx_anim_text_init_meta(&_metaLogoLoop);
    fx_anim_text_setDefaultColor(&_metaLogoLoop, (fw_vec4f) {
        1,1,1,1
    });
    _anims[ANIM_TEXT_LOGO_LOOP].keyframes = _metaLogoLoop.keys;
    _anims[ANIM_TEXT_LOGO_LOOP].numKeyframes = _metaLogoLoop.numKeys;

    _meta1.strings = _text1;
    _meta1.numLines = _numLines1;
    _meta1.numKeysPerChar = 4;
    _meta1.delay = 0;
    _meta1.duration = 15;
    _meta1.createKey = createAnimTextKey;
    fx_anim_text_init_meta(&_meta1);
    _anims[ANIM_TEXT1].keyframes = _meta1.keys;
    _anims[ANIM_TEXT1].numKeyframes = _meta1.numKeys;

    _meta2.strings = _text2;
    _meta2.numLines = _numLines2;
    _meta2.numKeysPerChar = 4;
    _meta2.delay = 1;
    _meta2.duration = 15;
    _meta2.createKey = createAnimTextKey;
    fx_anim_text_init_meta(&_meta2);
    _anims[ANIM_TEXT2].keyframes = _meta2.keys;
    _anims[ANIM_TEXT2].numKeyframes = _meta2.numKeys;

    _meta3.strings = _text3;
    _meta3.numLines = _numLines3;
    _meta3.numKeysPerChar = 4;
    _meta3.delay = 1;
    _meta3.duration = 15;
    _meta3.createKey = createAnimTextKey;
    fx_anim_text_init_meta(&_meta3);
    _anims[ANIM_TEXT3].keyframes = _meta3.keys;
    _anims[ANIM_TEXT3].numKeyframes = _meta3.numKeys;

    _meta3B.strings = _text3B;
    _meta3B.numLines = _numLines3B;
    _meta3B.numKeysPerChar = 4;
    _meta3B.delay = 21;
    _meta3B.duration = 15;
    _meta3B.createKey = createAnimTextKey;
    fx_anim_text_init_meta(&_meta3B);
    _anims[ANIM_TEXT3B].keyframes = _meta3B.keys;
    _anims[ANIM_TEXT3B].numKeyframes = _meta3B.numKeys;

    _meta4.strings = _text4;
    _meta4.numLines = _numLines4;
    _meta4.numKeysPerChar = 4;
    _meta4.delay = 1;
    _meta4.duration = 15;
    _meta4.createKey = createAnimTextKey;
    fx_anim_text_init_meta(&_meta4);
    _anims[ANIM_TEXT4].keyframes = _meta4.keys;
    _anims[ANIM_TEXT4].numKeyframes = _meta4.numKeys;

    fw_vec4f charColor = {0.922,0.278,0.192, 1};
    colorizeChars(&_meta3, 3, 0,14, charColor);
    colorizeChars(&_meta3, 9, 15,22, charColor);
    colorizeChars(&_meta3, 14, 0,20, charColor);

    colorizeChars(&_meta3B, 2, 3,17, charColor);
    colorizeChars(&_meta3B, 4, 16,26, charColor);
    colorizeChars(&_meta3B, 5, 0,10,charColor);
    colorizeChars(&_meta3B, 5, 16,23,charColor);
    colorizeChars(&_meta3B, 13, 10,19, charColor);
}

static void text(fx_anim_text_meta *meta, fw_font_face *fontFace, int posX, int posY) {
    // Drop shadow.
    fw_vec3f overrideColor = {0,0,0};
    fx_anim_text_render(meta, fontFace, posX+.5f,posY+.5f, 0.5, &overrideColor);
    fx_anim_text_render(meta, fontFace, posX+1,posY+1, 0.5, &overrideColor);

    // Draw text.
    fx_anim_text_render(meta, fontFace, posX,posY, .5, NULL);
}

static void putGlenzCube(float bounceAmount, float axisX, float objectAngle, float twistAngle) {
    getGlenzCubes()[0].c[1] = _glenzColor;

    glEnable(GL_LIGHTING);
    glPushMatrix();
    {
        glTranslatef(0, _glenzBounceBase.x + 1.5f * bounceAmount, -7);
        glRotatef(objectAngle, axisX, 2.0f, 3.0f);
        glRotatef(twistAngle, 0,1,0);
        glScalef(_glenzScale.x,_glenzScale.y,_glenzScale.z);

        static float previousGlenzDistort = _glenzDistortInit.x;
        if (previousGlenzDistort != _glenzDistort.x) {
            previousGlenzDistort = _glenzDistort.x;
            fx_glenz_modifyCubeCenterVertices(&getGlenzCubes()[0], _glenzDistort.x);
            fw_object_3d_calculateFaceNormals(&getGlenzCubes()[0]);
            fw_object_3d_updateArray(&getGlenzCubes()[0]);
        }

        static float previousGlenzPyramidFactor = _glenzPyramidFactorInit.x;
        if (previousGlenzPyramidFactor != _glenzPyramidFactor.x) {
            previousGlenzPyramidFactor = _glenzPyramidFactor.x;
            fx_glenz_modifyCubeVerticesToPyramid(&getGlenzCubes()[0], _glenzPyramidFactor.x);
            fw_object_3d_calculateFaceNormals(&getGlenzCubes()[0]);
            fw_object_3d_updateArray(&getGlenzCubes()[0]);
        }

        static float previousColor = _glenzColors[0].w;
        if (previousColor != _glenzColor.w) {
            previousColor = _glenzColor.w;
            fw_object_3d_updateArray(&getGlenzCubes()[0]);
        }

        fw_object_3d_putFacesArray(&getGlenzCubes()[0]);
    }
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

static void putGlenzCubeShadow(float bounceAmount, float axisX, float objectAngle, float twistAngle) {
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    {
        glTranslatef(0, -2, -7);
        float s = _glenzShadowScale.x * (1.f - .25f * bounceAmount);
        glScalef(s,0,s);
        glRotatef(objectAngle, axisX, 2.0f, 3.0f);
        glRotatef(twistAngle, 0,1,0);
        glScalef(_glenzScale.x,_glenzScale.y,_glenzScale.z);

        static float previousGlenzDistort = _glenzDistortInit.x;
        if (previousGlenzDistort != _glenzDistort.x) {
            previousGlenzDistort = _glenzDistort.x;
            fx_glenz_modifyCubeCenterVertices(&getGlenzCubes()[1], _glenzDistort.x);
            fw_object_3d_updateArray(&getGlenzCubes()[1]);
        }

        static float previousGlenzPyramidFactor = _glenzPyramidFactorInit.x;
        if (previousGlenzPyramidFactor != _glenzPyramidFactor.x) {
            previousGlenzPyramidFactor = _glenzPyramidFactor.x;
            fx_glenz_modifyCubeVerticesToPyramid(&getGlenzCubes()[1], _glenzPyramidFactor.x);
            fw_object_3d_updateArray(&getGlenzCubes()[1]);
        }

        fw_object_3d_putFacesArray(&getGlenzCubes()[1]);
    }
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

static void twistGlenzCube(fw_timer_data *time) {
    const float t = time->elapsed - _animSchedule.animations[ANIM_DELAY].timeStartedAt;

    int scissorHeight=1;
    const float twistFactor= _twistFactor.x;
    const float twistSpeed=.5f;
    const float bounceAmount = _glenzBounceAmount.x * fabs(sinf(t*4.3622f));
    const float objectAngle = _glenzRot.x;
    const float axisX = 4.f * sinf(t);

    if (twistFactor == 0) {
        scissorHeight = FW_RENDER_HEIGHT;
    }

    const float twistFactorSpeed = twistFactor*cosf(t*twistSpeed);
    const float twistAngleSpeed = sinf(t*twistSpeed)*500.f;

    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    for (int i=0; i<FW_RENDER_HEIGHT; i+=scissorHeight) {
        glScissor(0,i,FW_RENDER_WIDTH,scissorHeight);

        float twistAngle = ((float)i/(float)FW_RENDER_HEIGHT) * twistFactorSpeed + twistAngleSpeed;

        putGlenzCubeShadow(bounceAmount, axisX, objectAngle, twistAngle);
        putGlenzCube(bounceAmount, axisX, objectAngle, twistAngle);
    }
    glCullFace(GL_BACK);
    for (int i=0; i<FW_RENDER_HEIGHT; i+=scissorHeight) {
        glScissor(0,i,FW_RENDER_WIDTH,scissorHeight);

        float twistAngle = ((float)i/(float)FW_RENDER_HEIGHT) * twistFactorSpeed + twistAngleSpeed;

        putGlenzCube(bounceAmount, axisX, objectAngle, twistAngle);
    }
    glDisable(GL_CULL_FACE);
    glDisable(GL_SCISSOR_TEST);
}

///////////////////////////////////////////////////////////////////////////////
// EXECUTE
///////////////////////////////////////////////////////////////////////////////
void scene_0_execute(fw_timer_data *time) {
    fw_animation_processAnimationSchedule(&_animSchedule, time);

    fw_render_bindTextureBufferBegin();

    fw_projection_perspective();
    fw_render_viewportLowRes(_glenzPos.x, _glenzPos.y);

    twistGlenzCube(time);
    fw_render_bindTextureBufferEnd();

    fw_render_viewportHiRes(0,0);
    fw_render_clearHiRes(_clearColor.x,_clearColor.y,_clearColor.z,_clearColor.w);

    fw_image_renderBegin(getSpritesheetImage(), 1);
    // BG twirl color.
    glColor3f(_bgTwirlColor.x,_bgTwirlColor.y,_bgTwirlColor.z);
    fw_image_putImage(getSpritesheetImage());
    fw_image_renderEnd();

    if (_isLogoLoopEnabled) {
        text(&_metaLogoLoop, getLogoFontFace(), 4,10);
    } else {
        text(&_metaLogo, getLogoFontFace(), 4,10);
    }

    if (_isText1Enabled) {
        text(&_meta1, getFontFace(), 30,94);
    } else if (_isText2Enabled) {
        text(&_meta2, getFontFace(), 195,94);
    } else if (_isText3Enabled || _isText3BEnabled) {
        text(&_meta3, getFontFace(), 30,94);
        text(&_meta3B, getFontFace(), 30,94);
    } else if (_isText4Enabled) {
        text(&_meta4, getFontFace(), 195,94);
    }

    // Finally render low-res glenz cube from texture.
    fw_render_renderTextureBuffer();

    /*
        // 1:4 Scanlines
        fw_render_viewportHiRes(0,0);
        fw_projection_ortho();
        glColor4f(0,0,0,.1f);
        glPushMatrix();
        glLoadIdentity();
        glBegin(GL_LINES);
        for (float i=0; i<FW_WINDOW_HEIGHT/2; i+=1) {
            glVertex2f(0, i);
            glVertex2f(FW_WINDOW_WIDTH, i);
        }
        glEnd();
        glPopMatrix();
    */
}

