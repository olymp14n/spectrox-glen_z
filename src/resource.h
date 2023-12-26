#ifndef FW_RESOURCE_H
#define FW_RESOURCE_H

#include <GL/gl.h>
#include "fw/font.h"
#include "fw/image.h"
#include "fw/object_3d.h"

void fw_resource_init();

fw_image *getSpritesheetImage();
fw_font_face *getFontFace();
fw_font_face *getLogoFontFace();
fw_object_3d *getGlenzCubes();

#endif
