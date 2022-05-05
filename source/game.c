/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo"
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include "../include/libnds/nds.h" 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos
#include "../include/movementMgr.h"

//librerías desarrolladas por nosotros para el proyecto

#include "../include/defines.h"
#include "../include/eventMgr.h"
#include "../include/input.h"
#include "../include/controllers.h"
#include "../include/backgrounds.h"
#include "../include/game.h"
#include "../include/timer.h"
#include "../include/consoleUI.h"
#include "../include/objectMgr.h"
#include "../include/gfxInfo.h"
#include "../include/sprites.h"

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