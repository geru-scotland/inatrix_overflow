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

/**
 * @brief Actualiza en cada loop las diferentes funciones (por ahora, únicamente la encargada
 * de actualizar el estado de las teclas).
 */
void game_Update(){
    input_UpdateKeyData();
}
/**
 * @brief Función auxiliar para obtener la siguiente fase.
 * @return Número de fase, del tipo @enum Phases
 */
int game_getNextPhase(){

    switch(gameData.state){
        case GAME_STATE_INTRO:
            return gameData.phase + 1;
        default:
            break;
    }
    return PHASE_NULL;
}

/**
 * @brief Game loop principal, la función principal es la de analizar y gestionar el estado
 * actual del juego y sus posibles fases, abstrayendo lógica de contenido y adquiriendo
 * un rol de "director".
 */
void game_Loop()
{
    game_initData();
    game_launch();

    while(SWITCH)
    {
        game_Update();

        switch(gameData.state){
            case GAME_STATE_MAIN_MENU:
                if (keyData.isPressed){
                    switch (keyData.key) {
                        case INPUT_KEY_START:
                            if(gameData.phase != PHASE_SHOW_MENU)
                                break;
                            gameData.phase = PHASE_NULL;
                            gameData.state = GAME_STATE_INTRO;
                            eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, NO_WAIT);
                            eventMgr_ScheduleEvent(EVENT_INTRO_PRE_START, IN_3_SECONDS);
                            break;
                        case INPUT_KEY_UP:
                        case INPUT_KEY_LEFT:
                        case INPUT_KEY_RIGHT:
                            switch(gameData.phase){
                                case PHASE_NULL:
                                    break;
                                case PHASE_SHOW_MENU:
                                    switch(keyData.key){
                                        case INPUT_KEY_LEFT:
                                            eventMgr_ScheduleEvent(EVENT_SHOW_GAMEPLAY, IN_1_SECONDS);
                                            break;
                                        case INPUT_KEY_RIGHT:
                                            eventMgr_ScheduleEvent(EVENT_SHOW_CONTROLS, IN_1_SECONDS);
                                            break;
                                        case INPUT_KEY_UP:
                                            eventMgr_ScheduleEvent(EVENT_SHOW_LORE, IN_1_SECONDS);
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case PHASE_SHOW_LORE:
                                    gameData.phase = PHASE_NULL;
                                    eventMgr_ScheduleEvent(EVENT_SHOW_LORE_2, IN_1_SECONDS);
                                    break;
                                case PHASE_SHOW_GAMEPLAY:
                                case PHASE_SHOW_LORE_2:
                                case PHASE_SHOW_CONTROLS:
                                    gameData.phase = PHASE_NULL;
                                    eventMgr_ScheduleEvent(EVENT_MAIN_MENU_START, IN_1_SECONDS);
                                    break;
                                default:
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
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
                                    /*Libnds mantiene por más de un tick datos de teclas
                                     *Esto es para evitar los problemas que se generan por
                                     *ello.
                                     */
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

/**
 * @brief Fnción auxiliar encargada de gestionar de manera oportuna cada selección
 * de bitblock.
 * @param overflow Si se ha producido overflow o no.
 */
bool game_manageScore(bool overflow){
    if(overflow){
        playerData.overflowScore++;
        playerData.totalOverflows++;
        playerData.runOverflows++;
    }else{
        playerData.overflowScore--;
        playerData.failScore++;
        if(playerData.overflowScore < 0){
            game_manageGameOver(false);
            return false;
        }
    }
    consoleUI_showUI();
    return true;
}

/**
 * @brief Inicialización de las diferentes variables en relación al juego, jugador...etc.
 */
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

/**
 * @brief Establecer en qué estado debe de comenzar el juego exactamente. Ésta función
 * ha tenido principalmente una funcionalidad de testeo, pero considero que no hace daño
 * dejarla.
 */
void game_launch(){
    background_SetMainBackground();
    eventMgr_ScheduleEvent(EVENT_MAIN_MENU_START, IN_3_SECONDS);
}

/**
 * @brief Establecer la dificultad del juego, una vez haya sido seleccionada por el
 * jugador.
 *
 * 1. Capsula Azul: Normal mode (Overflow @ 9)
 * 2. Capsula Roja: Hard mode (Overflow @ 15)
 * @param difficulty modo de dificultad, @enum Difficulty.
 */
void game_setDifficulty(Difficulty difficulty){
    gameData.mode = difficulty;
}

/**
 * @brief Establece si el sistema encargado de la gestión de
 * la destrucción/regeneración de la matriz está actualmente activo.
 * @param active
 */
void game_setDestroyMatrix(bool active){
    gameData.destroyMatrixActive = active;
}

/**
 * Habilita el sistema encargado de la gestión de
 * la destrucción/regeneración de la matriz.
 */
void game_enableDestroyMatrix(){
    gameData.destroyMatrixActive = true;
    gameData.destroyMatrixTime = 15;
    playerData.runOverflows = 0;
}

/**
 * @brief Incrementar el contador de regeneraciones.
 */
void game_increaseMatrixRegens(){
    gameData.matrixRegens++;
}

/**
 * @brief Gestiona el game over, se encarga de borrar todos los eventos en cola y de
 * programar el evento de game over con unos segundos de retraso, para evitar los problemas
 * que se pueden genera con la libnds y la actualización por tick de los bit
 * de los registros oportunos en cuanto a la detección de teclas.
 */
void game_manageGameOver(bool surrender){

    background_setBackground(BG_GAME_OVER);
    game_setDestroyMatrix(false);
    gameData.state = GAME_STATE_GAME_OVER;
    gameData.phase = PHASE_NULL;

    matrix_displayMatrix(false);
    objectMgr_despawnInatrix();
    eventMgr_ScheduleEvent(EVENT_SHOW_STATS, IN_4_SECONDS);

    if(!surrender)
        consoleUI_showGameOver();
    else
        consoleUI_showSurrenderUI();

}

/**
 * @brief Comprueba si el jugador ha conseguido al menos 1 overflow
 * durante éste "run". Siendo "run" el tiempo entre una regeneración de la matriz
 * principal y la siguiente.
 * @return TRUE si ha conseguido al menos 1 overflow - FALSE en caso contrario.
 */
bool game_achievedMinimumOverflows(){
    return playerData.runOverflows > 0;
}
void game_surrender(){
    game_manageGameOver(true);
}