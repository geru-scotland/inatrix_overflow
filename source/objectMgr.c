//
// Created by Eideann on 2/5/22.
//

#include "../include/objectMgr.h"
#include "../include/movementMgr.h"
#include "../include/sprites.h"

uint8 INATRIX_XHOME_POS_X = MATRIX_X_POS + MATRIX_X_PADDING;
uint8 INATRIX_XHOME_POS_Y = INATRIX_X_POS_Y;
uint8 INATRIX_YHOME_POS_X = MATRIX_X_POS-30;
uint8 INATRIX_YHOME_POS_Y = MATRIX_Y_POS + MATRIX_Y_PADDING;

void objectMgr_spawnInatrix(){
    sprites_displaySprite(GFX_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y, false);
    sprites_displaySprite(GFX_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y, false);
    movementMgr_setHomePosition(MOVEMENT_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y);
    movementMgr_setHomePosition(MOVEMENT_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y);
}

void objectMgr_spawnCapsules(){

}