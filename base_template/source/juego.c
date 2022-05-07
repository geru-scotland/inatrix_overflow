/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

int tiempo;

void juego()
{	
	//definiciones de variables
	int i=9;
	int tecla=0;;

	ESTADO=ESPERA;
	
	//Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HPrueba de escritura");						

/*Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas.*/
	iprintf("\x1b[23;5HPrueba de escritura con variable. Valor=%d", i);

	//*******************************EN LA 2.ACTIVIDAD ********************************//
        // LLAMADAS A REALIZAR:
	// Habilitar interrupciones.
	// Configurar el teclado.
	// Configurar el temporizador.
	// Habilitar las interrupciones del teclado.
	// Habilitar las interrupciones del temporizador.
	// Establecer las rutinas de atención a interrupciones
	//******************************************************************************//

	


	while(1)
	{	
		
      /*******************************EN LA 1.ACTIVIDAD*****************************************/
		/*Si el estado es ESPERA: codificar aquí la encuesta del teclado, sacar por pantalla la tecla que se ha pulsado, y si se pulsa ta la tecla START cambiar de estado*/



	}
}



