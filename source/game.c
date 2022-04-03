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
#include "../include/event_manager.h"
#include "../include/input.h"
#include "../include/controllers.h"
#include "../include/backgrounds.h"
#include "../include/game.h"

int tiempo;

void juego()
{	
	//definiciones de variables
	int i=12;

	data.state = WAIT;

	//Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HPrueba de escritura");

    /*Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas.*/
	iprintf("\x1b[23;5HPrueba de escritura con variable. Valor=%d", i);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
	while(1)
	{
        /**************** EN LA 1.ACTIVIDAD ****************/

        /* Si el estado es ESPERA: codificar aquí la encuesta del teclado,
         * sacar por pantalla la tecla que se ha pulsado, y si se pulsa
         * la tecla START cambiar de estado
         * */
        GameData* data1 = malloc(sizeof *data1);
        data1->state = 2;
        if(TeclaDetectada() && (data.state == WAIT)){
            int tecla = TeclaPulsada();
            if(tecla != -1){
                iprintf("\x1b[16;00H TECLA PULSADA: %i", tecla);
                if(tecla == START){
                    visualizarPuerta();
                    data.state = CLOSED;
                }
            }
        }

        //*******************************EN LA 2.ACTIVIDAD ********************************//
        // LLAMADAS A REALIZAR:
        // Habilitar interrupciones.
        // Configurar el teclado.
        // Configurar el temporizador.
        // Habilitar las interrupciones del teclado.
        // Habilitar las interrupciones del temporizador.
        // Establecer las rutinas de atención a interrupciones
        //******************************************************************************//
	}
#pragma clang diagnostic pop
}



