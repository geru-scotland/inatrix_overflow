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
 * @file objectMgr.h
 */

#ifndef INATRIX_OVERFLOW_OBJECTMGR_H
#define INATRIX_OVERFLOW_OBJECTMGR_H

#include <stdbool.h>
#include "matrix.h"

#define ANIMATIONS_SIZE 1
#define INATRIX_X_POS_Y 170

/**
 * @enum AnimID
 * @brief Listado de animaciones.
 */
typedef enum{
    ANIMATION_BIT_SHAKE = 0
} AnimID;

/**
 * @struct Animation
 * @brief Información acerca del estado de la animación.
 * @var active: Indica si la animación está activa o no.
 * @var state: indica la posición con respecto al centro.
 */
typedef struct {
    bool active;
    int8 state;
} Animation;

extern uint8 INATRIX_XHOME_POS_X;
extern uint8 INATRIX_XHOME_POS_Y;
extern uint8 INATRIX_YHOME_POS_X;
extern uint8 INATRIX_YHOME_POS_Y;

extern void objectMgr_init();
extern void objectMgr_initAnimations();
extern void objectMgr_spawnInatrix();
extern void objectMgr_despawnInatrix();
extern void objectMgr_spawnCapsules();
extern void objectMgr_setAnimationActive(AnimID animID, bool active);

extern int objectMgr_objectAreaClicked(int x, int y);
extern void objectMgr_manageSelectedCapsule(int mode);

extern void objectMgr_inatrixCastSpellX(bool cast);

extern Animation* animations[ANIMATIONS_SIZE];
#endif //INATRIX_OVERFLOW_OBJECTMGR_H
