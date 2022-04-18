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

void gfxInfo_setGfx(uint8 guid, GfxID gfxId, SpriteSize size, bool overwrite){
    gfxList[guid] = malloc(sizeof(GfxData));
    gfxList[guid]->memAddress = NULL;
    gfxList[guid]->GUID = guid;
    gfxList[guid]->gfxId = gfxId;
    gfxList[guid]->bitmap = gfxBitmaps[gfxId];
    gfxList[guid]->size = size;
    gfxList[guid]->colorFormat = SpriteColorFormat_256Color;

    if(!overwrite)
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
    gfxInfo_setGfx(gfxGUID, GFX_CAPSULE_BLUE, SpriteSize_16x16, false);
    gfxInfo_setGfx(gfxGUID, GFX_CAPSULE_RED, SpriteSize_16x16, false);

    /* INATRIX */

    /* NUMBER_1 */

    // matrix_initMatrix()
    // dir a matrix, malloc

}
/**
 * Función que genera la Matrix de manera independiente
 * Para poder construir los sprites oportunos.
 */
void gfxInfo_initMatrix(){

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            gfxInfo_setGfx(gfxGUID, matrix[i][j] ? GFX_DIGIT_ONE : GFX_DIGIT_ZERO, SpriteSize_16x16, false);
            sprites_memorySetup(gfxList[gfxGUID - 1]);
            spriteMatrix[i][j] = sprites[gfxGUID - 1];
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
void gfxInfo_overwriteMatrixGfx(uint8 i, uint8 j, Binary digit){

    if(spriteMatrix[i][j] != NULL){

        uint8 guid = spriteMatrix[i][j]->gfx->GUID;
        int x = spriteMatrix[i][j]->spriteEntry->x;
        int y = spriteMatrix[i][j]->spriteEntry->y;

        sprites_displaySprite(guid, 0, 0, true);
        free(gfxList[guid]);
        free(sprites[guid]);
        free(spriteMatrix[i][j]);
        gfxInfo_setGfx(guid, digit ? GFX_DIGIT_ONE : GFX_DIGIT_ZERO, SpriteSize_16x16, true);
        sprites_memorySetup(gfxList[guid]);
        spriteMatrix[i][j] = sprites[guid];
        sprites_displaySprite(guid, x, y, false);
    }

}

void gfxInfo_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}