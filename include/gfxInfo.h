//
// Created by Eideann on 14/4/22.
//

#ifndef INATRIX_OVERFLOW_GFX_BITMAPS_H
#define INATRIX_OVERFLOW_GFX_BITMAPS_H

#include "nds.h"
#define GFX_SIZE 2

#define GFX_SIZE_16_16 16392
#define GFX_SIZE_32_32 32800

#define GFX_256COLOR_FORMAT 1

// Identificadores para los GFX, asociamos uno a cada sprite.
// Deben coincidir con SpriteIndex. TODO: Revisar esto, está feo.
typedef enum{
    GFX_BALL = 0,
    GFX_BALL2,
    GFX_ONE,
    GFX_ZERO,
    GFX_INATRIX_1
} GfxID;


typedef struct {
    u16* memAddress;
    uint8 id;
    u8* bitmap;
    SpriteSize size;
    SpriteColorFormat colorFormat;
} GfxData;

extern GfxData* gfxList[GFX_SIZE];

extern void gfxInfo_setBitmaps();
extern void gfxInfo_init();

#endif //INATRIX_OVERFLOW_GFX_BITMAPS_H
