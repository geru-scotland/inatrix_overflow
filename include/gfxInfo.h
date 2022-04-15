//
// Created by Geru on 14/4/22.
//

#ifndef INATRIX_OVERFLOW_GFX_BITMAPS_H
#define INATRIX_OVERFLOW_GFX_BITMAPS_H

#include "nds.h"
#define GFX_SIZE 2

// Identificadores para los GFX, asociamos uno a cada sprite.
// Deben coincidir con SpriteIndex. TODO: Revisar esto, está feo.
typedef enum{
    GFX_INATRIX = 0
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
