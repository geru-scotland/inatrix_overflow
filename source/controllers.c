/*-------------------------------------
controllers.cc
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "input.h"
#include "backgrounds.h"
#include "sprites.h"

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

