//
// Created by Geru on 2/5/22.
// Gestor de movimiento para ambos Iñatrix
// Movimiento en bloque
//

#include "../include/movementMgr.h"
#include "../include/sprites.h"

Movement* movementInfo[MOVEMENT_INFO_SIZE];

void movementMgr_allocateMovements(MovementGfx movGfx){
    movementInfo[movGfx] = malloc(sizeof(Movement));
    movementInfo[movGfx]->homePos = malloc(sizeof(Vector));
    movementInfo[movGfx]->destinyPos = malloc(sizeof(Vector));
}

void movementMgr_initSystem(){
    movementMgr_allocateMovements(MOVEMENT_INATRIX_X);
    movementMgr_allocateMovements(MOVEMENT_INATRIX_Y);
    movementInfo[MOVEMENT_INATRIX_X]->sprite = sprites[GFX_INATRIX_X];
    movementInfo[MOVEMENT_INATRIX_Y]->sprite = sprites[GFX_INATRIX_Y];
}

void movementMgr_setHomePosition(MovementGfx movGfx){
    // TODO: Hacer control de extremos.
    movementInfo[movGfx]->homePos->x = movementInfo[movGfx]->sprite->spriteEntry->x;
    movementInfo[movGfx]->homePos->y = movementInfo[movGfx]->sprite->spriteEntry->y;

    if(movGfx == MOVEMENT_INATRIX_X){
        movementInfo[movGfx]->destinyPos->x = movementInfo[movGfx]->homePos->x + MATRIX_X_PADDING;
        movementInfo[movGfx]->destinyPos->y = movementInfo[movGfx]->homePos->y;
    }else{
        movementInfo[movGfx]->destinyPos->y = movementInfo[movGfx]->homePos->y + MATRIX_Y_PADDING;
    }
}

bool movementMgr_nextPositionReached(MovementGfx movGfx){


    if(movementInfo[movGfx]->sprite->spriteEntry->x >= movementInfo[movGfx]->destinyPos->x
    && movementInfo[movGfx]->sprite->spriteEntry->y >= movementInfo[movGfx]->destinyPos->y){
        // Reset movement struct

        return true;
    }else{
        // Move
        // TODO: Hacer control de extremos.
        if(movGfx == MOVEMENT_INATRIX_X)
            movementInfo[movGfx]->sprite->spriteEntry->x += 1;
        else
            movementInfo[movGfx]->sprite->spriteEntry->y += 1;
    }
    return false;
}

void movementMgr_destructor(){
    free(movementInfo[MOVEMENT_INATRIX_X]);
    free(movementInfo[MOVEMENT_INATRIX_Y]);
}