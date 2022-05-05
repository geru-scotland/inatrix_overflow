//
// Created by Geru on 15/4/22.
//
#include "gfxInfo.h"
#include "utils.h"
#include "sprites.h"

GfxData* gfxList[GFX_SIZE];
uint8 gfxGUID = 0;

u8 redCapsule[256] = {

        0,0,0,0,0,1,1,1,
        0,0,0,0,1,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,0,0,0,0,
        0,0,0,1,1,1,1,1,

        1,1,1,1,0,0,0,0,
        0,0,0,0,1,0,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,
        1,1,1,1,1,1,0,0,

        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,1,1,1,1,1,
        0,0,0,0,1,1,1,1,
        0,0,0,0,0,1,1,1,

        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,0,
        1,1,1,1,1,0,0,0,
        1,1,1,1,0,0,0,0

};

u8 blueCapsule[256] = {

        0,0,0,0,0,5,5,5,
        0,0,0,0,5,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,0,0,0,0,
        0,0,0,5,5,5,5,5,

        5,5,5,5,0,0,0,0,
        0,0,0,0,5,0,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        0,0,0,0,0,5,0,0,
        5,5,5,5,5,5,0,0,

        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,5,5,5,5,5,
        0,0,0,0,5,5,5,5,
        0,0,0,0,0,5,5,5,

        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,5,0,0,
        5,5,5,5,5,0,0,0,
        5,5,5,5,0,0,0,0
};

u8 digitOne[256] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,

        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,

        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,4,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,

        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        4,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0


};

u8 digitZero[256] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,4,4,
        0,0,0,0,0,4,4,4,
        0,0,0,0,0,4,4,0,
        0,0,0,0,0,4,4,0,

        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        4,4,0,0,0,0,0,0,
        4,4,4,0,0,0,0,0,
        0,4,4,0,0,0,0,0,
        0,4,4,0,0,0,0,0,

        0,0,0,0,0,4,4,0,
        0,0,0,0,0,4,4,0,
        0,0,0,0,0,4,4,4,
        0,0,0,0,0,0,4,4,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,

        0,4,4,0,0,0,0,0,
        0,4,4,0,0,0,0,0,
        4,4,4,0,0,0,0,0,
        4,4,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0


};

u8 inatrix[256] = {

        0,0,0,0,9,10,10,10,
        0,0,0,11,11,9,9,9,
        0,0,11,11,11,9,9,9,
        0,0,11,11,11,17,17,17,
        0,0,11,11,11,17,17,17,
        0,0,11,11,17,6,6,17,
        0,0,0,11,17,17,17,11,
        0,17,0,0,17,17,17,17,

        10,10,10,10,0,0,0,0,
        9,9,9,9,10,0,0,0,
        9,9,9,9,9,0,0,0,
        17,17,17,0,0,0,0,0,
        17,17,17,0,0,0,0,0,
        17,6,6,0,0,0,0,0,
        11,17,17,0,0,0,0,0,
        17,17,0,0,0,0,0,0,

        0,6,0,6,6,6,6,11,
        0,0,6,6,6,6,19,19,
        0,0,0,6,6,6,19,19,
        0,0,0,10,10,10,10,9,
        0,0,0,6,11,0,0,0,
        0,0,0,6,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,

        11,6,6,0,0,0,0,0,
        19,6,6,6,6,17,0,0,
        19,19,6,0,0,0,0,0,
        9,9,10,0,0,0,0,0,
        0,6,11,0,0,0,0,0,
        0,6,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0
};

void gfxInfo_setGfx(GfxID gfxId, SpriteSize size){
    gfxList[gfxGUID] = malloc(sizeof(GfxData));
    gfxList[gfxGUID]->memAddress = NULL;
    gfxList[gfxGUID]->GUID = gfxGUID;
    gfxList[gfxGUID]->gfxId = gfxId;
    gfxList[gfxGUID]->bitmap = gfxBitmaps[gfxId];
    gfxList[gfxGUID]->size = size;
    gfxList[gfxGUID]->colorFormat = SpriteColorFormat_256Color;

    gfxGUID++;
}

// Referencias a los arrays que contienen
// los bitmaps.
// El orden importa, como en el enum GfxID.
u8* gfxBitmaps[BITMAP_SIZE] = {
    blueCapsule,    // Blue Capsule
    redCapsule,     // Red Capsule
    inatrix,        // Inatrix_X
    inatrix,        // Inatrix_Y
    digitOne,       // Digit 1
    digitZero       // Digit 0
};

void gfxInfo_init(){

    /**
     * Ojo:
     * Cada vez que se introduzca un gráfico más, acordarse de
     * actualizar el #define GFX_NUMBER.
     */

    /* CAPSULES */
    gfxInfo_setGfx(GFX_CAPSULE_BLUE, SpriteSize_16x16);
    gfxInfo_setGfx(GFX_CAPSULE_RED, SpriteSize_16x16);

    /* INATRIX */
    gfxInfo_setGfx(GFX_INATRIX_X, SpriteSize_16x16);
    gfxInfo_setGfx(GFX_INATRIX_Y, SpriteSize_16x16);
}

/**
 * Función que genera la Matrix de manera independiente
 * Para poder construir los sprites oportunos.
 */
void gfxInfo_initMatrix(Binary *base, uint8 size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            gfxInfo_allocateMatrixElement(*(base + i*size + j) ? GFX_DIGIT_ONE : GFX_DIGIT_ZERO);
            gfxInfo_linkToMatrix(size, i, j, *(base + i*size + j) ? BIT_ONE : BIT_ZERO);
        }
    }
}

void gfxInfo_allocateMatrixElement(GfxID gfxId){
    gfxInfo_setGfx(gfxId, SpriteSize_16x16);
    sprites_memorySetup(gfxList[gfxGUID - 1]);
}

// TODO: Mejorar esto, es una chapuza.
void gfxInfo_linkToMatrix(uint8 size, uint8 i, uint8 j, Binary bit) {
    if(size == BITBLOCK_SIZE){
        bitBlockBuffer[i][j] = malloc(sizeof(MatrixElement));
        bitBlockBuffer[i][j]->sprite = sprites[gfxGUID - 1];
        bitBlockBuffer[i][j]->bit = bit;
    }else
    {
        matrix[i][j] = malloc(sizeof(MatrixElement));
        matrix[i][j]->sprite = sprites[gfxGUID - 1];
        matrix[i][j]->bit = bit;
    }
}

void gfxInfo_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}