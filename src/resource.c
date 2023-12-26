#include "resource.h"
#include "fw/image.h"
#include "fw/lut.h"
#include "fw/font.h"
#include "dat/spritesheet_pixels.h"
#include "dat/font_pixels.h"
#include "dat/font_meta.h"
#include "dat/logo_font_pixels.h"
#include "dat/logo_font_meta.h"
#include "fx/glenz.h"

static fw_image _spritesheetImage;
static fw_image _fontImage;
static fw_image _logoFontImage;

static fw_object_3d _glenzCubes[2];

void fw_resource_init() {
    fw_lut_init();

    // Image.
    fw_image_initRGBA(&_spritesheetImage, SPRITESHEET_PIXELS_WIDTH, SPRITESHEET_PIXELS_HEIGHT, _spritesheetPixels);

    // Font.
    fw_image_initRGBA(&_fontImage, FONT_PIXELS_WIDTH, FONT_PIXELS_HEIGHT, _fontPixels);
    fw_font_initFontFace(&_fontFace, &_fontImage);

    fw_image_initRGBA(&_logoFontImage, LOGO_FONT_PIXELS_WIDTH, LOGO_FONT_PIXELS_HEIGHT, _logoFontPixels);
    fw_font_initFontFace(&_logoFontFace, &_logoFontImage);

    fx_glenz_initCube(&_glenzCubes[0]);
    fx_glenz_initCube(&_glenzCubes[1]);


    _glenzCubes[0].c[0] = (fw_vec4f){1,1,1,.95f};
    _glenzCubes[0].c[1] = (fw_vec4f){.85f,0,0,.7f};

    _glenzCubes[1].c[0] = (fw_vec4f){0,0,0,.25};
    _glenzCubes[1].c[1] = (fw_vec4f){0,0,0,.25f};

    fw_object_3d_initArray(&_glenzCubes[0]);
    fw_object_3d_initArray(&_glenzCubes[1]);
}

fw_image *getSpritesheetImage() {
    return &_spritesheetImage;
}

fw_font_face *getFontFace() {
    return &_fontFace;
}

fw_font_face *getLogoFontFace() {
    return &_logoFontFace;
}

fw_object_3d *getGlenzCubes() {
    return _glenzCubes;
}
