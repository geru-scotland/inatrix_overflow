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
    // Está así para la segunda actividad
    if(data.state == TIMER_TESTS)
        timer_UpdateTimer();
}

void game_Loop()
{
	int i=12;

	data.state = WAIT;

	//Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HPruebaA de escritura");

    /*Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas.*/
	iprintf("\x1b[23;5HPrueba de escritura con variable. Valor=%d", i);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
	while(SWITCH)
	{
        game_Update();

        // Está así para la segunda actividad
        if(data.state == TIMER_TESTS)
        {
            iprintf("\x1b[13;00H Timer: %i", timer.time);
        }

        if(keyData.isPressed && (data.state == WAIT)) // Una vez se cambie de estado no entrará más. Puesto para tests.
        {
            if(keyData.key != -1){
                iprintf("\x1b[16;00H TECLA PULSADA: %i", keyData.key);
                if(keyData.key == START){
                    // Está así para la segunda actividad
                    timer_StartTimer();
                    data.state = TIMER_TESTS;
                }
            }
        }
	}
#pragma clang diagnostic pop
}



