/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/

#include "../include/libnds/nds.h" 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estandar de C
#include <stdlib.h>		//librería estandar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarroladas por nosotros para el proyecto

#include "../include/engine.h"
#include "../include/defines.h"
#include "../include/sprites.h"
#include "../include/game.h"
#include "../include/input.h"
#include "../include/timer.h"
#include "../include/controllers.h"

// Geru: variables globales aquí.
GameData data;
TimerData timer;

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    controllers_ConfigureInterrupts();
    iprintf("\x1b[16;00H  MAIN LLAMADO  ");
	inicializarGraficosSprites();

	//llamada al juego que vosotros programaréis
	juego();

	return(0);

}
