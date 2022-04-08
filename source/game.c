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

GameData data;

void game_Update(){
    input_UpdateKeyData();
    // Aquí más updates que necesitemos.
}

void game_Loop()
{
	data.state = WAIT;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
	while(SWITCH)
	{
        game_Update();
        iprintf("\x1b[14;00H  Timer: %i", timer.time);

        if(keyData.isPressed && (data.state == WAIT))
        {
            if(keyData.key != -1){
                if(keyData.key == START){
                        eventMgr_ScheduleEvent(EVENT_TEST_2ND_ACTIVITY, IN_5_SECONDS-2);
                        data.state = TIMER_TESTS;
                }
            }
        }
	}
#pragma clang diagnostic pop
}



