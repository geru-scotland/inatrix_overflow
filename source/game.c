/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include "../include/libnds/nds.h" 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "../include/defines.h"
#include "../include/eventMgr.h"
#include "../include/input.h"
#include "../include/controllers.h"
#include "../include/backgrounds.h"
#include "../include/game.h"
#include "../include/timer.h"

int tiempo;
int SWITCH = 1;

GameData gameData;

void game_Update(){
    input_UpdateKeyData();
    // Aquí más updates que necesitemos.
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

	while(SWITCH)
	{
        game_Update();

        switch(gameData.state){
            case GAME_STATE_INTRO:
                switch(gameData.phase){
                    case PHASE_INTRO_START:
                        eventMgr_ScheduleEvent(EVENT_INTRO_START, IN_5_SECONDS);
                        eventMgr_ScheduleEvent(EVENT_INTRO_SETBACKGROUND1, IN_2_SECONDS);
                        gameData.phase = PHASE_INTRO_WAITING;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
	}
}


