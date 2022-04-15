//
// Created by Geru on 15/4/22.
//
#include "../include/gfxInfo.h"

GfxData* gfxList[GFX_SIZE];

u8 ball[256] =
        {
                0,0,0,0,0,0,2,2,
                0,0,0,0,0,2,2,2,	//	0,0,0,0,0,0,2,2, 2,2,0,0,0,0,0,0,
                0,0,0,0,2,2,2,2,
                0,0,0,2,2,2,2,2,	//	0,0,0,0,0,2,2,2, 2,2,2,0,0,0,0,0,
                0,0,2,2,2,2,2,2,
                0,2,2,2,2,2,2,2,	//	0,0,0,0,2,2,2,2, 2,2,2,2,0,0,0,0,
                2,2,2,2,2,2,2,2,
                2,2,2,2,2,2,2,2,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,

                2,2,0,0,0,0,0,0,
                2,2,2,0,0,0,0,0,	//	0,0,2,2,2,2,2,2, 2,2,2,2,2,2,0,0,
                2,2,2,2,0,0,0,0,
                2,2,2,2,2,0,0,0,	//	0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
                2,2,2,2,2,2,0,0,
                2,2,2,2,2,2,2,0,	//	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
                2,2,2,2,2,2,2,2,
                2,2,2,2,2,2,2,2,	//	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

                1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
                0,1,1,1,1,1,1,1,
                0,0,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
                0,0,0,1,1,1,1,1,
                0,0,0,0,1,1,1,1,	//	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
                0,0,0,0,0,1,1,1,
                0,0,0,0,0,0,1,1,	//	0,0,1,1,1,1,1,1, 1,1,1,1,1,1,0,0,

                1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,	//	0,0,0,1,1,1,1,1, 1,1,1,1,1,0,0,0,
                1,1,1,1,1,1,1,0,
                1,1,1,1,1,1,0,0,	//	0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,
                1,1,1,1,1,0,0,0,
                1,1,1,1,0,0,0,0,	//	0,0,0,0,0,1,1,1, 1,1,1,0,0,0,0,0,
                1,1,1,0,0,0,0,0,
                1,1,0,0,0,0,0,0,	//	0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,
        };

void gfxInfo_init(){

    // Llevar esto a otro fichero, gfxInfo.c o similar.
    // Tener cuidado con el orden, asegurarte de que primero invoca
    // la función donde se estén cargando.
    // Geru: Primero se crea el struct en memoria dinámica o heap
    // Luego tendremos que liberarla, si no -> memory leaks.

    /* BALL */
    gfxList[GFX_BALL] = malloc(sizeof(GfxData));
    gfxList[GFX_BALL]->memAddress = NULL;
    gfxList[GFX_BALL]->bitmap = ball;
    gfxList[GFX_BALL]->id = GFX_BALL;
    gfxList[GFX_BALL]->size = SpriteSize_16x16;
    gfxList[GFX_BALL]->colorFormat = SpriteColorFormat_256Color;

    /* BALL 2 */

    /*
     * Se pueden nutrir del mismo bitmap, porque en el loadGfx
     * lo copian en la memoria reservada por el oam
     */
    gfxList[GFX_BALL2] = malloc(sizeof(GfxData));
    gfxList[GFX_BALL2]->memAddress = NULL;
    gfxList[GFX_BALL2]->bitmap = ball;
    gfxList[GFX_BALL2]->id = GFX_BALL2;
    gfxList[GFX_BALL2]->size = SpriteSize_16x16;
    gfxList[GFX_BALL2]->colorFormat = SpriteColorFormat_256Color;

    /* INATRIX */

    /* NUMBER_1 */
}