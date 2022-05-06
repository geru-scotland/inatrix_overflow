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
uint8 INATRIX_YHOME_POS_Y = MATRIX_Y_POS + MATRIX_Y_PADDING + 2;

Animation* animations[ANIMATIONS_SIZE];

void objectMgr_init(){
    objectMgr_initAnimations();
}

void objectMgr_spawnInatrix(){
    sprites_displaySprite(GFX_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y, false);
    sprites_displaySprite(GFX_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y, false);
    movementMgr_setHomePosition(MOVEMENT_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y);
    movementMgr_setHomePosition(MOVEMENT_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y);
}

void objectMgr_despawnInatrix(){
    sprites_displaySprite(GFX_INATRIX_X, INATRIX_XHOME_POS_X, INATRIX_XHOME_POS_Y, true);
    sprites_displaySprite(GFX_INATRIX_Y, INATRIX_YHOME_POS_X, INATRIX_YHOME_POS_Y, true);
}
void objectMgr_spawnCapsules(){
    sprites_displaySprite(GFX_CAPSULE_BLUE, 95, 80, false);
    sprites_displaySprite(GFX_CAPSULE_RED, 140, 80, false);
}

void objectMgr_initAnimations(){
    animations[ANIMATION_BIT_SHAKE] = malloc(sizeof(Animation));
    animations[ANIMATION_BIT_SHAKE]->active = false;
    animations[ANIMATION_BIT_SHAKE]->state = -1;
}

void objectMgr_setAnimationActive(AnimID animID, bool active){
    if(!active){
        matrix_bitResetPosEffect();
    }
    animations[ANIMATION_BIT_SHAKE]->active = active;
}

int objectMgr_objectAreaClicked(int x, int y){
    if(x >= 99 && x <= 108 && y >= 81 && y <= 95)
        return GFX_CAPSULE_BLUE;
    else if(x >= 148 && x <= 159 && y >= 81 && y <= 95)
        return GFX_CAPSULE_RED;

    return -1;
}

void objectMgr_manageSelectedCapsule(int mode){
    if(mode == DIFFICULTY_NORMAL_MODE){ // Blue capsule
        sprites_displaySprite(GFX_CAPSULE_RED, 145, 80, true);
    }else if(mode == DIFFICULTY_HARD_MODE){ // Red capsule
        sprites_displaySprite(GFX_CAPSULE_BLUE, 95, 80, true);
    }
}