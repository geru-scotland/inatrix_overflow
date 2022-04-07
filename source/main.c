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

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    controllers_InitSetup();
	inicializarGraficosSprites();

    // Main loop
	game_Loop();

	return(0);

}
