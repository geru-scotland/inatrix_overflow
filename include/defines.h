/*-------------------------------------
defines.h
-------------------------------------*/
#ifndef DEFINES_H
#define DEFINES_H

#include "nds.h" 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estandar de C
#include <stdlib.h>		//librería estandar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

#define IME		(*(vuint32*)0x04000208) //Interrupt Master Enable -- Habilitar-deshabilitar todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable -- Habilitar-deshabilitar las interrupciones de forma individual
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag -- Registro de solicitud de interrupción

#define CONSOLE_ROWS 23
#define CONSOLE_COLUMNS 31
#define WINDOW_WIDTH 255
#define WINDOW_HEIGHT 191

#define BIT_ONE 1
#define BIT_ZERO 0

//#define DEBUG_MODE
typedef unsigned char uint8;

extern int SWITCH;

// Importante el orden.
// Introducir nuevos GFX previo a DIGIT_ONE
typedef enum{
    GFX_CAPSULE_BLUE = 0,
    GFX_CAPSULE_RED,
    GFX_INATRIX_X,
    GFX_INATRIX_Y,
    GFX_DIGIT_ONE,
    GFX_DIGIT_ZERO,
} GfxID;


typedef struct {
    u16* memAddress;
    uint8 GUID;
    GfxID gfxId;
    u8* bitmap;
    SpriteSize size;
    SpriteColorFormat colorFormat;
} GfxData;

typedef struct {
    uint8 index;
    SpriteEntry* spriteEntry;
    int speed;
    GfxData* gfx;
} Sprite;

#endif //DEFINES_H

