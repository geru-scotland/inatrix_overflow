//
// Created by Geru on 15/4/22.
//
#include "../include/gfxInfo.h"
#include "../include/utils.h"
#include "../include/sprites.h"

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

        0,0,0,0,0,3,3,3,
        0,0,0,0,3,0,0,0,
        0,0,0,3,0,0,0,0,
        0,0,0,3,0,0,0,0,
        0,0,0,3,0,0,0,0,
        0,0,0,3,0,0,0,0,
        0,0,0,3,0,0,0,0,
        0,0,0,3,3,3,3,3,

        3,3,3,3,0,0,0,0,
        0,0,0,0,3,0,0,0,
        0,0,0,0,0,3,0,0,
        0,0,0,0,0,3,0,0,
        0,0,0,0,0,3,0,0,
        0,0,0,0,0,3,0,0,
        0,0,0,0,0,3,0,0,
        3,3,3,3,3,3,0,0,

        0,0,0,3,3,3,3,3,
        0,0,0,3,3,3,3,3,
        0,0,0,3,3,3,3,3,
        0,0,0,3,3,3,3,3,
        0,0,0,3,3,3,3,3,
        0,0,0,3,3,3,3,3,
        0,0,0,0,3,3,3,3,
        0,0,0,0,0,3,3,3,

        3,3,3,3,3,3,0,0,
        3,3,3,3,3,3,0,0,
        3,3,3,3,3,3,0,0,
        3,3,3,3,3,3,0,0,
        3,3,3,3,3,3,0,0,
        3,3,3,3,3,3,0,0,
        3,3,3,3,3,0,0,0,
        3,3,3,3,0,0,0,0
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

u8* gfxBitmaps[BITMAP_SIZE] = {
    redCapsule,
    blueCapsule,
    digitOne,
    digitZero
};

void gfxInfo_init(){

    /**
     * Ojo:
     * Cada vez que se introduzca un gráfico más, acordarse de
     * actualizar el #define GFX_NUMBER

     */

    /* CAPSULES */
    gfxInfo_setGfx(GFX_CAPSULE_BLUE, SpriteSize_16x16);
    gfxInfo_setGfx(GFX_CAPSULE_RED, SpriteSize_16x16);

    /* INATRIX */

}

/**
 * Función que genera la Matrix de manera independiente
 * Para poder construir los sprites oportunos.
 */
void gfxInfo_initMatrix(Binary *base, uint8 size){

    // C guarda internamente los arrays 2D como 1D, calculamos la
    // Posición en consecuencia con *(base + i*rowsCols + j)
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
void gfxInfo_linkToMatrix(uint8 size, uint8 i, uint8 j, Binary digit) {
    if(size == BITBLOCK_SIZE){
        bitBlockBuffer[i][j] = malloc(sizeof(MatrixElement));
        bitBlockBuffer[i][j]->sprite = sprites[gfxGUID - 1];
        bitBlockBuffer[i][j]->digit = digit;
    }else
    {
        matrix[i][j] = malloc(sizeof(MatrixElement));
        matrix[i][j]->sprite = sprites[gfxGUID - 1];
        matrix[i][j]->digit = digit;
    }
}

void gfxInfo_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}