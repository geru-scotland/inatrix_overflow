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
#include "../include/sprites.h"
#include "../include/game.h"
#include "../include/input.h"
#include "../include/controllers.h"
#include "../include/eventMgr.h"
#include "../include/audioMgr.h"
#include "../include/movementMgr.h"
#include "../include/objectMgr.h"

int main(void) {
    eventMgr_InitEventSystem();
    controllers_InitSetup();
	inicializarGraficosSprites();
    //audioMgr_initAudio();
    matrix_initSystem();
    movementMgr_initSystem();
    objectMgr_init();
	game_Loop();
	return(0);
}
