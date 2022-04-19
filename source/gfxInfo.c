//
// Created by Geru on 15/4/22.
//
#include "../include/gfxInfo.h"
#include "../include/utils.h"
#include "../include/sprites.h"

GfxData* gfxList[GFX_SIZE];
static uint8 gfxGUID = 0;

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

    /* CAPSULES */
    gfxInfo_setGfx(GFX_CAPSULE_BLUE, SpriteSize_16x16);
    gfxInfo_setGfx(GFX_CAPSULE_RED, SpriteSize_16x16);

    /* INATRIX */

    /* NUMBER_1 */
    gfxInfo_initMatrix();
}
/**
 * Función que genera la Matrix de manera independiente
 * Para poder construir los sprites oportunos.
 */
void gfxInfo_initMatrix(){

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            gfxInfo_setGfx(baseMatrix[i][j] ? GFX_DIGIT_ONE : GFX_DIGIT_ZERO, SpriteSize_16x16);
            sprites_memorySetup(gfxList[gfxGUID - 1]);
            matrix[i][j]->sprite = sprites[gfxGUID - 1];
            matrix[i][j]->digit = baseMatrix[i][j] ? BIT_ONE : BIT_ZERO;
        }
    }
}

void gfxInfo_overwriteGfx(uint8 index){

}

/**
 * Esto es/será llamado desde la propia Matrix, la real.
 * Cuando quiera replicar los cambios sufridos en sí misma

 * @param i
 * @param j
 * @param digit
 */
void gfxInfo_replicateMatrixGfx(uint8 i, uint8 j, Binary digit){
/*
    if(matrix[i][j]->sprite!= NULL){

        uint8 guid = matrix[i][j]->sprite->gfx->GUID;

        sprites_displaySprite(guid, 0, 0, true);
        free(gfxList[guid]);
        free(sprites[guid]);
        free(matrix[i][j]->sprite);
        gfxInfo_setGfx(digit ? GFX_DIGIT_ONE : GFX_DIGIT_ZERO, SpriteSize_16x16);
        sprites_memorySetup(gfxList[guid]);
        matrix[i][j]->sprite = sprites[guid];
        sprites_displaySprite(guid, matrix_getPositionX(j), matrix_getPositionY(i), false);
    }
*/
}

void gfxInfo_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}