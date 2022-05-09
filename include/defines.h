/*-------------------------------------
defines.h
-------------------------------------*/
#ifndef DEFINES_H
#define DEFINES_H

#include "nds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IME		(*(vuint32*)0x04000208) //Interrupt Master Enable
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag

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
/**
 * @enum GfxID
 * @brief Identificadores de los GFX.
 *
 */
typedef enum {
    GFX_CAPSULE_BLUE = 0,
    GFX_CAPSULE_RED,
    GFX_INATRIX_X,
    GFX_INATRIX_Y,
    GFX_DIGIT_ONE,
    GFX_DIGIT_ZERO,
    GFX_INATRIX_SPELL_X,
} GfxID;

/**
 * @struct GfxData
 * @brief Aúna los datos más relevantes y exclusivos a GFX.
 * @var memAddress: Primera posición del bloque de memoria reservado por oamMain (libnds)
 * @var GUID: Global unique identifier.
 * @var gfxId: Identificador del GFX.
 * @var bitmap: referencia al bitmap.
 */
typedef struct {
    u16* memAddress;
    uint8 GUID;
    GfxID gfxId;
    u8* bitmap;
    SpriteSize size;
    SpriteColorFormat colorFormat;
} GfxData;

/**
 * @struct Sprite
 * @brief Sirve para asociar un sprite a los GFX.
 * @var index: índice del sprite.
 * @var spriteEntry: puntero a SpriteEntry (libnds). Sirve para obtener/modificar vector posición.
 * @var speed: velocidad de movimiento.
 * @var gfx: Puntero a @struct GfxData asociado.
 */
typedef struct {
    uint8 index;
    SpriteEntry* spriteEntry;
    int speed;
    GfxData* gfx;
} Sprite;

#endif //DEFINES_H

