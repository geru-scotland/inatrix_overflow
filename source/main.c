/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo"
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/

#include "nds.h" 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estandar de C
#include <stdlib.h>		//librería estandar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarroladas por nosotros para el proyecto

#include "engine.h"
#include "sprites.h"
#include "game.h"
#include "input.h"
#include "controllers.h"
#include "eventMgr.h"
#include "audioMgr.h"
#include "movementMgr.h"
#include "objectMgr.h"

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
