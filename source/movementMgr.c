/*
 * This file is part of the Iñatrix Overflow Project.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file movementMgr.c
 * @brief Gestión de diferentes tipos de movimientos, centrándose principalmente en el
 * movimiento en bloque y asociado a la matriz de los dos personajes.
 */

#include "movementMgr.h"
#include "sprites.h"

Movement* movementInfo[MOVEMENT_INFO_SIZE];

void movementMgr_allocateMovements(MovementGfx movGfx){
    movementInfo[movGfx] = malloc(sizeof(Movement));
    movementInfo[movGfx]->posId = START_POS;
}

void movementMgr_initSystem(){
    movementMgr_allocateMovements(MOVEMENT_INATRIX_X);
    movementMgr_allocateMovements(MOVEMENT_INATRIX_Y);
    movementInfo[MOVEMENT_INATRIX_X]->sprite = sprites[GFX_INATRIX_X];
    movementInfo[MOVEMENT_INATRIX_Y]->sprite = sprites[GFX_INATRIX_Y];
    matrix_updatePivot(START_POS, START_POS);
}

void movementMgr_updateDirection(MovementGfx movGfx, Direction direction){
    movementInfo[movGfx]->direction = direction;
}

int8 movementMgr_getMultiplier(Direction direction, uint8 posId){
    return (((posId == START_POS) && (direction == DIRECTION_BACKWARDS))
    || ((posId == MATRIX_SIZE-START_POS-1) && (direction == DIRECTION_FORWARDS))) ? -1 : 1;
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
           (direction == DIRECTION_BACKWARDS && (movementInfo[movGfx]->sprite->spriteEntry->x <= movementInfo[movGfx]->destinyPos.x
           && movementInfo[movGfx]->sprite->spriteEntry->y <= movementInfo[movGfx]->destinyPos.y));
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

uint8 movementMgr_getPositionX(){ return movementInfo[MOVEMENT_INATRIX_X]->posId; }
uint8 movementMgr_getPositionY(){ return movementInfo[MOVEMENT_INATRIX_Y]->posId; }

void movementMgr_setHomePosition(MovementGfx movGfx, uint8 x, uint8 y){
    movementInfo[movGfx]->homePos.x = x;
    movementInfo[movGfx]->homePos.y = y;
}

bool movementMgr_hasGfxReachedDest(GfxID gfxId){

    // Cambiar esto, chapuza, pero estoy reventado. Generalizar.
    if(gfxId == GFX_CAPSULE_RED){
        sprites[gfxId]->spriteEntry->x -= 1;
    }else
        sprites[gfxId]->spriteEntry->x += 1;

    sprites[gfxId]->spriteEntry->y -= 1;

    return (gfxId == GFX_CAPSULE_RED && sprites[gfxId]->spriteEntry->x <= 120) ||
            (gfxId == GFX_CAPSULE_BLUE && sprites[gfxId]->spriteEntry->x >= 120);
}

void movementMgr_destructor(){
    free(movementInfo[MOVEMENT_INATRIX_X]);
    free(movementInfo[MOVEMENT_INATRIX_Y]);
}