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
 * @file game.c
 * @brief Game loop principal, así como la gestión de algunas funcionalidades
 * intrínsecas a la lógica del juego.
 */

#include "nds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "movementMgr.h"
#include "defines.h"
#include "eventMgr.h"
#include "input.h"
#include "controllers.h"
#include "backgrounds.h"
#include "game.h"
#include "timer.h"
#include "consoleUI.h"
#include "objectMgr.h"
#include "gfxInfo.h"
#include "sprites.h"

int SWITCH = 1;

GameData gameData;
PlayerData playerData;

void game_Update(){
    input_UpdateKeyData();
}

int game_getNextPhase(){

    switch(gameData.state){
        case GAME_STATE_INTRO:
            return gameData.phase + 1; // Geru: Ojo con las declaraciones
        default:
            break;
    }

    return PHASE_NULL;
}

void game_Loop()
{
    game_initData();
    game_launch();

	while(SWITCH)
	{
        game_Update();

        switch(gameData.state){
            case GAME_STATE_MAIN_MENU:
                switch(gameData.phase) {
                    case PHASE_WAITING_PLAYER_INPUT:
                        if (keyData.isPressed) {
                            gameData.phase = PHASE_NULL;
                            gameData.state = GAME_STATE_INTRO;
                            eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, NO_WAIT); // Igual una pequeña transición en negro.
                            eventMgr_ScheduleEvent(EVENT_INTRO_PRE_START, IN_2_SECONDS); // Igual una pequeña transición en negro.
                        }
                    break;
                    default:
                        break;
                }
                break;
            case GAME_STATE_INTRO:
                switch(gameData.phase){
                    case PHASE_INTRO_START:
                        eventMgr_ScheduleEvent(EVENT_MAIN_MENU_START, IN_2_SECONDS);
                        eventMgr_ScheduleEvent(EVENT_INTRO_SETBG_2, IN_2_SECONDS);
                        gameData.phase = PHASE_INTRO_SCENE_ACTIVE;
                        break;
                    case PHASE_WAITING_PLAYER_INPUT:
                            if(input_touchScreenUsed()){
                                int capsule = objectMgr_objectAreaClicked(input_getTouchScreenX(), input_getTouchScreenY());
                                if(capsule != -1){
                                    if(capsule == GFX_CAPSULE_RED){
                                        gameData.mode = DIFFICULTY_HARD_MODE;
                                    }else{
                                        gameData.mode = DIFFICULTY_NORMAL_MODE;
                                    }
                                    gameData.phase = PHASE_NULL;
                                    eventMgr_ScheduleEvent(EVENT_INTRO_CAPSULE_SELECTED, NO_WAIT);
                                }
                            }
                        break;
                    default:
                        break;
                }
                break;
            case GAME_STATE_GAME:
                switch(gameData.phase){
                    case PHASE_WAITING_PLAYER_INPUT:
                        if(keyData.isPressed){
                            switch(keyData.key){
                                case INPUT_KEY_LEFT:
                                    movementMgr_updateDirection(MOVEMENT_INATRIX_X, DIRECTION_BACKWARDS);
                                    eventMgr_ScheduleEvent(EVENT_GAME_INATRIX_MOVE_X, NO_WAIT);
                                    break;
                                case INPUT_KEY_RIGHT:
                                    movementMgr_updateDirection(MOVEMENT_INATRIX_X, DIRECTION_FORWARDS);
                                    eventMgr_ScheduleEvent(EVENT_GAME_INATRIX_MOVE_X, NO_WAIT);
                                    break;
                                case INPUT_KEY_DOWN:
                                    movementMgr_updateDirection(MOVEMENT_INATRIX_Y, DIRECTION_FORWARDS);
                                    eventMgr_ScheduleEvent(EVENT_GAME_INATRIX_MOVE_Y, NO_WAIT);
                                    break;
                                case INPUT_KEY_UP:
                                    movementMgr_updateDirection(MOVEMENT_INATRIX_Y, DIRECTION_BACKWARDS);
                                    eventMgr_ScheduleEvent(EVENT_GAME_INATRIX_MOVE_Y, NO_WAIT);
                                    break;
                                case INPUT_KEY_A:
                                    eventMgr_ScheduleEvent(EVENT_GAME_EVALUATE_BITBLOCK, NO_WAIT);
                                    break;
                                case INPUT_KEY_START:
                                    // Libnds mantiene por más de un tick datos de teclas
                                    // Esto es para evitar los problemas que se generan por
                                    // ello.
                                    if(gameData.destroyMatrixTime > 2) // Temporal, para evitar problemas con la regen.
                                        eventMgr_ScheduleEvent(EVENT_GAME_PAUSE, IN_1_SECONDS);
                                    break;
                                default:
                                    break;
                            }
                            gameData.phase = PHASE_NULL;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case GAME_STATE_PAUSE:
                if(gameData.phase == PHASE_GAME_PAUSE){
                    if(keyData.isPressed && (keyData.key == INPUT_KEY_START)){
                        gameData.state = GAME_STATE_GAME;
                        eventMgr_ScheduleEvent(EVENT_LISTEN_INPUT, IN_1_SECONDS);
                    }
                }
                break;
            case GAME_STATE_STATS:
                if((gameData.phase == PHASE_SHOW_STATS) && keyData.isPressed){
                    game_initData();
                    game_launch();
                    SWITCH = 0;
                }
                break;
            default:
                break;
        }
	}

    sprites_freeMemory();
    gfxInfo_freeMemory();
}

void game_manageScore(bool overflow){
    if(overflow){
        playerData.overflowScore++;
        playerData.totalOverflows++;
        playerData.runOverflows++;
    }else{
        playerData.overflowScore--;
        playerData.failScore++;
        if(playerData.overflowScore < 0){
            game_manageGameOver();
            return;
        }
    }
    consoleUI_showUI();
}

void game_initData(){
    gameData.state = GAME_STATE_MAIN_MENU;
    gameData.phase = PHASE_WAITING_PLAYER_INPUT;
    gameData.mode = DIFFICULTY_NORMAL_MODE;
    playerData.overflowScore = 0;
    playerData.totalOverflows = 0;
    playerData.runOverflows = 0;
    playerData.failScore = 0;
    gameData.matrixRegens = 0;
    gameData.destroyMatrixTime = TIMER_REGEN;
}

void game_launch(){
    background_SetMainBackground();
    eventMgr_ScheduleEvent(EVENT_MAIN_MENU_START, IN_2_SECONDS);
}

// Capsula Azul: Normal mode (Overflow @ 9)
// Capsula Roja: Hard mode (Overflow @ 15)
void game_setDifficulty(Difficulty difficulty){
    gameData.mode = difficulty;
}

void game_setDestroyMatrix(bool active){
    gameData.destroyMatrixActive = active;
}

void game_enableDestroyMatrix(){
    gameData.destroyMatrixActive = true;
    gameData.destroyMatrixTime = 15;
    playerData.runOverflows = 0;
}

void game_increaseMatrixRegens(){
    gameData.matrixRegens++;
}

void game_manageGameOver(){
    gameData.state = GAME_STATE_GAME_OVER;
    gameData.phase = PHASE_NULL;
    eventMgr_cancelAllEvents();
    eventMgr_ScheduleEvent(EVENT_GAME_OVER, IN_1_SECONDS);
}

bool game_achievedMinimumOverflows(){
    return playerData.runOverflows > 0;
}