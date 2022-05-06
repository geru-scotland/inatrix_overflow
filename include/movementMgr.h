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
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file movementMgr.h
 */

#ifndef INATRIX_OVERFLOW_MOVEMENTMGR_H
#include "defines.h"
#include <stdbool.h>

#define INATRIX_OVERFLOW_MOVEMENTMGR_H
#define MOVEMENT_INFO_SIZE 2
#define START_POS 1

/**
 * @enum MovementGfx
 * @brief Listado de tipos de movimientos
 */
typedef enum{
    MOVEMENT_INATRIX_X,
    MOVEMENT_INATRIX_Y
} MovementGfx;

/**
 * @enum Direction
 * @brief Listado de direcciones
 */
typedef enum{
    DIRECTION_BACKWARDS  = -1,
    DIRECTION_FORWARDS    = 1
} Direction;

/**
 * @struct Vector
 * @brief Vector posición de un objeto
 * @var x: posición en el eje x
 * @var y: posición en el eje y
 */
typedef struct{
    uint8 x;
    uint8 y;
} Vector;

/**
 * @struct Movement
 * @brief Estructura con datos útiles relacionados al movimiento de cada GFX/Sprite.
 * @var posId: Asociación con la matriz. Hace referencia a la fila o columna asociada a
 * la posición del sprite en cada momento.
 * @var homePos: posición inicial o "home" de un sprite. Podría considerarse la posición de inicio "absoluta".
 * @var startPos: posición de inicio "relativa" a cada movimiento. Cada vez que se dé la orden de movimiento
 * @var destinyPos: posición destino "relativa" a cada movimiento. Cada vez que se dé la orden de movimiento.
 * @var direction: Indica la dirección de movimiento establecida en @enum Direction
 * @var sprite: Puntero a @struct Sprite.
 */
typedef struct{
    uint8 posId;
    Vector homePos;
    Vector startPos;
    Vector destinyPos;
    Direction direction;
    Sprite* sprite;
} Movement;

extern void movementMgr_allocateMovements(MovementGfx movGfx);
extern void movementMgr_initSystem();
extern void movementMgr_updateDirection(MovementGfx movGfx, Direction direction);
extern int8 movementMgr_getMultiplier(Direction direction, uint8 posId);
extern void movementMgr_movePosition(MovementGfx gfxMove);
extern bool movementMgr_checkPosition(Direction direction, MovementGfx movGfx);
extern bool movementMgr_nextPositionReached(MovementGfx movGfx);
extern uint8 movementMgr_getPositionX();
extern uint8 movementMgr_getPositionY();
extern void movementMgr_setHomePosition(MovementGfx movGfx, uint8 x, uint8 y);
extern bool movementMgr_hasGfxReachedDest(GfxID gfxId);
extern void movementMgr_destructor();

extern Movement* movementInfo[MOVEMENT_INFO_SIZE];
#endif //INATRIX_OVERFLOW_MOVEMENTMGR_H
