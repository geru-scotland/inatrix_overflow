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

//registros del temporizador Timer0
#define TIMER0_CNT   (*(vuint16*)0x04000102) //registro de control
#define TIMER0_DAT    (*(vuint16*)0x04000100) //registro de datos

//Acceso a los registros de la pantalla táctil
extern touchPosition PANT_DAT;

#define MAX_EVENTS 15
extern int SWITCH;

#endif

