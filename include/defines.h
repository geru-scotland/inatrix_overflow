/*-------------------------------------
defines.h
-------------------------------------*/
#ifndef DEFINES_H
#define DEFINES_H

#include "../include/libnds/nds.h" 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estandar de C
#include <stdlib.h>		//librería estandar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

#define IME		(*(vuint32*)0x04000208) //Interrupt Master Enable -- Habilitar-deshabilitar todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable -- Habilitar-deshabilitar las interrupciones de forma individual
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag -- Registro de solicitud de interrupción

//#define DEBUG_MODE
typedef unsigned char uint8;

//Acceso a los registros de la pantalla táctil
extern touchPosition PANT_DAT;

extern int SWITCH;

//Defines para los backgrounds:
//IMPORTANTE: Actualizar cada vez que se añada un nuevo background
#define Puerta 0
#define PuertaAbierta 1
#define Matrix 2
#define Matrix2 3



#endif //DEFINES_H

