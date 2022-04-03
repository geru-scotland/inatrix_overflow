/*-------------------------------------
controllers.cc
-------------------------------------*/

#include "../include/libnds/nds.h"
#include <stdio.h>
#include "../include/defines.h"
#include "../include/input.h"
#include "../include/backgrounds.h"
#include "../include/sprites.h"
#include "../include/event_manager.h"
#include "../include/game.h"
// TODO: Geru: Quitar event_manager.h y game.h de aqui una vez implementado correctamente.

int seg3;

void RutAtencionTeclado ()
{
if (data.state == CLOSED)
{	
	if (TeclaPulsada()==A)
	{
		data.state = OPEN;
		visualizarPuertaAbierta();
		seg3=0;
		MostrarRombo(1, 5, 5);
		MostrarRomboGrande(2, 100, 100);
	}
}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	

if (data.state != WAIT)
{
	tick++; 
	if (tick==5)
	{
		seg++;
		iprintf("\x1b[13;5HSegundos que han pasado=%d", seg);
		tick=0;
		if (data.state == OPEN)
		{
			seg3++;
			if (seg3==3)
			{
				visualizarPuerta();
				seg3=0;
				data.state = CLOSED;
				BorrarRombo(1, 5, 5);
				BorrarRomboGrande(2, 100, 100);
			}
		}
				
	}
}
	
}

void EstablecerVectorInt()
{
// A COMPLETAR
	
}

