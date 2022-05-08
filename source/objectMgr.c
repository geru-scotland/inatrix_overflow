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
 * @file objectMgr.c
 * @brief Gestor de diversos objetos del juego.
 */

#include "objectMgr.h"
#include "movementMgr.h"
#include "sprites.h"
#include "game.h"

uint8 INATRIX_XHOME_POS_X = MATRIX_X_POS + MATRIX_X_PADDING;
uint8 INATRIX_XHOME_POS_Y = INATRIX_X_POS_Y;
uint8 INATRIX_YHOME_POS_X = MATRIX_X_POS-30;
uint8 INATRIX_YHOME_POS_Y = MATRIX_Y_POS + MATRIX_Y_PADDING;

/**
 * @var animatinos[ANIMATION_SIZE]: Array que contiene punterios a struct @struct Animation.
 */
Animation* animations[ANIMATIONS_SIZE];

/**
 * @brief Inicializa las animaciones.
 */
void objectMgr_init(){
    objectMgr_initAnimations();
}

/**
 * @brief Spawn y asignación de posición "home" de Iñatrix.
 */
void objectMgr_spawnInatrix(){
    sprites_displaySprite(GFX_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y, false);
    sprites_displaySprite(GFX_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y, false);
    movementMgr_setHomePosition(MOVEMENT_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y);
    movementMgr_setHomePosition(MOVEMENT_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y);
}

/**
 * @brief Despawn de Iñatrix.
 */
void objectMgr_despawnInatrix(){
    sprites_displaySprite(GFX_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y, true);
    sprites_displaySprite(GFX_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y, true);
}

/**
 * @brief Spawn the las capsulas.
 */
void objectMgr_spawnCapsules(){
    sprites_displaySprite(GFX_CAPSULE_BLUE, 95, 80, false);
    sprites_displaySprite(GFX_CAPSULE_RED, 140, 80, false);
}

/**
 * @brief Reserva memoria dinámica e inicializa las animaciones.
 */
void objectMgr_initAnimations(){
    animations[ANIMATION_BIT_SHAKE] = malloc(sizeof(Animation));
    animations[ANIMATION_BIT_SHAKE]->active = false;
    animations[ANIMATION_BIT_SHAKE]->state = -1;
}

/**
 * @brief Establece si una animación está activa o no.
 * @param animID ID de la animación.
 * @param active Indica si se ha de poner activa o no.
 */
void objectMgr_setAnimationActive(AnimID animID, bool active){
    if(!active){
        matrix_bitResetPosEffect();
    }
    animations[ANIMATION_BIT_SHAKE]->active = active;
}

/**
 * @brief Detecta si un GFX determinado ha sido clickado a través de la
 * pantalla táctil.
 * @param x coordenada X de la posición donde se ha hecho click.
 * @param y coordenada Y de la posición donde se ha hecho click.
 * @return @enum GfxID del objeto clickado, -1 si ninguno.
 */
int objectMgr_objectAreaClicked(int x, int y){
    if(x >= 99 && x <= 108 && y >= 81 && y <= 95)
        return GFX_CAPSULE_BLUE;
    else if(x >= 140 && x <= 159 && y >= 81 && y <= 95)
        return GFX_CAPSULE_RED;

    return -1;
}

/**
 * @brief Función auxiliar para mostrar/ocultar capsulas en función de cual
 * ha sido seleccionada mediante la pantalla táctil.
 * @param mode Modo de juego seleccionado por el jugador.
 */
void objectMgr_manageSelectedCapsule(int mode){
    if(mode == DIFFICULTY_NORMAL_MODE){ // Blue capsule
        sprites_displaySprite(GFX_CAPSULE_RED, 145, 80, true);
    }else if(mode == DIFFICULTY_HARD_MODE){ // Red capsule
        sprites_displaySprite(GFX_CAPSULE_BLUE, 95, 80, true);
    }
}