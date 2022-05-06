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

/**
 * @var movementInfo[MOVEMENT_INFO_SIZE]: array que almacena punteros a structs @struct Movement, para poder gestionar
 * toda la información relativa al movimiento de cada GFX/Sprite.
 */
Movement* movementInfo[MOVEMENT_INFO_SIZE];

/**
 * @brief Reserva en memoria dinámica o heap espacio para los struct @struct Movement. Inicializa la posición de inicio.
 * @param movGfx tipo de movimiento asociado a Iñatrix.
 */
void movementMgr_allocateMovements(MovementGfx movGfx){
    movementInfo[movGfx] = malloc(sizeof(Movement));
    movementInfo[movGfx]->posId = START_POS;
}

/**
 * @brief Encargada de llamar a las funciones que reserven memoria dinámica para los movimientos asociados a Iñatrix.
 * Asocia sprite <-> movimientos y actualiza el pivot de la matriz a la posición inicial.
 */
void movementMgr_initSystem(){
    movementMgr_allocateMovements(MOVEMENT_INATRIX_X);
    movementMgr_allocateMovements(MOVEMENT_INATRIX_Y);
    movementInfo[MOVEMENT_INATRIX_X]->sprite = sprites[GFX_INATRIX_X];
    movementInfo[MOVEMENT_INATRIX_Y]->sprite = sprites[GFX_INATRIX_Y];
    matrix_updatePivot(START_POS, START_POS);
}

/**
 * @brief Actualiza la dirección cuando corresponda.
 * @param movGfx tipo de movimiento asociado a Iñatrix.
 * @param direction dirección en la que el sprite se está moviendo.
 */
void movementMgr_updateDirection(MovementGfx movGfx, Direction direction){
    movementInfo[movGfx]->direction = direction;
}

/**
 * @brief Calcula el multiplicador que provocará un cambio de dirección en el sprite o no, dependiendo
 * de la posición actual de Iñatrix. Evita que se salga de los extremos.
 * @param direction dirección en la que el sprite se va a mover.
 * @param posId Asociación con la matriz. Hace referencia a la fila o columna asociada a
 * la posición del sprite en cada momento.
 * @return 1 si no se ha de cambiar la dirección y -1 en caso contrario.
 */
int8 movementMgr_getMultiplier(Direction direction, uint8 posId){
    return (((posId == START_POS) && (direction == DIRECTION_BACKWARDS))
    || ((posId == MATRIX_SIZE-START_POS-1) && (direction == DIRECTION_FORWARDS))) ? -1 : 1;
}

/**
 * @brief Función encargada de gestionar el movimiento en bloque del personaje, manteniendo la asociación
 * con la posición del elemento pivote de la matriz en todo momento.
 * @param movGfx tipo de movimiento asociado a Iñatrix.
 */
void movementMgr_movePosition(MovementGfx movGfx){
    movementInfo[movGfx]->startPos.x = movementInfo[movGfx]->sprite->spriteEntry->x;
    movementInfo[movGfx]->startPos.y = movementInfo[movGfx]->sprite->spriteEntry->y;
    int mul = movementMgr_getMultiplier(movementInfo[movGfx]->direction, movementInfo[movGfx]->posId);
    // @todo: Rehacer esto, chapuza.
    if(movGfx == MOVEMENT_INATRIX_X){
        movementInfo[movGfx]->destinyPos.x =
                movementInfo[movGfx]->startPos.x +
                (MATRIX_X_PADDING * mul * movementInfo[movGfx]->direction);

        movementInfo[movGfx]->destinyPos.y = movementInfo[movGfx]->startPos.y;
    } else {
        movementInfo[movGfx]->destinyPos.y =
                movementInfo[movGfx]->startPos.y +
                (MATRIX_Y_PADDING * mul * movementInfo[movGfx]->direction);

        movementInfo[movGfx]->destinyPos.x = movementInfo[movGfx]->startPos.x;
    }
    movementMgr_updateDirection(movGfx, movementInfo[movGfx]->direction * mul);
}

/**
 * @brief Comprueba si se ha llegado a la posición destino o no, en cada movimiento.
 * @param direction dirección en la que el sprite se va a mover.
 * @param movGfx tipo de movimiento asociado a Iñatrix.
 * @return TRUE si se ha llegado, FALSE en caso contrario.
 */
bool movementMgr_checkPosition(Direction direction, MovementGfx movGfx){

    return (direction == DIRECTION_FORWARDS && (movementInfo[movGfx]->sprite->spriteEntry->x >= movementInfo[movGfx]->destinyPos.x
           && movementInfo[movGfx]->sprite->spriteEntry->y >= movementInfo[movGfx]->destinyPos.y)) ||
           (direction == DIRECTION_BACKWARDS && (movementInfo[movGfx]->sprite->spriteEntry->x <= movementInfo[movGfx]->destinyPos.x
           && movementInfo[movGfx]->sprite->spriteEntry->y <= movementInfo[movGfx]->destinyPos.y));
}

/**
 * @brief Función encargada de mover el sprite, mientras no se haya llegado a la posición.
 * @param movGfx tipo de movimiento asociado a Iñatrix.
 * @return TRUE si se ha llegado, FALSE en caso contrario.
 */
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

/**
 * @brief Información sobre la posición asociada a la matriz actual.
 * @return devuelve la columna.
 */
uint8 movementMgr_getPositionX(){ return movementInfo[MOVEMENT_INATRIX_X]->posId; }

/**
 * @brief Información sobre la posición asociada a la matriz actual.
 * @return devuelve la fila.
 */
uint8 movementMgr_getPositionY(){ return movementInfo[MOVEMENT_INATRIX_Y]->posId; }

/**
 * @brief Establece la posición inicial o "home" del sprite. En caso de respawn etc, el gráfico
 * se respawneará en ella.
 * @param movGfx tipo de movimiento asociado a Iñatrix.
 * @param x posición en el eje x.
 * @param y posición en el eje y.
 */
void movementMgr_setHomePosition(MovementGfx movGfx, uint8 x, uint8 y){
    movementInfo[movGfx]->homePos.x = x;
    movementInfo[movGfx]->homePos.y = y;
}

/**
 * @brief Indica si un GFX con tipo de movimiento genérico ha llegado a su posición destino.
 * @param gfxId Identificador del gráfico / sprite.
 * @return TRUE si ha llegado a su posición destino, FALSE en caso contrario.
 */
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

/**
 * @brief Función que libera de la memoria dinámica o heap los structs @struct Movement.
 */
void movementMgr_destructor(){
    free(movementInfo[MOVEMENT_INATRIX_X]);
    free(movementInfo[MOVEMENT_INATRIX_Y]);
}