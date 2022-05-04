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
	gameData.state = GAME_STATE_INTRO;
    gameData.phase = PHASE_INTRO_START;
    gameData.mode = DIFFICULTY_NORMAL_MODE; // TODO: Quitar esto cuando implementes capsulas selection
    game_initData();

	while(SWITCH)
	{
        game_Update();

        switch(gameData.state){
            case GAME_STATE_INTRO:
                switch(gameData.phase){
                    case PHASE_INTRO_START:
                        eventMgr_ScheduleEvent(EVENT_INTRO_TEXT4, IN_2_SECONDS);
                        eventMgr_ScheduleEvent(EVENT_INTRO_SETBACKGROUND1, IN_2_SECONDS);
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
                                    // Pause
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
            case GAME_STATE_GAME_OVER:
                break;
            case GAME_STATE_STATS:
                break;
            default:
                break;
        }
	}

    // Liberar recursos de memoria aquí.
    // De todos los arrays etc.
    // gfxInfo_freeMemory();
    // audioMgr_unloadSounds();
}

void game_manageScore(bool overflow){
    if(overflow){
        playerData.overflowScore++;

    }else{
        playerData.overflowScore--;
        playerData.failScore++;
        if(playerData.overflowScore <= 0){
            // Game Over
            //gameData.state = GAME_STATE_GAME_OVER;
            return;
        }
    }
    consoleUI_showUI();
}

void game_initData(){
    playerData.overflowScore = 0;
    playerData.failScore = 0;
    gameData.matrixRegens = 0;
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
    gameData.destroyMatrixTime = 30;
}

void game_increaseMatrixRegens(){
    gameData.matrixRegens++;
}