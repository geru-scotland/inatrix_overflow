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
    //Ojo, inicializar con valores correctos, no está siendo init con
    //los dados en el eventmgr
    movementInfo[movGfx]->homePos.x = movementInfo[movGfx]->sprite->spriteEntry->x;
    movementInfo[movGfx]->homePos.y = movementInfo[movGfx]->sprite->spriteEntry->y;
    movementInfo[movGfx]->posId = 0;
}

void movementMgr_initSystem(){
    movementMgr_allocateMovements(MOVEMENT_INATRIX_X);
    movementMgr_allocateMovements(MOVEMENT_INATRIX_Y);
    movementInfo[MOVEMENT_INATRIX_X]->sprite = sprites[GFX_INATRIX_X];
    movementInfo[MOVEMENT_INATRIX_Y]->sprite = sprites[GFX_INATRIX_Y];
}

void movementMgr_updateDirection(MovementGfx movGfx, Direction direction){
    movementInfo[movGfx]->direction = direction;
}

int8 movementMgr_getMultiplier(Direction direction, uint8 posId){
    return (((posId == 0) && (direction == DIRECTION_BACKWARDS))
    || ((posId == MATRIX_SIZE-1) && (direction == DIRECTION_FORWARDS))) ? -1 : 1;
}

void movementMgr_movePosition(MovementGfx gfxMove){
    movementInfo[gfxMove]->startPos.x = movementInfo[gfxMove]->sprite->spriteEntry->x;
    movementInfo[gfxMove]->startPos.y = movementInfo[gfxMove]->sprite->spriteEntry->y;
    int mul = movementMgr_getMultiplier(movementInfo[gfxMove]->direction, movementInfo[gfxMove]->posId);
    // TODO: Rehacer esto, chapuza.
    if(gfxMove == MOVEMENT_INATRIX_X){
        movementInfo[gfxMove]->destinyPos.x =
                movementInfo[gfxMove]->startPos.x +
                (MATRIX_X_PADDING * mul * movementInfo[gfxMove]->direction);

        movementInfo[gfxMove]->destinyPos.y = movementInfo[gfxMove]->startPos.y;
    } else {
        movementInfo[gfxMove]->destinyPos.y =
                movementInfo[gfxMove]->startPos.y +
                (MATRIX_Y_PADDING * mul * movementInfo[gfxMove]->direction);

        movementInfo[gfxMove]->destinyPos.x = movementInfo[gfxMove]->startPos.x;
    }
    movementMgr_updateDirection(gfxMove, movementInfo[gfxMove]->direction * mul);
}

bool movementMgr_checkPosition(Direction direction, MovementGfx movGfx){

    return (direction == DIRECTION_FORWARDS && (movementInfo[movGfx]->sprite->spriteEntry->x >= movementInfo[movGfx]->destinyPos.x
           && movementInfo[movGfx]->sprite->spriteEntry->y >= movementInfo[movGfx]->destinyPos.y)) ||
           direction == DIRECTION_BACKWARDS && (movementInfo[movGfx]->sprite->spriteEntry->x <= movementInfo[movGfx]->destinyPos.x
           && movementInfo[movGfx]->sprite->spriteEntry->y <= movementInfo[movGfx]->destinyPos.y);
}

bool movementMgr_nextPositionReached(MovementGfx movGfx){

    if(movementMgr_checkPosition(movementInfo[movGfx]->direction, movGfx)){
            movementInfo[movGfx]->posId += 1 * movementInfo[movGfx]->direction;
            return true;
    }else{
            if(movGfx == MOVEMENT_INATRIX_X)
                movementInfo[movGfx]->sprite->spriteEntry->x += 1 * movementInfo[movGfx]->direction;
            else
                movementInfo[movGfx]->sprite->spriteEntry->y += 1 * movementInfo[movGfx]->direction;
    }

    return false;
}

void movementMgr_destructor(){
    free(movementInfo[MOVEMENT_INATRIX_X]);
    free(movementInfo[MOVEMENT_INATRIX_Y]);
}